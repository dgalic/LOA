PROGRAM=LOA

all:sub

sub:
	cd src;	make
	cp src/$(PROGRAM) $(PROGRAM)

clean:
	rm LOA
	cd src;	clean;