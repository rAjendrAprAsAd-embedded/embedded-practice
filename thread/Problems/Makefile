SOURCES := $(wildcard *.c)
PROGS := $(SOURCES:.c=)

all: $(PROGS)

%: %.c
	gcc -O2 -pthread $< -o $@

clean:
	rm -f *~ *.o $(PROGS)
