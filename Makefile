# Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lodbc

SRCDIR = src
BINDIR = bin
TARGET = $(BINDIR)/autodealership

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

clean:
	rm -rf $(BINDIR)

run:
	$(all)
	$(TARGET)
