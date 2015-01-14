#
#
#

PROGS = bnr
bnr_SRCS = bsearch.c
SRCS  = $(bnr_SRCS)
OBJS  = $(SRCS:%.c=%.o)

all: $(PROGS)

$(OBJS): %.o:%.c

$(OBJS:%.o=%): $(OBJS)

$(PROGS): $(bnr_SRCS)

clean:
	rm -f $(PROGS)

clobber: clean
	rm -f $(OBJS)

