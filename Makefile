CC = g++
CFLAGS = -Wall
PROG = main

SRCS = 1.cpp imageloader.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS) -lGLU

clean:
	rm -f $(PROG)
