//
//
#include "STQueueNode.h"

class Request;
class FCFSQueue;

STQueueNode::STQueueNode(Request *req) : _request(req),  _next(nullptr)  {}

STQueueNode *STQueueNode::next() {
    return _next;
}

void STQueueNode::next(STQueueNode *node) {
    _next = node;
}

Request *STQueueNode::request() {
    return _request;
}


