

FILES = stack.c
OBJS = ${FILES:%.c=%.o}
LIBS = libstack.so
CFLAGS = -m64 -fPIC -std=c99 -I../includes
LDFLAGS = -shared

all: $(LIBS)

$(LIBS): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(OBJS)

clean:
	$(RM) $(LIBS)

clobber: clean
	$(RM) $(OBJS)

