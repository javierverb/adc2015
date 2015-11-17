TARGET = temperature
NAME = temperature
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

.PHONY : clean

CC = mpicc

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)