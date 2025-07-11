#ifndef DISKSIM_X_DISK_H
#define DISKSIM_X_DISK_H

#include <string>
#include <climits>  // for INT_MAX
#include "../CommonFiles/Request.hpp"

class EventQueue;
class Queue;

class Disk {
public:
    Disk(Queue *waitQueue, const std::string& diskName)
        : waitQueue{waitQueue}, busy{false}, diskName{diskName}, currentTime{0},
          curr_track{0}, curr_sector{0}, dest_track{0}, dest_sector{0},
          minRequest{INT_MAX}, maxRequest{0}, averageRequests{0.0}, totalRequests{0}, totalSamples{0} {}

    std::string getName() { return diskName; }

    void processRequest(EventQueue *eventQueue, Request *req);    
    void processDiskDone(EventQueue *eventQueue);
    int processTimer();

    double getCurrentTime() { return currentTime; }
    bool isBusy() { return busy; }

    int getMinRequest() { return minRequest; }
    int getMaxRequest() { return maxRequest; }
    double getAverageRequests() { return (totalSamples > 0) ? averageRequests / totalSamples : 0.0; }

    int getQueueLength();
    void printStats();

private:
    std::string diskName;

    Queue *waitQueue;
    bool busy;
    double currentTime;

    int curr_track;
    int dest_track;
    int curr_sector;
    int dest_sector;

    int minRequest;
    int maxRequest;
    double averageRequests;
    int totalRequests;
    int totalSamples;

    double accessTime();
    double distance(int curr_sector, int dest_sector);
    double rotdist(int curr_sector, int dest_sector);

    static int count;
};

#endif // DISKSIM_X_DISK_H
