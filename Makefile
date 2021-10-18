BINS = sort_driver experiments
OBJS = sort_driver.o sorts.o array_util.o experiments.o

CFLAGS = -g -std=c99 -Wall
LDFLAGS = -g -lm

.PHONY: all clean

all: $(BINS)

clean:
	$(RM) $(BINS) $(OBJS)

sort_driver: sorts.o array_util.o

sort_driver.o: sorts.h array_util.h

experiments: sorts.o array_util.o

experiments.o: sorts.h array_util.h
