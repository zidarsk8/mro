#include "receiver.h"

Define_Module(receiver);

receiver::receiver() {

}

receiver::~receiver() {

}

void receiver::initialize()
{
	received = 0;
    sent = 0;

    travelTimeSignal = registerSignal("travelTime");
    transmitErrorSignal = registerSignal("transmitError");
}

void receiver::handleMessage(cMessage *msg)
{
	myPacket *packet = check_and_cast<myPacket *>(msg);
	emit(travelTimeSignal, packet->getDuration());

    if (packet->hasBitError())
    {
    	EV << "! paket z napako";
    	emit(transmitErrorSignal,1);
    }
    else
    {
    	received ++;
    }

    send(packet,"out");

	updateDisplay(received, sent);
}


void receiver::updateDisplay(int r, int s)
{
    char buf[35];
    sprintf(buf, "sent = %ld, received = %ld", (long) r, (long) s);
    getDisplayString().setTagArg("t",0,buf);
}
