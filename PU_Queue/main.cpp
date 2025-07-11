#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../CommonFiles/Request.hpp"
#include "PUQueue.h"

PUQueue *createPUQueueFromInputFile( int argc, char *argv[] ) {

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

    auto *queue = new PUQueue();
    int time, track, sector;

    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request,0,0);
    }
    return queue;
}


int main(int argc, char *argv[]) {
    std::cout << "PU -- Main function.\n";
    PUQueue *queue = nullptr;
    queue = createPUQueueFromInputFile(argc, argv);
    queue->print();
    delete queue;

    return 0;
}
