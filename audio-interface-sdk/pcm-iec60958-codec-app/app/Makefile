CC = gcc
CFLAGS = -I../libiec958-custom -Wall
LDFLAGS = -L../libiec958-custom
LIBS = -liec958
TARGET = app-iec60958-enc-dec

SRCS = iec60958-enc-dec-main.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean: 
	rm -f $(OBJS) $(TARGET) 
	

	
