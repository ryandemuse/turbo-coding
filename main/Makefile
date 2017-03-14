CC = gcc
CFLAGS = -Wall
DEPENDENCIES = debug.h channel.h encoder.h decoder.h encoder4.h decoder4.h encoders3.h decoders3.h srandominterleaver.h
OBJECTS = turbo.o debug.o channel.o encoder.o decoder.o encoder4.o decoder4.o encoders3.o decoders3.o srandominterleaver.o

%.o: %.c $(DEPENDENCIES)
	$(CC) $(CFLAGS) -c -o $@ $<

turbo: $(OBJECTS)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm turbo $(OBJECTS)
