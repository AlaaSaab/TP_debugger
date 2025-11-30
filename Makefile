CC=clang -g

all: essai_fap essai cesar

essai_fap.o: essai_fap.c
	$(CC) -include instrumentation.h -c essai_fap.c

fap_bug.o: fap_bug.c fap.h
	$(CC) -c fap_bug.c

instrumentation.o: instrumentation.c
	$(CC) -c instrumentation.c

essai_fap: essai_fap.o fap_bug.o instrumentation.o
	$(CC) $^ -o $@

essai.o: essai.c
	$(CC) -c essai.c

essai: essai.o
	$(CC) $^ -o $@

cesar.o: cesar.c
	$(CC) -c cesar.c

cesar: cesar.o
	$(CC) $^ -o $@

clean:
	rm -f *.o essai_fap essai cesar
