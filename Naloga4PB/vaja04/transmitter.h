
#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <omnetpp.h>
#include "myPacket.h"

class transmitter : public cSimpleModule{
private:
    simsignal_t transmitErrorSignal;
	int received, sent, capacity;
	cQueue txQueue;
	cMessage *channelFreeMsg;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int r, int s);


public:
	transmitter();
	virtual ~transmitter();
};

#endif /* transmitter_H_ */
