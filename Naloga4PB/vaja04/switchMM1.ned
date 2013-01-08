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

package vaja04;

module switchMM1
{
    parameters:
        @display("i=block/routing;bgb=138,83");

    gates:
        input in;
        output out[];

    submodules:
        switch: mySwitch {
            @display("p=98,40");
        }
        myQueue: myQueue {
            @display("p=38,40");
            resources = 1;
            capacity = 100;
            serviceTime = 1ms; //izrabimo ze ustvarjen myQueue
        }
    connections:
  		in --> myQueue.in++;
        myQueue.out --> switch.in;
        switch.out++ --> out++;        
        switch.out++ --> out++;
        switch.out++ --> out++;
        switch.out++ --> out++;
}
