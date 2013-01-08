// Modeliranje racunalniskih omrezij
// Model terminatorja

#ifndef MYSINK_H_
#define MYSINK_H_

#include <omnetpp.h>

class mySink : public cSimpleModule{
public:

protected:
	int sinked;		// stevec terminiranih opravil
	virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int i);

};

#endif /* MYSINK_H_ */
