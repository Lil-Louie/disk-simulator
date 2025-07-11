#ifndef FCFS_QUEUE_FCFSQUEUE_HPP
#define FCFS_QUEUE_FCFSQUEUE_HPP

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "FCFSQueueNode.hpp"

class Request;

class FCFSQueue : public Queue {
public:
    FCFSQueue() : head(nullptr), tail(nullptr), _size(0) {}

    void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) override;
    Request *getRequest() override;
    bool empty() override;
    void print() override;
    int size() const override;

    ~FCFSQueue() override;

private:
    FCFSQueueNode *head;
    FCFSQueueNode *tail;
    int _size;
};

#endif // FCFS_QUEUE_FCFSQUEUE_HPP
