CC=gcc

CFLAGS= -fsanitize=address
LDFLAGS += -fsanitize=address


PROGS=frame
packages=src/main.o src/entities/ball.o src/maths/geo2D.o src/logic/physic.o src/logic/collisions.o

all: $(PROGS) $(packages)


# ----------- FILES -----------

%.o: %.c
	$(CC) -c $<  $(CFLAGS) $(LDFLAGS) -o $@


# -------------- EXECUTABLES --------------


frame: src/main.o src/entities/ball.o src/maths/geo2D.o src/logic/physic.o src/logic/collisions.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ `simple2d --libs` -o $@


clean:
	rm $(PROGS) -f | rm $(packages) -f