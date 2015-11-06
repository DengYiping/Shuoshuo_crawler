CC=clang
CFLAGS=-c -Wall -std=c++11 -pthread -stdlib=libc++
LDFLAGS= -lcurl -lstdc++ -lpthread -stdlib=libc++ -ljsoncpp -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options
EXECUTABLE=qq_crawler

all: qq_crawler

qq_crawler: main.o qqlogin.o fetcher.o
  $(CC) $(LDFLAGS) main.o downloader.o fetcher.o -o qq_crawler

main.o: main.cpp
  $(CC) $(CFLAGS) main.cpp

fetcher.o: fetcher.cpp
  $(CC) $(CFLAGS) fetcher.cpp

qqlogin.o: qqlogin.cpp
  $(CC) $(CFLAGS) qqlogin.cpp
clean:
  rm *.o qq_crawler