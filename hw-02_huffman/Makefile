CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++20 -Iinclude  -g3
LDFLAGS =

EXE = hw-02_huffman
TEST = hw-02_huffman_test
SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
EXE_OBJECTS = $(filter-out $(OBJDIR)/test.o, $(OBJECTS))
TEST_OBJECTS = $(filter-out $(OBJDIR)/main.o, $(OBJECTS))

all: $(EXE) $(TEST)

$(EXE): $(EXE_OBJECTS)
	$(CXX) $(EXE_OBJECTS) -o $(EXE) $(LDFLAGS)

$(TEST): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $(TEST) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEST) 

.PHONY: clean all