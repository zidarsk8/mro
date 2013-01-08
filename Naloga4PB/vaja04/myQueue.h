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

#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <omnetpp.h>
#include <string.h>

class myQueue : public cSimpleModule{
private:
	cQueue queue;
	//cMessage *endServiceMsg;
	int capacity, length, resources, processing;
	simtime_t serviceTime;
    simsignal_t serverCountSignal;
    simsignal_t waitTimeSignal;


	typedef std::list<cMessage *> jobsProcessingList;
	jobsProcessingList jobsProcessing;

public:
	myQueue();
	virtual ~myQueue();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int i, int p, int r);
};



#endif /* MYQUEUE_H_ */
