CC = g++
CFLAGS = -std=c++11 -I.

TARGET = main
SRCS = main.cpp knight2.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del *.gch $(OBJS) $(TARGET) 2>NUL || (exit 0)
