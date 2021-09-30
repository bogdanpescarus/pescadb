# compiler
CC = g++

# compiler flags
CFLAGS = -g -Wall

TARGET = ./bin/main
TARGETOBJ = ./dataTypes.o ./inputBuffer.o ./utils.o

main:	main.cpp ./dataTypes.o ./inputBuffer.o ./utils.o
	$(CC) $(CFLAGS) main.cpp ./dataTypes.o ./inputBuffer.o ./utils.o -o ./bin/main --std=c++17

dataTypes.o:	./include/dataTypes.hpp ./src/dataTypes.cpp
	$(CC) $(CFLAGS) -c ./src/dataTypes.cpp ./include/dataTypes.hpp --std=c++17

inputBuffer.o:	./include/inputBuffer.hpp ./src/inputBuffer.cpp
	$(CC) $(CFLAGS) -c ./src/inputBuffer.cpp ./include/dataTypes.hpp --std=c++17

utils.o:	./src/utils.cpp ./include/utils.hpp
	$(CC) $(CFLAGS) -c ./src/utils.cpp ./include/utils.hpp --std=c++17

clean:
	rm -f $(TARGET) $(TARGETOBJ)
