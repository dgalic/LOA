#Nicolas CAILLOUX et David GALICHET
PROGRAM=LOA
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXX=g++
CXXFLAGS := -std=c++0x -Wall -Wextra -pedantic-errors -g
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	@echo "building "$@;
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	cp $(PROGRAM) ../$(PROGRAM)

%.o:%.d
	$(CXX) -c $(CXXFLAGS) $< -o $@

%.d:%.cpp %.hpp
	$(CXX) -MM $(CXXFLAGS) $<

clean:
	rm -f $(PROGRAM) $(OBJECTS) *.d *~ *.gch

