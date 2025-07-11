//
// Created by Luis Galvez on 11/16/23.
//

#ifndef DISKSIM_X_STQUEUENODE_H
#define DISKSIM_X_STQUEUENODE_H

#include "../CommonFiles/Request.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"


class Request;
class FCFSQueue;

class STQueueNode {
public:
    STQueueNode(Request *req);
    STQueueNode *next();
    void next( STQueueNode *node );
    Request *request();
    ~STQueueNode() = default;

private:
    STQueueNode *_next;
    Request *_request;
};

#endif //DISKSIM_X_STQUEUENODE_H
