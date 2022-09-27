CC = gcc
CFLAGS = -O2 -pedantic -ggdb -g3

YACC = yacc
YFLAGS = -d

scottcom_obj = parser.o scottcom.o code.o dict.o font.o init.o item.o message.o output.o room.o symbol.o ti99.o

all: parser.c scottcom

scottcom: $(scottcom_obj)
	$(CC) $(scottcom_obj) -o scottcom

clean:
	rm -f *.o
	rm -f parser.c parser.h
	rm -f scottcom

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.c : %.y
	$(YACC) $(YFLAGS) $< -o $@
