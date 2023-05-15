#ifndef TRANSPORTTX
#define TRANSPORTTX

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;
#include "FeedbackPkt_m.h"

class TransportTx : public cSimpleModule {
  private:
    // data
    cQueue buffer;

    // events
    cMessage *endServiceEvent;

    // temporizers
    double lastCong;

    // scalars
    double contScalar;

    // stats
    cOutVector bufferSizeVector;

    // functions
    void sendPacket();
    void enqueueMessage(cMessage *msg);
    void handleCongestion();
    void handleFlow();
    void controlSendRate();

  public:
    TransportTx();
    virtual ~TransportTx();

  protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportTx);



#endif /* Transporte Tx */
