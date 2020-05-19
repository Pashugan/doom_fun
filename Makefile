CFLAGS = -g -Wall -Wextra -Werror -std=c99 -pedantic
TARGET = doom

all: $(TARGET)

$(TARGET): doom.o wad.o
	$(CC) $(CFLAGS) -o $(TARGET) doom.o wad.o

doom.o: doom.c datatype.h wad.h
	$(CC) $(CFLAGS) -c doom.c

wad.o: wad.c wad.h
	$(CC) $(CFLAGS) -c wad.c

clean:
	$(RM) $(TARGET) *.o *~
