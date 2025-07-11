#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"

void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode* newNode = new STQueueNode(request);

    if (empty()) {
        head = tail = newNode;
    } else {
        STQueueNode* cur = head;
        STQueueNode* lastSameTrack = nullptr;

        // Traverse to find the last node with the same track
        while (cur != nullptr) {
            if (cur->request()->track() == request->track()) {
                lastSameTrack = cur;
            }
            cur = cur->next();
        }

        if (lastSameTrack != nullptr) {
            // Insert after the last node of the same track
            newNode->next(lastSameTrack->next());
            lastSameTrack->next(newNode);
            if (lastSameTrack == tail) tail = newNode;
        } else {
            // No match, insert at end
            tail->next(newNode);
            tail = newNode;
        }
    }

    _size++;
}

Request* STQueue::getRequest() {
    if (empty()) {
        std::cerr << "Calling STQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }

    STQueueNode* node = head;
    Request* request = head->request();
    head = head->next();
    if (head == nullptr) tail = nullptr;

    delete node;
    _size--;
    return request;
}

bool STQueue::empty() {
    return head == nullptr;
}

void STQueue::print() {
    STQueueNode* cur = head;
    while (cur != nullptr) {
        cur->request()->print();
        cur = cur->next();
    }
}

int STQueue::size() const {
    return _size;
}

STQueue::~STQueue() {
    while (head != nullptr) {
        STQueueNode* node = head;
        head = node->next();
        delete node;
    }
}
