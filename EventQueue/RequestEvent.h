#ifndef DISKSIM_X_REQUESTEVENT_H
#define DISKSIM_X_REQUESTEVENT_H

#include <iostream>
#include "../CommonFiles/Request.hpp"

class RequestEvent {
public:
    RequestEvent(Request *req): currentTime{req->time()}, track{req->track()}, sector{req->sector()}, request{req} {}
    Request *getRequest() { return request; }
    double getcurrentTime() const { return currentTime; }
    int getTrack() const { return track; }
    int getSector() const { return sector; }
    void print() { std::cout << "Arrival Time: " << getcurrentTime() << " Track: " << getTrack() << " Sector: " << getSector() << std::endl; }
private:
    Request *request;
    double currentTime;
    int track;
    int sector;
};

#endif //DISKSIM_X_REQUESTEVENT_H
