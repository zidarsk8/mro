package vaja04;

simple myQueue
{
   parameters:
        @display("i=block/queue");
        @statistic[serverCount](title="servers in use";record=vector,mean,max;interpolationmode=none);
        @statistic[waitTime](title="queueing time at dequeue";record=vector,mean;unit=s;interpolationmode=none);
        
        
        int capacity = default(-1);   
        int resources = default(1);
        volatile double serviceTime @unit(s) = default(truncnormal(8s,2s));   
      
    gates:
        input in[];
        output out;
}
