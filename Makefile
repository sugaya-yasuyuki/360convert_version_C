CC		= g++ -O2
CFLAGS          = -Wall \
		  `pkg-config --cflags opencv4 eigen3`
LDFLAGS         = `pkg-config --libs opencv4`
LIBS            = `pkg-config --libs opencv4` -lm

SRCS		= main.c \
		  getargs.c \
		  e2p.c \
		  f2p.c \
		  rotation.c 

HDRS		= getargs.h \
		  e2p.h \
		  f2p.h \
		  rotation.h

OBJS		= $(SRCS:.c=.o)

PROGRAM		= 360convert

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS) $(HDRS) 
		$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

clean:;		rm -f *.o *~ $(PROGRAM)

###								End of Makefile
