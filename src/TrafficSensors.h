#ifndef __TRAFFIC_TRAFFICSENSORS_H_
#define __TRAFFIC_TRAFFICSENSORS_H_

#include <omnetpp.h>

using namespace omnetpp;

class TrafficSensors : public cSimpleModule
{
  private:
    cMessage *generateTimer = nullptr; //a timer to tell generate a new event to itself dynamically (so it is a pointer)

    // signals to calculate the sim statistics
    simsignal_t generatedSignal;
    simsignal_t failureSignal;

  protected:
    virtual void initialize() override; //register signals and schedules the initial event
    virtual void handleMessage(cMessage *msg) override; //if the module needs to receive a timer message, this method is called.
    virtual ~TrafficSensors(); //called at the finish of the simulation

    void scheduleNextTrafficEvent(); //schedule the next event considering the interarrival time parameter
    void generateTrafficEvent(); //generates a new event
};

#endif
