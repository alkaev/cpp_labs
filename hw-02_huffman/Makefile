CXX = g++
CXXFLAGS = -O2 -std=c++11 -Iinclude -Wall -Werror
LDFLAGS = 

EXE = hw-02_huffman
SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

TESTDIR = test

testing: obj/FileWorker.o obj/HuffmanTree.o obj/HuffmanTreeArchiver.o obj/HuffmanTreeNode.o obj/HuffmanTests.o obj/tests.o
	$(CXX) obj/FileWorker.o obj/HuffmanTree.o obj/HuffmanTreeArchiver.o obj/HuffmanTreeNode.o obj/HuffmanTests.o obj/tests.o -o testing $(LDFLAGS)
	
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) testing samples/test1 samples/test1.txt testing samples/test2 samples/test2.txt

.PHONY: clean all