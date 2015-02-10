

FILES = stack.c item.c
OBJS = ${FILES:%.c=%.o}
LIBS = libstack.so libitem.so
CFLAGS = -m64 -fPIC -std=c99 -I../includes
LDFLAGS = -shared

all: $(LIBS)

# $(LIBS): $(OBJS)
$(LIBS): lib%.so:%.o
	$(CC) -o $@ $(LDFLAGS) $^

clean:
	$(RM) $(LIBS)

clobber: clean
	$(RM) $(OBJS)

