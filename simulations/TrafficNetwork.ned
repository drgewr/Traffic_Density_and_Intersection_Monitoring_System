package trafficdensityandintersectionmonitoringsystem.simulations;

import trafficdensityandintersectionmonitoringsystem.TrafficSensors;
import trafficdensityandintersectionmonitoringsystem.TrafficServer;

network TrafficNetwork
{
    parameters:
        int numSensors = default(4); //we have 4 sensors

    submodules:
        sensor[numSensors]: TrafficSensors {
            parameters:
                sensorId = index;
                sensorType = index;
                @display("p=100,100,row,150;i=device/accesspoint");
        }

        server: TrafficServer {
            @display("p=380,320;i=device/server");
        }

    connections:
        for i=0..numSensors-1 {
            sensor[i].out -->  server.in++; //sensor to server
        }
}