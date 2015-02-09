#
#
#

INCLUDES = -I../includes
CFLAGS = -Wall -Werror -g -m64 -fPIC -std=gnu99 $(INCLUDES)
LDFLAGS = -L../libs -Xlinker -rpath=../libs
PROGS = stkchk
HEADERS = 
bnr_SRCS = bsearch.c
SRCS  = tree.c item.c stkchk.c
OBJS  = $(SRCS:%.c=%.o)
EXERCISES = 63 64

all: $(OBJS)

$(OBJS): %.o:%.c $(HEADERS)

stkchk: LDFLAGS += -lstack

$(PROGS): %:%.o ../libs/libstack.so
	cc -o $@ $(LDFLAGS) $^

$(EXERCISES:%=pr%): pr%:Problems/Exercise-12.%.o $(OBJS)
	cc -o $@ $^

clean:
	rm -f $(EXERCISES:%=pr%)

clobber: clean
	rm -f $(PROGS) Problems/*.o
	rm -f $(OBJS)

