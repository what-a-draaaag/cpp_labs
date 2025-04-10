CXX = g++
CXXFLAGS = -O0 -g3 -Wall -Werror -std=c++11 -Iinclude -std=c++17
LDFLAGS = 

EXE = lab-14_linq
SRCDIR = src
OBJDIR = obj

OBJECTS = $(OBJDIR)/test.o

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE)

.PHONY: clean all