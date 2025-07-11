#include <iostream>
#include "EventQueue.h"
#include "EventQueueNode.h"

void EventQueue::addEvent( EventNode *newEvent ) {
    if ( empty() ){
        head = tail = newEvent;
    } else if ( newEvent->getCurrentTime() < head->getCurrentTime() ){
        newEvent->setNext( head );
        head = newEvent;
    } else if ( newEvent->getCurrentTime() >= tail->getCurrentTime() ) {
        tail->setNext( newEvent );
        tail = newEvent;
    } else {
        EventNode *cur = head;
        while ( newEvent->getCurrentTime() >= cur->next()->getCurrentTime() ) {
            cur = cur->next();
        }
        newEvent->setNext( cur->next() );
        cur->setNext( newEvent );
    }
}

EventNode *EventQueue::getEvent() {
    if (empty()) {
        std::cout << "Calling EventQueue::getEvent() on an empty queue. Terminating...\n";
        exit(1);
    }
    EventNode *node = head;
    head = node->next();
    if (head == nullptr)
        tail = nullptr;
    return node;
}

bool EventQueue::empty() {
    return head == nullptr;
}

void EventQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->print();
}

EventQueue::~EventQueue() {
    while( head != nullptr ) {
        EventNode *node = head;
        head = node->next();
        delete node;
    }
}


