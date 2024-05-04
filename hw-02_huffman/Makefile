CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++20 -Iinclude -g3
LDFLAGS = 

EXE = hw-02_huffman
SRCDIR = src
TEST = hw-02_huffman_test
BINDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TEST_OBJECTS = $(filter-out $(OBJDIR)/main.o, $(OBJECTS))

all: $(EXE) $(TEST)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<


$(TEST): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $(TEST) $(LDFLAGS)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE) $(TEST)
