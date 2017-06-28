LDFLAGS=-L/usr/lib/x86_64-linux-gnu
LDLIBS=-lcurl

appname := placa

CXX := g++
CXXFLAGS := -std=c++11 -g -Wall

srcfiles := $(shell find . -name "*.cc")
objects  := $(patsubst %.cc, %.o, $(srcfiles))

all: $(appname) 

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)
	rm -f $(appname)

dist-clean: clean
	rm -f *~ .depend

