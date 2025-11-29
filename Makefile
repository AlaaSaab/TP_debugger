CC=clang -g

all: essai_fap essai

%.o: %.c	
	$(CC) -c $<

fap_bug.o: fap_bug.c fap.h

essai_fap.o: essai_fap.c fap_bug.c fap.h

essai.o: essai.c

essai_fap: fap_bug.o essai_fap.o
	$(CC) $^ -o $@

essai: essai.o

clean:
	rm -f *.o



