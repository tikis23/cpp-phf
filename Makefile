cc = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -Iinclude/

# headers included for incremental build
HEADERS = include/phf/internal/phf.h include/phf/hash.h include/phf/unordered_map.h
SRCS = example.cpp

BINDIR = bin
TARGET = example

.PHONY: all

all: release

release: CXXFLAGS += -O3
release: build

debug: CXXFLAGS += -g
debug: build

build: $(BINDIR) $(BINDIR)/obj $(BINDIR)/$(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/obj:
	mkdir -p $(BINDIR)/obj

OBJS = $(SRCS:%.cpp=$(BINDIR)/obj/%.o)

$(BINDIR)/$(TARGET): $(OBJS)
	$(cc) $(CXXFLAGS) -o $@ $^

$(BINDIR)/obj/%.o: %.cpp $(HEADERS)
	$(cc) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -r $(BINDIR)

