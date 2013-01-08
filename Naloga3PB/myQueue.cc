// Modeliranje racunalniskih omrezij
// Model M/M/1 sistema

#include "myQueue.h"

Define_Module(myQueue);		// makro, ki registrira modul

myQueue::myQueue() {

}

myQueue::~myQueue() {
    currentJob.clear();
    endServiceMsg.clear();
}

// inicializacijska metoda
void myQueue::initialize()
{
    droppedSignal = registerSignal("dropped");
    waitTimeSignal = registerSignal("waitTime");
    serverCountSignal = registerSignal("serverCount");


    capacity = par("capacity");				// kapaciteta cakalne vrste
    serviceTime = par("serviceTime");		// cas procesiranje
    queue.setName("queue");					// opcijsko lahko cakalni vrsti dolocimo ime
    length = 0;								// na zacetku je cakalna vrsta prazna
    serverCount = par("serverCount");

    EV << endl << "Stevilo serverjev: " << serverCount << endl;

    for (int i=0 ; i < serverCount; ++i)
    {
        cMessage *msg = new cMessage("end");   // sporocilo, ki ga bo modul posiljal samemu sebi - modul si ga interpretira kot konec procesiranja trenutnega opravila
        msg->setKind(i);

        endServiceMsg.push_back(msg);

        idleServers.push_back(i);
        currentJob.push_back(NULL); // zaenkrat je job tega serverja NULL
    }

    emit(droppedSignal, 0);
    emit(waitTimeSignal,0);
    emit(serverCountSignal,0);


}


// metoda, ki se klice ob sprejemu sporocila
// imamo dva tipa sporocil:
//   - sporocila, ki pridejo od zunaj in predstavljajo opravila, ki jih mora M/M/1 sistem sprocesirati
//   - sporocila, ki jih modul poslje samemu sebi in pomenijo konec procesiranja trenutnega opravila
void myQueue::handleMessage(cMessage *msg)
{
	// ali je prislo sporocilo o koncu procesiranja trenutnega opravila?
	if (strcmp(msg->getName(), "end") == 0 )
	    {
	        int ID=msg->getKind();
	        send(currentJob[ID], "out");	    // trenutno opravilo je obdelano, zato ga posljemo skozi izhodna vrata naprej v omrezje

	        if (queue.empty())			        // ce je cakalna vrsta prazna, potem v izvajanje ne moremo vzeti nobenega opravila
	        {
	        	currentJob[ID]= NULL;
	        	idleServers.push_back(ID);      //server dodamo med neaktivne
	        }

	        else						        // ce cakalna vrsta ni prazna, v izvajajnje vzamemo naslednje opravilo v cakalni vrsti
	        {
	        	// modul poslje sporocilo samemu sebi, ki ga bo obvestilo, da je izvajanja opravila NA DOLOCENEM SERVERJU konec
	        	// sporocilo bo prispelo cez cas, ki je dolocen s parametrom serviceTime

	            scheduleAt( simTime()+serviceTime, endServiceMsg[ID] );     //schedulamo endServiceMessage za server st. ID
	            currentJob[ID] = check_and_cast<cMessage *>(queue.pop());	// v spremenljivko currentJob ZA SERVER ID shranimo trenutno opravilo
	        	EV << "Cakalni cas:" << simTime() - currentJob[ID]->getTimestamp() << " s" << "V vrsti: " << length;		// v konzolo izpisemo cas, ki ga je opravilo prezivelo v cakalni vrsti
	        	emit(waitTimeSignal, simTime() - currentJob[ID]->getTimestamp());

	        	length--;				// cakalna vrsta se je skrajsala za 1
	        }

	    }
		// ali je skozi vhodna vrata prislo novo opravilo, ki ga mora M/M/1 sistem obdelati?
	    else
	    {
	    	cMessage *job = msg;

	    	// v primeru, da v obdelavi trenutno ni nobenega opravila, lahko zacnemo s procesiranja prispelega opravila
	    	if (idleServers.size() > 0)
	        {
	    	    int ID=idleServers.front(); //najdemo prvi prost server in ga vzamemo iz prostih
	    	    idleServers.pop_front();

	        	scheduleAt( simTime()+serviceTime, endServiceMsg[ID] ); // modul poslje sporocilo samemu sebi, ki ga bo obvestilo, da je izvajanja opravila konec

	        	currentJob[ID] = job;									// v spremenljivko currentJob z IDjem SERVERJA shranimo prispelo opravilo

	        	EV << "Cakalni cas: 0 s";
	        	emit(waitTimeSignal,0);
	        }

	    	// v primeru, da procesna enota ni prosta, opravilo poskusimo shraniti v cakalno vrsto
	    	else
	        {
	            // ali je cakalna vrsta presegla svojo kapaciteto?
	            if (capacity >=0 && length >= capacity)
	            {
	                // ce v cakalni vrsti ni prostora, opravilo zavrzemo
                    delete job;
                    emit(droppedSignal, 1);

	            }
	            else
	            {
	            	// sicer opravilo shranimo v cakalno vrsto
	            	job->setTimestamp();	// s pomocjo TimeStampa bomo lahko izmerili cas, ki ga je opravilo prezivelo v cakalni vrsti
	            	queue.insert( job );	// vstavljanje v vrsto
	            	length++;				// dolzina cakalne vrste se je povecala
	            }
	        }
	    }

    emit(serverCountSignal,serverCount - idleServers.size());

	int S = serverCount-idleServers.size();
	int A = serverCount;
	updateDisplay( length, S , A);		// zavoljo testiranja prikazujemo stevilo aktivnih serverjev
}

void myQueue::updateDisplay(int i, int S, int A)
{
    char buf[15];
    sprintf(buf, "Q_len:%ld,Used:%ld/%ld", (long) i,(long) S,(long) A);
    getDisplayString().setTagArg("t",0,buf);
}
