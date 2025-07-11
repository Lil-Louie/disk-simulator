#ifndef DISKSIM_X_STQUEUE_HPP
#define DISKSIM_X_STQUEUE_HPP

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "STQueueNode.h"

class Request;

class STQueue : public Queue {
public:
    STQueue() : head(nullptr), tail(nullptr), _size(0) {}

    void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) override;
    Request *getRequest() override;
    bool empty() override;
    void print() override;
    int size() const override;

    ~STQueue() override;

private:
    STQueueNode *head, *tail;
    int _size;
};

#endif // DISKSIM_X_STQUEUE_HPP
