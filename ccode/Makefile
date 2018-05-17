#Include complier options
CC=gcc

#compiler flags: -g  -Wall
CFLAGS = -g -Wall

#file flasgs
LFALGS= -lcs 50

#the name to user for both the target files
TARGET = helloworld

all: $(TARGET)

$(TARGET) : $(TARGET).c 
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c  $(LFAGS)
