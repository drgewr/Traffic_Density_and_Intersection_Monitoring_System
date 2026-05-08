# Traffic Density and Intersection Monitoring System

## Requirements
This project requires:
* OMNeT++ 6.0.x
* INET 4.4.x
* FLoRa 1.1.x

Recommended build order:
1. INET
2. FLoRa
3. This project

## Building Message Files
OMNeT++ message file is .msg file. In this project, it is located in:
`src/TrafficEvent.msg`

### Message Build Command
From the project root:
`cd src
opp_msgc TrafficEvent.msg`

## Building the Project from Terminal
From the project root:
`make MODE=debug all`

## Running the Simulation from OMNeT++ IDE
Open:
`simulations/omnetpp.ini`
Right click omnetpp.ini
→ Run As
→ OMNeT++ Simulation

The simulation uses the network defined in:
`simulations/TrafficNetwork.ned`
and configured by:
`simulations/omnetpp.ini`

## Simulation Output
OMNeT++ creates result files under:
`simulations/results/`
