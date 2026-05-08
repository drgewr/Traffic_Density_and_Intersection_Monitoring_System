#include "TrafficSensors.h"
#include "TrafficEvent_m.h"

Define_Module(TrafficSensors);

void TrafficSensors::initialize()
{
    generatedSignal = registerSignal("generatedEvents");
    failureSignal = registerSignal("sensorFailures");

    generateTimer = new cMessage("generateTrafficEvent"); //timer to generate the new event

    scheduleNextTrafficEvent();
}

void TrafficSensors::handleMessage(cMessage *msg)
{
    if (msg == generateTimer) {
        generateTrafficEvent();
        scheduleNextTrafficEvent();
        return;
    }
}

void TrafficSensors::scheduleNextTrafficEvent()
{
    simtime_t nextTime = par("interArrivalTime").doubleValue(); //reads the interArrivalTime parameter from the .ned file
    scheduleAt(simTime() + nextTime, generateTimer);
}

void TrafficSensors::generateTrafficEvent()
{
    int sensorId = par("sensorId").intValue();
    int sensorType = par("sensorType").intValue();

    double meanVehicles = par("meanVehicles").doubleValue();
    double meanPedestrians = par("meanPedestrians").doubleValue();
    double meanQueueLength = par("meanQueueLength").doubleValue();

    double failureProb = par("failureProbability").doubleValue();
    double accidentProb = par("accidentProbability").doubleValue();

    bool failed = bernoulli(failureProb);

    TrafficEvent *event = new TrafficEvent("trafficEvent"); //because traffic event message types needs to be persistent and kept into heap

    event->setSensorId(sensorId);
    event->setEventType(sensorType);
    event->setSensorFailure(failed);
    event->setCreatedAt(simTime());

    // Default values for fields
    event->setVehicleCount(0);
    event->setPedestrianCount(0);
    event->setAccident(false);
    event->setMeasuredDensity(0);
    event->setQueueLength(0);

    // Traffic Density Sensor
    if (sensorType == 0) {
        int vehicles = poisson(meanVehicles);

        event->setVehicleCount(vehicles);
        event->setMeasuredDensity(vehicles);
    }
    // Incident Detection Sensor
    else if (sensorType == 1) {

        bool accident = uniform(0, 1) < accidentProb;

        event->setAccident(accident);
        event->setVehicleCount(poisson(meanVehicles));
    }
    // Pedestrian Event Sensor
    else if (sensorType == 2) {
        int pedestrians = poisson(meanPedestrians);

        event->setPedestrianCount(pedestrians);
    }
    // Queue Detection Sensor
    else if (sensorType == 3) {
        int q = poisson(meanQueueLength);

        event->setQueueLength(q);
        event->setVehicleCount(q);
    }

    emit(generatedSignal, 1); //emits one generated event

    if (failed) //generates a failure signal if sensor failed
        emit(failureSignal, 1);

    send(event, "out");
}

TrafficSensors::~TrafficSensors()
{
    cancelAndDelete(generateTimer);
}
