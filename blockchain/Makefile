CC = g++
CFLAGS = -g -Wall

default: blockchain

blockchain: mine.cpp block.cpp block.hpp chain.cpp chain.hpp sha256.cpp sha256.hpp
	$(CC) $(CFLAGS) -o blockchain mine.cpp block.cpp chain.cpp sha256.cpp

clean: 
	$(RM) count *.o blockchain