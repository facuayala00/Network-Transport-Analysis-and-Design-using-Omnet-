#ifndef TRANSPORTRX
#define TRANSPORTRX

#include <string.h>
#include <omnetpp.h>

#include "feedbackPkt_m.h"

using namespace omnetpp;


class TransportRx: public cSimpleModule {
private:
    cQueue buffer;
    cQueue bufferFeedback;

    cMessage *endServiceEvent;
    cMessage *feedbackEvent;

    simtime_t serviceTime;

    //stats
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;

    // treshold
    int treshold;
    void setTreshold(float);
    int getTreshold();

public:
    TransportRx();
    virtual ~TransportRx();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportRx);

TransportRx::TransportRx() {
    endServiceEvent = NULL;
}

TransportRx::~TransportRx() {
    cancelAndDelete(endServiceEvent);
}

void TransportRx::initialize() {
    buffer.setName("buffer");
    endServiceEvent = new cMessage("endService");
    feedbackEvent = new cMessage("endFeedback");

    //initialize
    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");

    setTreshold(0.75);
}

void TransportRx::finish() {
}

void TransportRx::setTreshold(float percentage) {
    const int bufferMaxSize = par("bufferSize").intValue();
    this.treshold = bufferMaxSize * percentage;
}

int TransportRx::getTreshold() {
    return this.treshold;
}

void TransportRx::handleMessage(cMessage *msg) {
    const int bufferMaxSize = par("bufferSize").intValue();

    if (msg->getKind() == 2) {
        bufferFeedback.insert(msg);

        if (!feedbackEvent->isScheduled()) {
            // If there are no messages being sent, send this one now
            scheduleAt(simTime() + 0, feedbackEvent);
        }
    }

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            // deTransportRx packet
            cPacket *pkt = (cPacket*) buffer.pop();
            // send packet
            send(pkt, "toApp");
            // start new service
            serviceTime = pkt->getDuration();
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }

    } else if (msg == feedbackEvent) { //

        if (!bufferFeedback.isEmpty()) {
            // Dequeue packet
            FeedbackPkt *pkt = (FeedbackPkt *)bufferFeedback.pop();

            // Send packet
            send(pkt, "toOut$o");
            scheduleAt(simTime() + pkt->getDuration(), feedbackEvent);
        }

    } else { //msg is normal

        if (buffer.getLength() >= bufferMaxSize) {
            // drop the packet
            delete msg;
            this->bubble("packet dropped");
            packetDropVector.record(1);
        }
        else if (buffer.getLength() > this->getTreshold()) { //threshold is met
            // we send feedback messages
            FeedbackPkt *fbkPkt = new FeedbackPkt();
            fbkPkt->setByteLength(20);
            fdbPkt->setKind(2);
            fdbPkt->setFullBufferR(true);
            send(fdbPkt, "toOut$o");

            bufferFeedback.insert(fdbPkt);
            if (!feedbackEvent->isScheduled()) {
                // If there are no messages being sent, send this one now
                scheduleAt(simTime() + 0, feedbackEvent);
            }

        }
        else {
            // enqueue the packet
            buffer.insert(msg);
            bufferSizeVector.record(buffer.getLength());
            // if the server is idle
            if (!endServiceEvent->isScheduled()) {
                // start the service
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }



#endif /* TransportRx */
