CC = gcc
CFLAGS = -c
TARGET = l2b
SOURCES = lab2b.c
OBJECTS = $(SOURCES:.c=.o)


all : $(TARGET)
	./l2b

$(TARGET) : $(OBJECTS)
	$(CC) $(SOURCES) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf *.o $(TARGET)

