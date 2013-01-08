// Modeliranje racunalniskih omrezij
// Model M/M/1 sistema

#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <omnetpp.h>
#include "deque"
using namespace std;

class myQueue : public cSimpleModule{
private:

    // statistics
    simsignal_t droppedSignal;
    simsignal_t waitTimeSignal;
    simsignal_t serverCountSignal;

	cQueue queue;

	deque<cMessage*> currentJob;			//array trenutno izvajajoèih opravil
	deque<cMessage*> endServiceMsg;		// naredimo array ki hrani vsa prekinitvena sporoèila

	int capacity, length, serverCount;			// capacity = kapaciteta cakalne vrste (parameter), length = trenutna dolzina cakalne vrste, serverCount = stevilo serverjev (c)
	simtime_t serviceTime;			// cas procesiranja (parameter)

	deque<int> idleServers;

public:
	myQueue();
	virtual ~myQueue();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int i, int S, int A);
};
#endif /* MYQUEUE_H_ */
