#ifndef MYSOURCE_H_
#define MYSOURCE_H_

#include <omnetpp.h>
#include "myPacket.h"

class mySource : public cSimpleModule{
private:
	cMessage *generateJobMsg;
	simtime_t startTime;
	simtime_t stopTime;
    int maxJobs, numJobs, jobCounter, packetLength;
    double serverProb1,serverProb2,serverProb3;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int i);

public:
	mySource();
	virtual ~mySource();
};

#endif /* MYSOURCE_H_ */
