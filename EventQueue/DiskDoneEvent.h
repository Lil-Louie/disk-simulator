#ifndef DISKSIM_X_DISKDONEEVENT_H
#define DISKSIM_X_DISKDONEEVENT_H

#include "../CommonFiles/Queue.hpp"
#include "../CommonFiles/Disk.h"

class Disk;
class Queue;

class DiskDoneEvent {
public:
    DiskDoneEvent(double completionTime, Queue* waitQueue, Disk* disk)
        : completionTime{completionTime}, waitQueue{waitQueue}, disk{disk} {}

    Disk* getDisk() const { return disk; }
    Queue* getWaitQueue() const { return waitQueue; }
    double getcurrentTime() const { return completionTime; }

private:
    Disk* disk;
    Queue* waitQueue;
    double completionTime;
};
#endif //DISKSIM_X_DISKDONEEVENT_H
