CC = gcc
CFLAGS = -c
TARGET = l7
SOURCES = lab7.c
OBJECTS = $(SOURCES:.c=.o)

all : $(TARGET)
	./l7
$(TARGET) : $(OBJECTS)
	$(CC) -o $@  $(OBJECTS) -lpthread 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf *.o $(TARGET)

