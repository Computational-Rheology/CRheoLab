#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS := -std=c++11 -g -Wall -I../../src -I/usr/local/Cellar/boost/1.78.0_1/include/

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -lboost_filesystem -lboost_system -L/usr/local/Cellar/boost/1.78.0_1/lib/

# define output directory
OUTPUT := ../../run

# define source directory
SRC_DIR := ../../src

# define obj directory
OBJ_DIR := ../../obj

# define bin directory
BIN_DIR := ../../bin

MAIN := ../../bin/csrSpmat_test

FIXPATH = $1
RM = rm -f
MD := mkdir -p

# define the C source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp *.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

### To create automatically the obj and bin directory
$(shell $(MD) $(OBJ_DIR))
$(shell $(MD) $(BIN_DIR))

$(MAIN): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c  -o $@ $<

.PHONY: clean
clean:
	$(RM) $(MAIN)
	@echo Cleanup complete!

runs: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!!
