#include "LookQueue.h"

class PUQueue;
void LookQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode *rNode = new STQueueNode(request);

    if (empty()) {
        head = tail = rNode;
        inward = cRWHeadTrack > request->track();  // inward if we are higher than the new request
    } else {
        STQueueNode *cur = head;
        STQueueNode *prev = nullptr;

        while (cur && request->track() > cur->request()->track()) {
            prev = cur;
            cur = cur->next();
        }

        if (!prev) { // Insert at head
            rNode->next(head);
            head = rNode;
        } else if (!cur) { // Insert at tail
            tail->next(rNode);
            tail = rNode;
        } else { // Insert in middle
            prev->next(rNode);
            rNode->next(cur);
        }

        // Only set direction if it was undefined (queue was empty before)
        if (_size == 0) {
            inward = cRWHeadTrack > request->track();
        }
    }

    _size++;
}



Request *LookQueue::getRequest() {
    if (empty()) {
        std::cerr << "Calling LookQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }

    STQueueNode *prev = nullptr;
    STQueueNode *cur = head;
    STQueueNode *best = nullptr;

    while (cur) {
        int diff = cur->request()->track() - currentTrack;
        if ((inward && diff <= 0) || (!inward && diff >= 0)) {
            best = cur;
            break;
        }
        prev = cur;
        cur = cur->next();
    }

    if (!best) {
        // Flip direction and search again without recursion
        inward = !inward;
        prev = nullptr;
        cur = head;

        while (cur) {
            int diff = cur->request()->track() - currentTrack;
            if ((inward && diff <= 0) || (!inward && diff >= 0)) {
                best = cur;
                break;
            }
            prev = cur;
            cur = cur->next();
        }

        if (!best) {
            std::cerr << "No request found in either direction. Exiting.\n";
            exit(1);
        }
    }

    // Remove best from list
    if (best == head) {
        head = head->next();
        if (!head) tail = nullptr;
    } else {
        prev->next(best->next());
        if (best == tail) tail = prev;
    }

    Request* req = best->request();
    currentTrack = req->track();
    delete best;
    _size--;
    return req;
}




bool LookQueue::empty() {
    return head == nullptr;
}

void LookQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();

}

int LookQueue::size() const {
    return _size;
}

LookQueue::~LookQueue() {
    while( head != nullptr ) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
