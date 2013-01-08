#include "responseGen.h"

Define_Module(responseGen);

responseGen::responseGen() {

}

responseGen::~responseGen() {

}

void responseGen::initialize()
{
	packetLength = par("responseBytePacketLength");

}

void responseGen::handleMessage(cMessage *msg)
{
    delete msg;

	myPacket *packet = new myPacket();

	packet->setKind(0);
	packet->setByteLength(packetLength);
	packet->setAddress(0);

	send(packet, "out");
}

