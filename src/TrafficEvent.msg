//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOU ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

packet TrafficEvent
{
    int sensorId;
    int eventType; // 0 - Traffic Density, 1 - Incident Detection, 2 - Pedestrian Event, 3 - Queue Detection
    int vehicleCount;
    int pedestrianCount;
    bool accident;
    bool sensorFailure;
    int measuredDensity;
    int queueLength;
    simtime_t createdAt;
}