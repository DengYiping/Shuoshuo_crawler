CXX=g++-4.9
CXXFLAGS=-c -Wall -std=c++11 -I/usr/include/jsoncpp
LDFLAGS=-pthread
LIBS=  -L/usr/local/lib -lcurl -lstdc++ -ljsoncpp -lpthread

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
