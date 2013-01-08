
#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <omnetpp.h>
#include "myPacket.h"

class receiver : public cSimpleModule{
private:
    simsignal_t transmitErrorSignal;
    simsignal_t travelTimeSignal;

	int received, sent;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int r, int s);


public:
	receiver();
	virtual ~receiver();
};

#endif /* receiver_H_ */
