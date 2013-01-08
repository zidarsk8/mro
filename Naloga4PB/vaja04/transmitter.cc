#include "transmitter.h"

Define_Module(transmitter);

transmitter::transmitter() {
	channelFreeMsg = NULL;
}

transmitter::~transmitter() {
	cancelAndDelete(channelFreeMsg);
}

void transmitter::initialize()
{
	txQueue.setName("txQueue");

	channelFreeMsg = new cMessage("channel free");	// sporocilo o prostem kanalu

    received = 0;
    sent = 0;
    capacity = par("capacity");
}

void transmitter::handleMessage(cMessage *msg)
{
	// ce prispe sporocilo, ki oddajniku pove, da je kanal prost
   	if (msg == channelFreeMsg)
   	{
		// vzemi iz vrste prvi paket in ga poslji na izhodno povezavo
   		myPacket *packet = check_and_cast<myPacket *>(txQueue.pop());
   		send(packet, "out");

   		// ce cakalna vrsta ni prazna, se bo ko se kanal sprosti spet posiljalo!
   		if (!txQueue.empty())
   		{
   			cChannel *txChannel = gate("out")->getTransmissionChannel();
   			simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
   			scheduleAt(txFinishTime, channelFreeMsg);

   			sent ++;
    	}
   	}
    else // prejeli smo nov paket
    {
    	myPacket *packet = check_and_cast<myPacket *>(msg);

    	received ++;

    	cChannel *txChannel = gate("out")->getTransmissionChannel();
   		simtime_t txFinishTime = txChannel->getTransmissionFinishTime();

   		if (txFinishTime <= simTime())
   		{
   			// channel free; send out packet immediately
   			send(packet, "out");
   			sent++;
   		}
   		else
   		{
   			// ali je v cakalni vrsti prostor?

   			if ((capacity > 0) && (txQueue.length() >= capacity))
   			{
   				delete(packet);
   				EV << "transmitting buffer capacity exceeded - packet dropped!";
   				emit(transmitErrorSignal,1);
   			}
   			else
   			{
				// store packet and schedule timer; when the timer expires,
				// the packet should be removed from the queue and sent out
				if (txQueue.empty())	// ce je cakalna vrsta prazna, to pomeni da trenutno ne cakamo na nobeno sporocilo o prosti liniji
				{
					scheduleAt(txFinishTime, channelFreeMsg);
				}

				txQueue.insert(packet);
   			}
   		}
    }

	updateDisplay(received, sent);
}


void transmitter::updateDisplay(int r, int s)
{
    char buf[35];
    sprintf(buf, "sent = %ld, received = %ld", (long) r, (long) s);
    getDisplayString().setTagArg("t",0,buf);
}
