#include <iostream>
#include <fstream>
#include <cstdlib>
#include "./CommonFiles/Queue.hpp"
#include "./EventQueue/EventQueue.h"
#include "./EventQueue/DiskDoneEvent.h"
#include "./EventQueue/TimerEvent.h"
#include "./EventQueue/RequestEvent.h"

#include "./FCFS_Queue/FCFSQueue.hpp"
#include "./ST_Queue/STQueue.hpp"
#include "./PU_Queue/PUQueue.h"
#include "./Look_Queue/LookQueue.h"
#include "./CLook_Queue/CLookQueue.h"

class Request;

Request *ReadNextRequest(std::ifstream &inputStream) {
    int time, track, sector;

    if (inputStream >> time >> track >> sector) {
        return new Request(time, track, sector);
    }

    return nullptr;  // Return nullptr if we reach EOF or a bad line
}

int main( int argc, char *argv[] ) {

    //Checks for Valid file input
    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }




    //Declarations and Defintions
    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();
    Queue *pu = new PUQueue();
    Queue *look = new LookQueue();
    Queue *clook = new CLookQueue();

    Disk *fcfsDisk = new Disk(fcfs, "FCFS");
    Disk *stDisk = new Disk(st, "ST");
    Disk *puDisk = new Disk(pu, "PickUp");
    Disk *lookDisk = new Disk(look, "Look");
    Disk *clookDisk = new Disk(clook, "CLook");

    std::vector<Disk*> disks = { fcfsDisk, stDisk, puDisk, lookDisk, clookDisk };

    // Init event queue
    EventQueue* eQueue = new EventQueue();
    if (Request* firstRequest = ReadNextRequest(inputStream)) {
        eQueue->addEvent(new EventNode(new RequestEvent(firstRequest)));
    }
    eQueue->addEvent(new EventNode(new TimerEvent(0)));

   while (!eQueue->empty()) {
        EventNode* event = eQueue->getEvent();

        if (event->isRequestEvent()) {
            RequestEvent* reqEvent = event->getRequest();
            for (Disk* disk : disks) {
                disk->processRequest(eQueue, reqEvent->getRequest());
            }

            if (Request* nextRequest = ReadNextRequest(inputStream)) {
                eQueue->addEvent(new EventNode(new RequestEvent(nextRequest)));
            }

        } else if (event->isTimerEvent()) {
            TimerEvent* timer = event->getTimer();

            std::cout << "\n[Timer @ " << timer->getcurrentTime() << "ms] Disk Queue Status:\n";
            for (Disk* disk : disks) {
                std::cout << "  " << disk->getName() << ": "
                          << disk->processTimer() << " entries\n";
            }

            if (!eQueue->empty()) {
                eQueue->addEvent(new EventNode(new TimerEvent(timer->getcurrentTime())));
            }

        } else if (event->isDiskDoneEvent()) {
            DiskDoneEvent* done = event->getDiskDone();
            done->getDisk()->processDiskDone(eQueue);
        }

        delete event;
    }

    // Final stats
    std::cout << "\n========== FINAL DISK STATS ==========\n";
    for (Disk* disk : disks) {
        disk->printStats();  // <-- make sure Disk has this function implemented
    }

    return 0;
}
