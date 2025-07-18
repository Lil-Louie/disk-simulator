//
//

#ifndef QUEUE_HPP
#define QUEUE_HPP
class Request;

class Queue {

public:
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) = 0;
    virtual Request *getRequest() = 0;
    virtual bool empty() = 0;
    virtual void print() = 0;
    virtual int size() const = 0;
    virtual ~Queue() {}

};

#endif // QUEUE_HPP
