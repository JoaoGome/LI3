IDIR=../include
ODIR=obj

CC = gcc
CFLAGS = -g -ansi -D_GNU_SOURCE -std=c99 -pedantic -O2  `pkg-config --cflags glib-2.0` -I$(IDIR)

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
LIBS = `pkg-config --libs glib-2.0` 

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : $(SDIR)%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o) -o program $(LIBS) -lm

clean:
	rm obj/*.o
	rm program
