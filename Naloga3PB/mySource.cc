// Modeliranje racunalniskih omrezij
// Generator prometa

//
// generator prometa deluje tako, da si periodicno posilja sporocila, in sicer z intervalom, ki je dolocen z medprihodnim casom
// ko generator prometa dobi sporocilo, zgenerira izhodna sporocila, ki dolocajo opravila in jih razposlje v omrezje
//


#include "mySource.h"

Define_Module(mySource);	// makro, ki registrira modul

mySource::mySource() {
	generateJobMsg = NULL;
}

mySource::~mySource() {
	cancelAndDelete(generateJobMsg);
}

void mySource::initialize()
{
	generateJobMsg = new cMessage("generate");		// sporocilo, ki generatorju pove, naj zgenerira izhodna opravila
	startTime = par("startTime");					// zacetek generiranja (parameter)
    stopTime = par("stopTime");						// konec generiranja (parameter)
    numJobs = par("numJobs");						// koliko sporocil, ki dolocajo opravila naj se zgenerira naenkrat (parameter)
	maxJobs = par("maxJobs");						// maksimalno stevilo zgeneriranih opravil (parameter) - ko bo to stevilo dosezeno, bo generator ustavil generiranje opravil

    jobCounter = 0;		// stevec zgeneriranih opravil

    scheduleAt(startTime, generateJobMsg);			// generator zazenemo z zacetnim sporocilom - posljemo ga samemu sebi cez cas, ki je dolocen s parametrom startTime

    int P = par("interArrivalTime");
    EV << endl << "Cas med prihodi: " << P << endl; //to deluje zgolj ker imamo konstantne prihode
}

void mySource::handleMessage(cMessage *msg)
{
	// ce prispe sporocilo, ki generatorju pove, naj zgenerira nova opravila
    if (msg == generateJobMsg)
    {
    	// ali je norma dosezena?
    	if ((maxJobs < 0 || maxJobs > jobCounter) && (stopTime < 0 || stopTime > simTime()))
    	{
    		scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);	// najprej poskrbimo za to, da se bo cez interval, ki je dolocen z medprihodnim casom, zgeneriral nov niz opravil
			for (int i=0; i<numJobs; i++)			// potem zgeneriramo numJobs sporocil, ki predstavljajo opravila in jih razposljemo v omrezje
			{
				cMessage *job = new cMessage();
				send(job, "out");
				jobCounter++;
			}
			updateDisplay(jobCounter);
		}
    	// ce prispe nepredvideno sporocilo
		else
		{
			delete msg;
		}
    }
}

// metoda, ki izpise stevilo zgeneriranih sporocil v graficni vmesnik
void mySource::updateDisplay(int i)
{
    char buf[10];
    sprintf(buf, "%ld", (long) i);
    getDisplayString().setTagArg("t",0,buf);
}
