

OBJS	= 12-9.o 12-10.o
SRCS	= $(OBJS:%.o=%.c)
INCLUDES	= ../

all: $(OBJS)
	@echo "Done."

%.o : %.c
	$(CC) -c -o %@ -I $(INCLUDES) $^


