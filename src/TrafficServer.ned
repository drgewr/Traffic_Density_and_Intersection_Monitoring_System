package trafficdensityandintersectionmonitoringsystem;

simple TrafficServer
{
    parameters:
        volatile double serviceTime @unit(s) = default(exponential(2s)); //volatile because interarrival time needs to be recalculated differently for each read
        int queueCapacity = default(100); //defined randomly

        @signal[queueLength](type=long); //how many events are waiting in queue
        @signal[endToEndDelay](type=simtime_t); //time passed between each event start and end time
        @signal[droppedEvents](type=long); //events can not be processed by server (full)
        @signal[processedEvents](type=long); //events can be processed by server

		//Sim statistics for the server 
        @statistic[queueLength](title="Queue Length"; source=queueLength; record=vector,mean,max);
        @statistic[endToEndDelay](title="End-to-End Delay"; source=endToEndDelay; record=vector,mean,stats);
        @statistic[droppedEvents](title="Dropped Events"; source=droppedEvents; record=count);
        @statistic[processedEvents](title="Processed Events"; source=processedEvents; record=count);

		//Default icon for server
        @display("i=device/server");
    gates:
        input in[];
}