CXXFLAGS = -g -Wall -pedantic

SOURCEDIR = source
BUILDIR = build

EXECUTABLE= $(BUILDIR)/graphcoloring

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
DEPENDENCIES = $(wildcard $(SOURCEDIR)/*.hpp)

_OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst $(SOURCEDIR)/%,$(BUILDIR)/%,$(_OBJECTS))

$(BUILDIR)/%.o : $(SOURCEDIR)/%.cpp $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY : cleanobj clean

cleanobj:
	rm $(OBJECTS)
clean:
	rm $(EXECUTABLE)
