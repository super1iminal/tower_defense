# Where SFML is installed (for MSYS2 MinGW 64-bit)
SFML_INCLUDE = /mingw64/include
SFML_LIB     = /mingw64/lib

# Find all .cpp files in "src" folder
cppFileNames := $(shell find src -type f -name "*.cpp")

all: main.exe

main.exe: $(cppFileNames)
	@echo "Compiling..."
	mkdir -p bin
	g++ $^ -I$(SFML_INCLUDE) \
	    -o bin/main.exe \
	    -L$(SFML_LIB) \
	    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
	@echo "Build complete!"
