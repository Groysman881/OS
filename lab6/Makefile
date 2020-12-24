CC = gcc
CFLAGS = -c
TARGET = l6
SOURCES = lab6.c
OBJECTS = $(SOURCES:.c=.o)

all : $(TARGET) 
	./l6
$(TARGET) : $(OBJECTS)
	$(CC) -o $@  $(OBJECTS) -lpthread 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf *.o $(TARGET)

