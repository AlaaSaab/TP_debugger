CC      = clang
CFLAGS  = -g
EXE     = essai_fap essai cesar

.PHONY: all clean
all: $(EXE)

essai_fap.o: essai_fap.c
	$(CC) $(CFLAGS) -include instrumentation.h -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

essai_fap: essai_fap.o fap_bug.o instrumentation.o
	$(CC) $(CFLAGS) $^ -o $@

essai: essai.o
	$(CC) $(CFLAGS) $^ -o $@

cesar: cesar.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY:
clean:
	rm -f *.o $(EXE)
