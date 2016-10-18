CC = gcc
OBJECTS = lib/libbmp.c src/r20_math.c src/r20_shader.c src/r20_plane.c r20.c
LIBS = -lm
CFLAGS = -Wall -O2
BINDIR = $(DESTDIR)/usr/bin
NAME = r20

r20: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<
