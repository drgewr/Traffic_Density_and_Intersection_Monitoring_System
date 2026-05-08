package trafficdensityandintersectionmonitoringsystem;

simple TrafficSensors
{
    parameters:
        int sensorId = default(0);
        int sensorType = default(0); // 0 - Traffic Density, 1 - Incident Detection, 2 - Pedestrian Event, 3 - Queue Detection

        volatile double interArrivalTime @unit(s) = default(exponential(5s)); //volatile because the value is recalculated everytime it is read, unit is seconds

		//these are defined as double for count variation for each event 
        double meanVehicles = default(12);
        double meanPedestrians = default(3);
        double meanQueueLength = default(8);

        double failureProbability = default(0.02);
        double accidentProbability = default(0.05);

		//I want to define default sensor icon as ap
        @display("i=device/accesspoint");
    gates:
        output out;
}