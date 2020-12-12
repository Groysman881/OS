CC = gcc
CFLAGS = -c
TARGET = l2a
SOURCES = lab2a.c
OBJECTS = $(SOURCES:.c=.o)


all : $(TARGET)
	./l2a

$(TARGET) : $(OBJECTS)
	$(CC) $(SOURCES) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf *.o $(TARGET)

