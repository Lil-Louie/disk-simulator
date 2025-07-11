#ifndef DISKSIM_X_PUQUEUE_H
#define DISKSIM_X_PUQUEUE_H

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "../ST_Queue/STQueueNode.h"

class Request;

class PUQueue : public Queue {
public:
    PUQueue() : head(nullptr), tail(nullptr), _size(0) {}

    void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) override;
    Request *getRequest() override;
    bool empty() override;
    void print() override;
    int size() const override;

    ~PUQueue() override;

private:
    STQueueNode *head;
    STQueueNode *tail;
    int _size;

    bool OnTheWay(Request *request, int cRWHeadTrack);
};

#endif // DISKSIM_X_PUQUEUE_H
