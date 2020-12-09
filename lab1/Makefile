CC = gcc
CFLAGS = -c
TARGET = l1
SOURCES = lab1.c
OBJECTS = $(SOURCES:.c=.o)


all : $(TARGET)
	./l1

$(TARGET) : $(OBJECTS)
	$(CC) $(SOURCES) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf *.o $(TARGET)
