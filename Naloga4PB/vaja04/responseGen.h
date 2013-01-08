#ifndef RESPONSEGEN_H_
#define RESPONSEGEN_H_

#include <omnetpp.h>
#include "myPacket.h"

class responseGen : public cSimpleModule{
private:

    int packetLength;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

public:
    responseGen();
	virtual ~responseGen();
};

#endif
