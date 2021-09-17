CC=gcc
CFLAGS=-g #-DPTH
all: libspin.so libhash.so libcounter.so liblist.so

spin.o : spin.c
	$(CC) $(CFLAGS) -c -fpic spin.c

list.o : list.c
	$(CC) $(CFLAGS) -c -fpic list.c

hash.o : hash.c
	$(CC) $(CFLAGS) -c -fpic hash.c

counter.o : counter.c
	$(CC) $(CFLAGS) -c -fpic counter.c

libspin.so: spin.o
	$(CC) $(CFLAGS) -shared -o $@ $<

libhash.so : hash.o
	$(CC) $(CFLAGS) -shared -o $@ $<

libcounter.so : counter.o
	$(CC) $(CFLAGS) -shared -o $@ $<

liblist.so : list.o
	$(CC) $(CFLAGS) -shared -o $@ $<

clean :
	rm -rf *.o *.so
