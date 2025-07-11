#ifndef DISKSIM_X_TIMEREVENT_H
#define DISKSIM_X_TIMEREVENT_H

class TimerEvent {
public:
    explicit TimerEvent(double oldTime) : currentTime{ oldTime + 50 } {}

    double getcurrentTime() const { return currentTime; }

    void print() const {
        std::cout << "[TimerEvent] Time: " << currentTime << std::endl;
    }

private:
    double currentTime;
};

#endif //DISKSIM_X_TIMEREVENT_H
