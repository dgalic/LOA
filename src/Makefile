#Nicolas CAILLOUX et David GALICHET
PROGRAM=LOA
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXX=g++
CXXFLAGS := -std=c++0x -Wall -Wextra -pedantic-errors -g
DEPS=make.dep
LIB=./lib64
INC=./include
LIBS := -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: show $(PROGRAM)

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


$(DEPS):$(SOURCES) $(HEADERS)
	echo "building $@ with $^";
	$(CXX) -M -I$(INC) -L$(LIB) $(LIBS) $^ > $(DEPS)

#include $(DEPS)

$(PROGRAM):$(OBJECTS)
	@echo "building "$@;
	$(CXX) $(CXXFLAGS) $^ -L$(LIB) $(LIBS) -o $@ 

%.o:%.cpp
	@echo "building $@ with .cpp";
	$(CXX) -c $(CXXFLAGS) -I$(INC) $<

clean:
	rm -f $(PROGRAM) $(OBJECTS) *.d *~ *# *.gch

start:
	export LD_LIBRARY_PATH=$(LIB) && ./$(PROGRAM)