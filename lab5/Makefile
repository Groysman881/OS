CC = gcc
CFLAGS = -c
TARGET = l5
SOURCES = lab5.c
OBJECTS = $(SOURCES:.c=.o)


$(TARGET) : $(OBJECTS)
	$(CC) -o $@  $(OBJECTS) -lpthread 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf *.o $(TARGET)

