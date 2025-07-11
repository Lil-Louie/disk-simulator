#include "CLookQueue.h"

void CLookQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode *rNode = new STQueueNode(request);

    if (empty()) {
        head = tail = rNode;
        direction = (cRWHeadTrack < request->track()) ? 1 : (cRWHeadTrack > request->track() ? -1 : 0);
            _size++;
        return;
    }

    // Insert in sorted order
    STQueueNode *cur = head;
    STQueueNode *prev = nullptr;
    while (cur != nullptr && request->track() > cur->request()->track()) {
        prev = cur;
        cur = cur->next();
    }

    if (prev == nullptr) { // insert at head
        rNode->next(head);
        head = rNode;
    } else if (cur == nullptr) { // insert at tail
        tail->next(rNode);
        tail = rNode;
    } else {
        prev->next(rNode);
        rNode->next(cur);
    }

    // Set direction if not set
    if (direction == 0) {
        direction = (cRWHeadTrack < request->track()) ? 1 : -1;
    }
    _size++;
}

Request *CLookQueue::getRequest() {
    if (empty()) {
        std::cerr << "Calling getRequest() on empty CLookQueue\n";
        exit(1);
    }

    STQueueNode *prev = nullptr;
    STQueueNode *cur = head;
    STQueueNode *best = nullptr;

    while (cur != nullptr) {
        int diff = cur->request()->track() - currentTrack;
        if ((direction == 1 && diff >= 0) || (direction == -1 && diff <= 0)) {
            best = cur;
            break;
        }
        prev = cur;
        cur = cur->next();
    }

    // If no valid request in current direction, reverse direction and try again
    if (best == nullptr) {
        direction = -direction;
        return getRequest();
    }

    // Remove best node from list
    if (best == head) {
        head = head->next();
        if (head == nullptr) tail = nullptr;
    } else {
        prev->next(best->next());
        if (best == tail) tail = prev;
    }

    Request *req = best->request();
    currentTrack = req->track();
    delete best;
    _size--;
    return req;
}

bool CLookQueue::empty() {
    return head == nullptr;
}

void CLookQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

int CLookQueue::size() const {
    return _size;
}

CLookQueue::~CLookQueue() {
    while( head != nullptr ) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
