cmake_minimum_required(VERSION 3.12)
project(DiskSim.x)

set(CMAKE_CXX_STANDARD 17)

add_executable(fcfs.x FCFS_Queue/main.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp CommonFiles/Request.cpp)

add_executable(st.x ST_Queue/main.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp CommonFiles/Request.cpp
        ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp)

add_executable(pickup.x PU_Queue/main.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp CommonFiles/Request.cpp
        ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp
        PU_Queue/PUQueue.cpp)

add_executable(look.x Look_Queue/main.cpp CommonFiles/Request.cpp)
