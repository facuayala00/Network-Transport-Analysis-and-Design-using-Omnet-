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

TransportTx::TransportTx() {
    endServiceEvent = NULL;
}

TransportTx::~TransportTx() {
    cancelAndDelete(endServiceEvent);
}

void TransportTx::initialize() {
    buffer.setName("transmisor status buffer");

    // Initialize timers
    lastCong = 0;

    // Initialize scalars
    contScalar = 0.0;

    // Initialize events
    endServiceEvent = new cMessage("endService");

    // Initialize stats
    bufferSizeVector.setName("bufferSize");
}

void TransportTx::finish() {
}


void TransportTx::sendPacket() {
    if (!buffer.isEmpty()) {
        // Dequeue packet
        cPacket *pkt = (cPacket *)buffer.pop();

        // Send packet
        send(pkt, "toOut$o");

        // Start new service when the packet is sent
        simtime_t serviceTime = pkt->getDuration();
        serviceTime = (serviceTime + (serviceTime * contScalar));
        scheduleAt(simTime() + serviceTime, endServiceEvent);
    }
}

void TransportTx::enqueueMessage(cMessage *msg) {
    if (buffer.getLength() >= par("bufferSize").intValue()) {
        // Drop the packet
        delete msg;

        // Animate loss
        this->bubble("packet dropped");
    } else {
        // Enqueue the packet
        buffer.insert(msg);

        if (!endServiceEvent->isScheduled()) {
            // If there are no messages being sent, send this one now
            scheduleAt(simTime() + 0, endServiceEvent);
        }
    }
}


void TransportTx::handleMessage(cMessage *msg) {
    // Record stats
    bufferSizeVector.record(buffer.getLength());

    if (simTime().dbl() - lastCong >= 0.2 && contScalar > 0.1) {
            contScalar -= 0.1;
        }

    if (msg->getKind() == 2) {
        //msg is a FeedbackPkt
        FeedbackPkt *feedbackPkt = (FeedbackPkt *)msg;

        if (feedbackPkt->getFullBufferQueue() || feedbackPkt->getFullBufferR()) {
            if (simTime().dbl() - lastCong >= 0.1) {
                contScalar += 0.1;
                lastCong = simTime().dbl();
            }
        }

        delete msg;
    } else {
        // msg is a data packet
        if (msg == endServiceEvent) {
            // If msg is signaling an endServiceEvent
            sendPacket();
        } else {
            // If msg is a incoming massage
            enqueueMessage(msg);
        }
    }

}


#endif /* Transporte Tx */
