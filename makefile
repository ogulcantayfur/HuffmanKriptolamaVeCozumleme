INCLUDE = -O3 -Ilibfdr/include
LIBS = libfdr/lib/libfdr.a
CC = gcc
OBJS = libfdr/obj/dllist.o libfdr/obj/fields.o libfdr/obj/jval.o libfdr/obj/jrb.o

all: lib/libfdr.a \
	kripto

clean:
	find . -maxdepth 1 ! -name "makefile" ! -name ".kilit" ! -name "giris_metin" ! -name "Readme.md"  ! -name "main.c" -type f -exec rm -f {} \;
	rm -f libfdr/obj/* libfdr/lib/*

lib/libfdr.a: $(OBJS)
	ar ru libfdr/lib/libfdr.a $(OBJS)
	ranlib libfdr/lib/libfdr.a

libfdr/obj/fields.o: libfdr/src/fields.c libfdr/include/fields.h
	$(CC) $(INCLUDE) -c -o libfdr/obj/fields.o libfdr/src/fields.c

libfdr/obj/jval.o: libfdr/src/jval.c libfdr/include/jval.h
	$(CC) $(INCLUDE) -c -o libfdr/obj/jval.o libfdr/src/jval.c

libfdr/obj/dllist.o: libfdr/src/dllist.c libfdr/include/dllist.h libfdr/include/jval.h
	$(CC) $(INCLUDE) -c -o libfdr/obj/dllist.o libfdr/src/dllist.c

libfdr/obj/jrb.o: libfdr/src/jrb.c libfdr/include/jrb.h libfdr/include/jval.h
	$(CC) $(INCLUDE) -c -o libfdr/obj/jrb.o libfdr/src/jrb.c

kripto:	main.c $(LIBS) 
	$(CC) $(INCLUDE) -g -Wall -o kripto main.c $(LIBS)