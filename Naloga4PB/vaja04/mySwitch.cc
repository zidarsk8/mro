/*
 * mySwitch.cc
 *
 *  Created on: 17. dec. 2012
 *      Author: Peter Benko
 */
#include "mySwitch.h"

Define_Module(mySwitch);

void mySwitch::initialize()
{

}

void mySwitch::handleMessage(cMessage *msg)
{
    myPacket *packet = check_and_cast<myPacket *>(msg);
    send(packet,"out", packet->getAddress());
}

