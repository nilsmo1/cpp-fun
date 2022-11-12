CXX=g++
CPPFILES=main.cpp
OBJDIR=./obj
OBJFILES=$(patsubst %.cpp,$(OBJDIR)/%.o, $(CPPFILES))
BINARY=minesweeper

all: $(BINARY)

$(BINARY): $(OBJFILES)
	@echo "Creating binary.."
	$(CXX) -o $@ $^

$(OBJFILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CXX) -c -o $@ $^

run: $(BINARY)
	@./$(BINARY)

clean:
	@echo "Removing object files.."
	rm -rf $(OBJDIR) 
	@echo "Removing binary.."
	rm -f $(BINARY)
