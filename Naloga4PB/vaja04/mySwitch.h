/*
 * mySwitch.h
 *
 *  Created on: 17. dec. 2012
 *      Author: Peter Benko
 */

#ifndef MYSWITCH_H_
#define MYSWITCH_H_

#include <omnetpp.h>
#include "myPacket.h"

class mySwitch : public cSimpleModule{

private:

public:

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* MYSWITCH_H_ */
