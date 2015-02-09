#
#
#

INCLUDES = -I../includes
CFLAGS = -Wall -Werror -g $(INCLUDES)
PROGS = bnr
HEADERS = 
bnr_SRCS = bsearch.c
SRCS  = tree.c item.c
OBJS  = $(SRCS:%.c=%.o)
EXERCISES = 63 64

all: $(OBJS)

$(OBJS): %.o:%.c $(HEADERS)

$(PROGS): %:%.o
	cc -o $@ $^

$(EXERCISES:%=pr%): pr%:Problems/Exercise-12.%.o $(OBJS)
	cc -o $@ $^

clean:
	rm -f $(EXERCISES:%=pr%)
	rm -f $(PROGS)

clobber: clean
	rm -f $(OBJS)

