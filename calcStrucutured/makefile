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
all: obj bin \
	obj$(SLASH)main.o \
	obj$(SLASH)Users.o \
	obj$(SLASH)Calculator.o \
	obj$(SLASH)Parser.o \
	obj$(SLASH)Controller.o \
    obj$(SLASH)Utility.o \
    obj$(SLASH)Encryption.o \
	bin$(SLASH)calculator$(EXE)

# Compile source files
obj$(SLASH)main.o:
	g++ $(FLAGS) main.cc -o obj$(SLASH)main.o

obj$(SLASH)Users.o:
	g++ $(FLAGS) Domain/Entities/Users.cc -o obj$(SLASH)Users.o

obj$(SLASH)Calculator.o:
	g++ $(FLAGS) Domain/Entities/Calculator.cc -o obj$(SLASH)Calculator.o

obj$(SLASH)Parser.o:
	g++ $(FLAGS) Domain/Entities/Parser.cc -o obj$(SLASH)Parser.o

obj$(SLASH)Controller.o:
	g++ $(FLAGS) Domain/Entities/Controller.cc -o obj$(SLASH)Controller.o

obj$(SLASH)Utility.o:
	g++ $(FLAGS) Domain/Entities/Utility.cc -o obj$(SLASH)Utility.o

obj$(SLASH)Encryption.o:
	g++ $(FLAGS) Domain/Encryption/Encryption.cc -o obj$(SLASH)Encryption.o

# Link object files into final binary
bin$(SLASH)calculator$(EXE):
	g++ -g -o bin$(SLASH)calculator$(EXE) \
	obj$(SLASH)main.o \
	obj$(SLASH)Users.o \
	obj$(SLASH)Calculator.o \
	obj$(SLASH)Parser.o \
	obj$(SLASH)Controller.o \
    obj$(SLASH)Utility.o \
    obj$(SLASH)Encryption.o 

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
