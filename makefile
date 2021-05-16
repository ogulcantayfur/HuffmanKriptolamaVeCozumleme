CLASSDIR = Libfdr
INCLUDE = -I$(CLASSDIR)/include
LIBS = $(CLASSDIR)/lib/libfdr.a
CC = gcc

all: kripto
		
clean:
	rm -f kripto

cleanall: clean
	find . -maxdepth 1  ! -name "main.c"  ! -name "makefile" ! -name "Readme.md" -type f -exec rm -f {} \;

run: clean \
	all \
	calistir

kripto:	main.c $(LIBS)
	$(CC) $(INCLUDE) -Wall -g -o kripto main.c $(LIBS)

calistir:
			./kripto -e giris_metin encrypted
			./kripto -d encrypted decrypted