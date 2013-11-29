#Nicolas CAILLOUX, Baptiste FONTAINE, David GALICHET
PROGRAM=Pixogames
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXX=g++
CXXFLAGS := -std=c++0x -Wall -Wextra -pedantic-errors -g
LDFLAGS= 

all: $(PROGRAM)

show:
	@echo "ld : "$(LDFLAGS);
	@echo "sources : "$(SOURCES);
	@echo "objects : "$(OBJECTS);
	@echo "command : "$(CXX) $(CXXFLAGS);

$(PROGRAM):$(OBJECTS)
	@echo "building "$@;
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	cp $(PROGRAM) ../$(PROGRAM)

%.o:%.d
	$(CXX) -c $(CXXFLAGS) $<

%.d:%.cpp %.hpp
	$(CXX) -MM $(CXXFLAGS) $<

clean:
	rm -f $(PROGRAM) $(OBJECTS) *.d *~

