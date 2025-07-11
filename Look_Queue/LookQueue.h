#ifndef DISKSIM_X_LOOKQUEUE_H
#define DISKSIM_X_LOOKQUEUE_H

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "../ST_Queue/STQueueNode.h"

class Request;

class LookQueue : public Queue {
public:
    LookQueue() : head(nullptr), tail(nullptr), inward(false), currentTrack(0), _size(0) {}

    void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) override;
    Request *getRequest() override;
    bool empty() override;
    void print() override;
    int size() const override;

    ~LookQueue() override; 

private:
    STQueueNode *head, *tail;
    bool inward;
    int currentTrack;
    int _size;
};

#endif // DISKSIM_X_LOOKQUEUE_H
