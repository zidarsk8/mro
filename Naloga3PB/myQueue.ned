//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package vaja02;

simple myQueue
{
   parameters:
        @display("i=block/queue");
        
        @statistic[dropped](title="drop event";record=vector,count;interpolationmode=none);
        @statistic[waitTime](title="queueing time at dequeue";record=vector,mean,max;unit=s;interpolationmode=none);
        @statistic[serverCount](title="servers in use";record=vector,mean,max;interpolationmode=none);
        
        int capacity = default(-1);   
        int serverCount = default(5);
        volatile double serviceTime @unit(s) = truncnormal(8s,2s);
      
    gates:
        input in[];
        output out;
}
