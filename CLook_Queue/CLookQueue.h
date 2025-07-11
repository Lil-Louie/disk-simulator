#ifndef DISKSIM_X_CLOOKQUEUE_H
#define DISKSIM_X_CLOOKQUEUE_H

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "../ST_Queue/STQueueNode.h"

class Request;

class CLookQueue : public Queue {
public:
    CLookQueue() : head(nullptr), tail(nullptr), direction(0), currentTrack(0), _size(0) {}

    void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) override;
    Request *getRequest() override;
    bool empty() override;
    void print() override;
    int size() const  override;

    ~CLookQueue() override;

private:
    STQueueNode *head;
    STQueueNode *tail;
    int direction;
    int currentTrack;
    int _size;
};

#endif // DISKSIM_X_CLOOKQUEUE_H
