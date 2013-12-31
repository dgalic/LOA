PROGRAM=LOA
LIB=src/lib64

all:sub

sub:
	cd src;	make
	cp src/$(PROGRAM) $(PROGRAM)

clean:
	cd src;	make clean;

proper:clean
	rm $(PROGRAM)
	cd src; make proper;

start:
	export LD_LIBRARY_PATH=$(LIB) && ./$(PROGRAM)