# Compiler flags
FLAGS = -g -c --std=c++17

# OS detection (Windows uses OS=Windows_NT)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist
    MKCMD = mkdir
    RM = rmdir /S /Q
    EXE = .exe
    SLASH = \\
    SHELL = cmd
else
    MKDIR = mkdir -p
    RM = rm -rf
    EXE =
    SLASH = /
endif

# Targets
all: obj bin
	g++ $(FLAGS) src/main.cc -o obj$(SLASH)calc.o
	g++ -g -o bin$(SLASH)calculator$(EXE) obj$(SLASH)calc.o

# Create directories
obj:
ifeq ($(OS),Windows_NT)
	$(MKDIR) obj $(MKCMD) obj
else
	$(MKDIR) obj
endif

bin:
ifeq ($(OS),Windows_NT)
	$(MKDIR) bin $(MKCMD) bin
else
	$(MKDIR) bin
endif

clean:
	$(RM) bin
	$(RM) obj

.PHONY: all clean bin obj