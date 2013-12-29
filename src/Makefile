#Nicolas CAILLOUX et David GALICHET
PROGRAM=LOA
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXX=g++
CXXFLAGS := -std=c++0x -Wall -Wextra -pedantic-errors -g
#LIB=./lib64
INC=./include
#WRAPFLAG := -Wl,--version-script memcpy_wrap.map
#LIBS := -Wl,-rpath,$(LIB) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


all: $(PROGRAM)


show:
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-compiler : $(CXX)"
	@echo "-compiler options : $(CXXFLAGS)"
	@echo "-libraries : $(LIB)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"
	@echo "-librairies : $(LIBS)"

#config:
#	cd lib64; make links;

 %.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -M $(CXXFLAGS) -I$(INC) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SOURCES:.cpp=.d)

#wrapper: memcpy_wrap.c memcpy_wrap.map
#	gcc -c memcpy_wrap.c -o memcpy_wrap.o

$(PROGRAM):$(OBJECTS)
	@echo "building "$@;
	$(CXX) $(CXXFLAGS) $^ -o $@ 

%.o:%.cpp
	@echo "building $@ with .cpp";
	$(CXX) -c $(CXXFLAGS) -I$(INC) $<

clean:
	rm -f $(OBJECTS) *.d* *~ *# *.gch

proper:clean
	rm -f $(PROGRAM)

start:
	./$(PROGRAM) 2> Errlog