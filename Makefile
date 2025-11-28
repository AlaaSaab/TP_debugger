CC=clang -g

all: essai_fap

%.o: %.c	
	$(CC) -c $<

fap_bug.o: fap_bug.c fap.h

essai_fap.o: essai_fap.c fap_bug.c fap.h

essai_fap: fap_bug.o essai_fap.o
	$(CC) $^ -o $@

clean:
	rm -f *.o



