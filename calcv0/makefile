# Compiler flags
FLAGS = -g -c --std=c++17

# OS detection (Windows uses OS=Windows_NT)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist obj mkdir obj & if not exist bin mkdir bin
    RM = rmdir /S /Q
    EXE = .exe
    SLASH = \\
else
    MKDIR = mkdir -p
    RM = rm -rf
    EXE =
    SLASH = /
endif

# Targets
all:
	$(MKDIR)
	g++ $(FLAGS) src/main.cc -o obj$(SLASH)calc.o
	g++ -g -o bin$(SLASH)organizador$(EXE) obj$(SLASH)calc.o

clean:
	$(RM) bin
	$(RM) obj