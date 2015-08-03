#### PROJECT SETTINGS ####
# Compiler used
CXX = g++
# Program name
NAME = platformer
# Extension of source files used in the project
SRC_EXT = cpp
# Path to the source directory, relative to the makefile
SRC_PATH = src
# Header extention
HEADER_EXT = h
# Header location
HEADER_PATH = ./include
# Standard header that should be precompiled
STANDARD_H = $(HEADER_PATH)/Standard.h
STANDARD_GCH = $(STANDARD_H).gch
# Extra compiler settings
EXTRA = -Wno-write-strings #-Wno-deprecated
# Preprocessor defs
DEFS = -DDEBUG_MODE=true -DDRAW_BOX=false -DLEGACY=false -DTPS=60 -DSCALE=2
# General compiler flags
COMPILE_FLAGS = -std=c++14 -Wall -Wextra -g $(EXTRA) $(DEFS)
# Add additional include paths
INCLUDES = -I $(HEADER_PATH)
# Destination directory, like a jail or mounted system
DESTDIR = /
# Used libraries
LIBS = glew glfw3 $(shell pkg-config --print-requires --print-requires-private glfw3)
LIBSwin = -lglew32 -lglfw3 -lopengl32
#### END PROJECT SETTINGS ####

SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
		    | sort -k 1nr | cut -f2-)

HEADERS = $(shell find $(HEADER_PATH) -name '*.$(HEADER_EXT)' -printf '%T@\t%p\n' \
		    | sort -k 1nr | cut -f2-)

all: $(STANDARD_GCH) $(NAME)

windows: $(STANDARD_GCH)-win $(NAME)-win

$(NAME): $(SOURCES) $(HEADERS) ./Makefile
	$(CXX) $(SOURCES) $(COMPILE_FLAGS) $(shell pkg-config --libs --cflags $(LIBS)) $(INCLUDES) -H -o $(NAME)

$(STANDARD_GCH): $(HEADERS) ./Makefile
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) $(STANDARD_H) 

$(NAME)-win: $(SOURCES) $(HEADERS) ./Makefile
	x86_64-w64-mingw32-$(CXX) $(SOURCES) $(COMPILE_FLAGS) $(INCLUDES) $(LIBSwin) -H -o $(NAME).exe

$(STANDARD_GCH)-win: $(HEADERS) ./Makefile
	x86_64-w64-mingw32-$(CXX) $(COMPILE_FLAGS) $(INCLUDES) $(STANDARD_H) 

execute:
	./$(NAME)

# clean:
# 	rm -f $(NAME)
