#include "PUQueue.h"
#include <iostream>

void PUQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode *newNode = new STQueueNode(request);

    if (empty()) {
        head = tail = newNode;
    } else if (request->track() == cRWHeadTrack) {
        // Insert immediately after the current head
        newNode->next(head->next());
        head->next(newNode);
        if (head == tail) tail = newNode;
    } else if (OnTheWay(request, cRWHeadTrack)) {
        // Add to the front if the request is "on the way"
        newNode->next(head);
        head = newNode;
    } else {
        // Add to the end otherwise
        tail->next(newNode);
        tail = newNode;
    }

    _size++;
}

Request *PUQueue::getRequest() {
    if (empty()) {
        std::cerr << "Calling PUQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }

    STQueueNode *node = head;
    Request *req = node->request();

    head = head->next();
    if (head == nullptr) tail = nullptr;

    delete node;
    _size--;
    return req;
}

bool PUQueue::empty() {
    return head == nullptr;
}

void PUQueue::print() {
    for (auto cur = head; cur; cur = cur->next()) {
        cur->request()->print();
    }
}

bool PUQueue::OnTheWay(Request *request, int cRWHeadTrack) {
    return (request->track() < head->request()->track() && request->track() > cRWHeadTrack) ||
           (request->track() > head->request()->track() && request->track() < cRWHeadTrack);
}

int PUQueue::size() const {
    return _size;
}

PUQueue::~PUQueue() {
    while (head != nullptr) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
