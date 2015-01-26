#
#
#

CFLAGS = -Wall -Werror
PROGS = bnr
bnr_SRCS = bsearch.c
SRCS  = tree.c item.c
OBJS  = $(SRCS:%.c=%.o)

all: $(OBJS)

$(OBJS): %.o:%.c

$(OBJS:%.o=%): $(OBJS)

$(PROGS): $(bnr_SRCS)

clean:
	rm -f $(PROGS)

clobber: clean
	rm -f $(OBJS)

