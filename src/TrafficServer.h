#ifndef __TRAFFIC_TRAFFICSERVER_H_
#define __TRAFFIC_TRAFFICSERVER_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;

class TrafficEvent;

class TrafficServer : public cSimpleModule
{
  private:
    std::queue<TrafficEvent *> eventQueue; //queue stores traffic event packets
    cMessage *serviceTimer = nullptr; //a timer to tell processing time of a new event to itself dynamically (so it is a pointer)
    bool busy = false; //server busy flag

    //counters for event processing results
    int processedEvents = 0;
    int droppedEvents = 0;

    //to hold simulation measurements
    simsignal_t queueLengthSignal;
    simsignal_t endToEndDelaySignal;
    simsignal_t droppedEventsSignal;
    simsignal_t processedEventsSignal;

  protected:
    virtual void initialize() override; //register signals and process initial event
    virtual void handleMessage(cMessage *msg) override; //to handle a packet after the event is occurred depending on the timer
    void processNextEvent(); //to handle the next event in queue
    virtual ~TrafficServer(); //called when the sim is finished
};

#endif
