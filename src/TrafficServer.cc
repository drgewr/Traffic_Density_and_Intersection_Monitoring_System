#include "TrafficServer.h"

#include "TrafficEvent_m.h"

Define_Module(TrafficServer);

void TrafficServer::initialize()
{
    serviceTimer = new cMessage("serviceTimer");

    queueLengthSignal = registerSignal("queueLength");
    endToEndDelaySignal = registerSignal("endToEndDelay");
    droppedEventsSignal = registerSignal("droppedEvents");
    processedEventsSignal = registerSignal("processedEvents");

    emit(queueLengthSignal, 0);
}

void TrafficServer::handleMessage(cMessage *msg)
{
    if (msg == serviceTimer) {
        TrafficEvent *currentEvent = static_cast<TrafficEvent *>(serviceTimer->getContextPointer());

        processedEvents++;

        simtime_t delay = simTime() - currentEvent->getCreatedAt(); //delay of processing time

        emit(endToEndDelaySignal, delay);
        emit(processedEventsSignal, 1);

        delete currentEvent; //delete the processed event
        serviceTimer->setContextPointer(nullptr);

        busy = false;
        processNextEvent(); //go to next event

        return;
    }

    TrafficEvent *event = check_and_cast<TrafficEvent *>(msg);

    int capacity = par("queueCapacity").intValue();

    if ((int)eventQueue.size() >= capacity) { //if greater than server capacity, drop the event
        droppedEvents++;
        emit(droppedEventsSignal, 1);
        delete event;
        return;
    }

    //event is added to queue
    eventQueue.push(event);
    emit(queueLengthSignal, (long)eventQueue.size());

    if (!busy)
        processNextEvent(); //next event
}

void TrafficServer::processNextEvent()
{
    if (eventQueue.empty()) {
        emit(queueLengthSignal, 0);
        return;
    }

    TrafficEvent *event = eventQueue.front();
    eventQueue.pop();

    emit(queueLengthSignal, (long)eventQueue.size());

    //start processing one event
    busy = true;

    simtime_t serviceTime = par("serviceTime").doubleValue();

    serviceTimer->setContextPointer(event);
    scheduleAt(simTime() + serviceTime, serviceTimer);
}

TrafficServer::~TrafficServer()
{
    EV << "Processed events: " << processedEvents << "\n";
    EV << "Dropped events: " << droppedEvents << "\n";
    EV << "Final queue length: " << eventQueue.size() << "\n";

    cancelAndDelete(serviceTimer);

    while (!eventQueue.empty()) {
        delete eventQueue.front();
        eventQueue.pop();
    }
}
