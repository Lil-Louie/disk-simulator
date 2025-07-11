#include "../FCFS_Queue/FCFSQueueNode.hpp"
#include "../ST_Queue/STQueue.hpp"
#include "Disk.h"
#include "../EventQueue/EventQueue.h"
#include <cmath>  // for std::abs

int Disk::count = 0;

void Disk::processRequest(EventQueue *eventQueue, Request *req) {
    if (isBusy()) {
        waitQueue->addRequest(req, req->track(), req->sector());
    } else {
        busy = true;
        curr_track = dest_track;
        curr_sector = dest_sector;
        dest_track = req->track();
        dest_sector = req->sector();

        int completionTime = eventQueue->getCurrentTime() + accessTime();
        auto *diskDoneEvent = new DiskDoneEvent(completionTime, waitQueue, this);
        auto *dNode = new EventNode(diskDoneEvent);
        eventQueue->addEvent(dNode);
    }
}

void Disk::processDiskDone(EventQueue *eventQueue) {
    totalRequests++;

    if (!waitQueue->empty()) {
        Request *req = waitQueue->getRequest();

        // Update current position before issuing next request
        curr_track = dest_track;
        curr_sector = dest_sector;

        // Set next destination before scheduling access time
        dest_track = req->track();
        dest_sector = req->sector();

        busy = true;
        int completionTime = eventQueue->getCurrentTime() + accessTime();
        auto *diskDoneEvent = new DiskDoneEvent(completionTime, waitQueue, this);
        auto *dNode = new EventNode(diskDoneEvent);
        eventQueue->addEvent(dNode);
    } else {
        busy = false;
        curr_track = dest_track;
        curr_sector = dest_sector;
        currentTime = eventQueue->getCurrentTime();
    }

    // Update stats
    if (waitQueue) {
        int size = waitQueue->size();
        if (size < minRequest) minRequest = size;
        if (size > maxRequest) maxRequest = size;
        averageRequests += size;
    }
}


int Disk::processTimer() {
    int size = getQueueLength();
    averageRequests += size;
    totalSamples++;
    return size;
}

double Disk::accessTime() {
    return std::abs(curr_track - dest_track) * 3.0
         + rotdist(curr_sector, dest_sector) * 0.1
         + 0.1;
}

double Disk::distance(int curr_sector, int dest_sector) {
    return std::abs(curr_track - dest_track);
}

double Disk::rotdist(int curr_sector, int dest_sector) {
    return (dest_sector - curr_sector + 30) % 30;
}

int Disk::getQueueLength() {
    return waitQueue->size();
}

void Disk::printStats() {
    std::cout << "\n[" << diskName << "] Stats:\n";
    std::cout << "  Total Requests Completed: " << totalRequests << "\n";
    std::cout << "  Max Queue Length: " << maxRequest << "\n";
    std::cout << "  Avg Queue Length: "
              << (totalSamples > 0 ? averageRequests / totalSamples : 0.0)
              << "\n";
}
