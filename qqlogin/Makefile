CXX=g++
CXXFLAGS=-c -Wall -std=c++11 -I/usr/include/jsoncpp
LDFLAGS=-pthread
LIBS= -lcurl -ljsoncpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -lboost_regex -lboost_system -lpthread -lstdc++

all: qq_crawler

qq_crawler: main.o qqlogin.o fetcher.o
	$(CXX) $(LDFLAGS) main.o qqlogin.o fetcher.o -o qq_crawler $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

fetcher.o: fetcher.cpp
	$(CXX) $(CXXFLAGS) fetcher.cpp

qqlogin.o: qqlogin.cpp
	$(CXX) $(CXXFLAGS) qqlogin.cpp

clean:
	rm -f *.o qq_crawler
