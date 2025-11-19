CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS = -shared
TARGET = libiec958.so

SRCS = iec958_custom.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)  

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -f $(OBJS) $(TARGET)


