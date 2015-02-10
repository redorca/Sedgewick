

FILES = stack.c item.c random.c
OBJS = ${FILES:%.c=%.o}
LIBS = libstack.so libitem.so librandom.so
CFLAGS = -m64 -fPIC -std=gnu99 -I../includes
LDFLAGS = -shared
HEADERS = $(FILES:%.c=%.h)
INC_PATHS = ../includes

all: $(LIBS)

$(LIBS): lib%.so:$(INC_PATHS)/%.h
$(LIBS): lib%.so:%.o
	$(CC) -o $@ $(LDFLAGS) $(@:lib%.so=%.o)

clean:
	$(RM) $(LIBS)

clobber: clean
	$(RM) $(OBJS)

