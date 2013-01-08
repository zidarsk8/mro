// Modeliranje racunalniskih omrezij
// Model terminatorja

#include "mySink.h"

Define_Module(mySink);


void mySink::initialize()
{
	sinked = 0;		// stevec terminiranih opravil inicializiramo na 0
}

// metoda se sprozi, ko prispe sporocilo, ki predstavlja opravilo, ki ga bomo terminirali
void mySink::handleMessage(cMessage *msg)
{
	sinked ++;
	delete msg;					// izbrisemo sprocilo, ki predstavlja prispelo opravilo
	updateDisplay(sinked);		// izpisemo stevilo terminiranih opravil v graficni vmesnik
}

void mySink::updateDisplay(int i)
{
    char buf[10];
    sprintf(buf, "%ld", (long) i);
    getDisplayString().setTagArg("t",0,buf);
}
