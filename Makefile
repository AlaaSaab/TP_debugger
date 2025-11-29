CC=clang -g

all: essai_fap essai cesar

%.o: %.c	
	$(CC) -c $<

fap_bug.o: fap_bug.c fap.h

essai_fap.o: essai_fap.c fap_bug.c fap.h

essai.o: essai.c

cesar.o: cesar.c

essai_fap: fap_bug.o essai_fap.o
	$(CC) $^ -o $@

essai: essai.o

cesar: cesar.o

clean:
	rm -f *.o



