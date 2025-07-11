#ifndef DISKSIM_X_EVENTQUEUE_H
#define DISKSIM_X_EVENTQUEUE_H

#include "EventQueueNode.h"
#include "../CommonFiles/Queue.hpp"

class EventNode;

class EventQueue {
public:
    EventQueue(): head{nullptr}, tail{nullptr}, _currentTime{0} {}

    void addEvent( EventNode *newEvent);

    EventNode *getEvent();
    double getCurrentTime() { return head->getCurrentTime(); }
    virtual bool empty();
    virtual void print();
    virtual ~EventQueue();

private:
    EventNode *head, *tail;
    double _currentTime;
};


#endif //DISKSIM_X_EVENTQUEUE_H
