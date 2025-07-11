#ifndef DISKSIM_X_EVENTQUEUENODE_H
#define DISKSIM_X_EVENTQUEUENODE_H

#include "EventQueueNode.h"
#include "RequestEvent.h"
#include "TimerEvent.h"
#include "DiskDoneEvent.h"

class TimerEvent;
class RequestEvent;
class DiskDoneEvent;

class EventNode {
public:
    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),
                 isTimer(false), isRequest(false), isDDone(false), _next{nullptr} {}

    explicit EventNode( TimerEvent *timer ) : timerEvent{timer}, requestEvent{nullptr}, ddoneEvent{nullptr},
                                     isTimer{true}, isRequest{false}, isDDone{false}, _next{nullptr}, currentTime{ timer->getcurrentTime() } {}

    explicit EventNode( RequestEvent *request ) : timerEvent{nullptr}, requestEvent{request}, ddoneEvent{nullptr},
                                         isTimer{false}, isRequest{true}, isDDone{false}, _next{nullptr}, currentTime { request->getcurrentTime() }  {}

    explicit EventNode ( DiskDoneEvent *ddone ) : timerEvent{nullptr}, requestEvent{nullptr}, ddoneEvent{ddone},
                                         isTimer{false}, isRequest{false}, isDDone{true}, _next{nullptr}, currentTime{ ddone->getcurrentTime() } {}

    TimerEvent *getTimer() { return timerEvent; }
    RequestEvent *getRequest() { return requestEvent; }
    DiskDoneEvent *getDiskDone() { return ddoneEvent; }

    bool isTimerEvent() const { return isTimer; }
    bool isRequestEvent() const { return isRequest; }
    bool isDiskDoneEvent() const { return isDDone; }
    
    EventNode *next() { return _next; }
    void setNext(EventNode *pNode) { _next = pNode; }
    void print() { requestEvent->print(); }
    double getCurrentTime() const { return currentTime; }
private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;
    EventNode *_next;
    bool isTimer, isRequest, isDDone;
    double currentTime;
};

#endif //DISKSIM_X_EVENTQUEUENODE_H
