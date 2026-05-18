package trafficdensityandintersectionmonitoringsystem;

simple TrafficServer
{
    parameters:
        volatile double serviceTime @unit(s) = default(exponential(105s)); //volatile because interarrival time needs to be recalculated differently for each read
        int queueCapacity = default(10); //defined referring to fig 16 in the report as average of 10 dropped events per sensor

        @signal[queueLength](type=long); //how many events are waiting in queue
        @signal[endToEndDelay](type=simtime_t); //time passed between each event start and end time
        @signal[droppedEvents](type=long); //events can not be processed by server (full)
        @signal[processedEvents](type=long); //events can be processed by server

		//Sim statistics for the server 
        @statistic[queueLength](title="Queue Length"; source=queueLength; record=vector,mean,stats);
        @statistic[endToEndDelay](title="End-to-End Delay"; source=endToEndDelay; record=vector,mean,stats);
        @statistic[droppedEvents](title="Dropped Events"; source=droppedEvents; record=count,mean,stats);
        @statistic[processedEvents](title="Processed Events"; source=processedEvents; record=count,mean,stats);

		//Default icon for server
        @display("i=device/server");
    gates:
        input in[];
}