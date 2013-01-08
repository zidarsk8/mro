#include "mySource.h"

Define_Module(mySource);

mySource::mySource() {
	generateJobMsg = NULL;
}

mySource::~mySource() {
	cancelAndDelete(generateJobMsg);
}

void mySource::initialize()
{
	generateJobMsg = new cMessage("generate");
	startTime = par("startTime");	// zacetek generiranja
    stopTime = par("stopTime");		// konec generiranja
    numJobs = par("numJobs");		// koliko se jih zgenerira naenkrat
    maxJobs = par("maxJobs");		// maksimalno stevilo zgeneriranih

    serverProb1 = par("serverProb1");   //verjetnosti za serverje
    serverProb2 = par("serverProb2");
    serverProb3 = par("serverProb3");


    packetLength = par("requestBytePacketLength");

    jobCounter = 0;

    scheduleAt(startTime, generateJobMsg);
}

void mySource::handleMessage(cMessage *msg)
{
    if (msg == generateJobMsg)
    {
    	if ((maxJobs < 0 || maxJobs > jobCounter) && (stopTime < 0 || stopTime > simTime()))
    	{
    		scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);
			for (int i=0; i<numJobs; i++)
			{
				myPacket *packet = new myPacket();

				packet->setKind(0);
				packet->setByteLength(packetLength);

				/**
				 *
				 * TU NASTAVITE CILJNI NASLOV, KI GA BO USMERJEVALNIK UPOSTEVAL PRI POSILJANJU NA IZHOD
				 *
				 */

				double rnd = dblrand();
				if (rnd < serverProb1) packet->setAddress(1);
				else if (rnd < (serverProb1 + serverProb2) ) packet->setAddress(2);
				else packet->setAddress(3);

				//--------------------------------------------------------


				send(packet, "out");

				jobCounter++;
			}
			updateDisplay(jobCounter);
		}
		else
		{
			delete msg;
		}
    }
}

void mySource::updateDisplay(int i)
{
    char buf[10];
    sprintf(buf, "%ld", (long) i);
    getDisplayString().setTagArg("t",0,buf);
}
