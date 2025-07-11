
# This Makefile is not intended to take advantage of separate compilation.
# It serves as a short-cut to command-line compilation

# Store this file in the project directory (DiskSim)
# This Makefile compiles all disk scheduling simulators

CXX = g++
CXXFLAGS = -std=c++17

COMMON = CommonFiles/Request.cpp
FCFS = FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp
ST = ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp
PU = PU_Queue/PUQueue.cpp
LOOK = Look_Queue/LookQueue.cpp
CLOOK = CLook_Queue/CLookQueue.cpp
EVENTS = EventQueue/EventQueue.cpp \
         CommonFiles/Disk.cpp

fcfs.x:
	$(CXX) $(CXXFLAGS) $(COMMON) $(FCFS) FCFS_Queue/main.cpp -o fcfs.x

st.x:
	$(CXX) $(CXXFLAGS) $(COMMON) $(FCFS) $(ST) ST_Queue/main.cpp -o st.x

pickup.x:
	$(CXX) $(CXXFLAGS) $(COMMON) $(FCFS) $(ST) $(PU) PU_Queue/main.cpp -o pickup.x

look.x:
	$(CXX) $(CXXFLAGS) $(COMMON) $(FCFS) $(ST) $(LOOK) Look_Queue/main.cpp -o look.x

clook.x:
	$(CXX) $(CXXFLAGS) $(COMMON) $(FCFS) $(ST) $(CLOOK) CLook_Queue/main.cpp -o clook.x

alldisks.x:
	$(CXX) $(CXXFLAGS) $(COMMON) $(FCFS) $(ST) $(PU) $(LOOK) $(CLOOK) $(EVENTS) main.cpp -o alldisks.x

clean:
	rm -f fcfs.x st.x pickup.x look.x clook.x alldisks.x
