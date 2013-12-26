PROGRAM=LOA
LIB=src/lib64

all:sub

sub:
	cd src;	make
	cp src/$(PROGRAM) $(PROGRAM)

clean:
	rm LOA
	cd src;	clean;

start:
	export LD_LIBRARY_PATH=$(LIB) && ./$(PROGRAM)