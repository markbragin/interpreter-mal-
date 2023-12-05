# 'make'       - build binary file $(BINARY)
# 'make clean' - clean dependencies, object files and binary
# 'make run'   - build and run $(BINARY)
# NO DIRECTORY NAME SHOULD HAVE ANY WHITESPACE

# copmpiler flags
CXX := g++

CXXFLAGS := -std=c++17 -Wall -Werror -Wfloat-equal -g -fsanitize=undefined \
            -fno-sanitize-recover -fstack-protector -fsanitize=address

# lib flags
LFLAGS := -lboost_regex

# root directory for source files
ROOT_SOURCE_DIR  := src
# root directory for obj
ROOT_OBJ_DIR     := obj
# binary name
BINARY := step4_if_fn_do

# for UNIX
RM := rm -rf
MD := mkdir -p

# define source files
SOURCE_DIRS  := $(shell find $(ROOT_SOURCE_DIR) -type d)
SOURCES      := $(wildcard $(patsubst %, %/*.cpp, $(SOURCE_DIRS)))

# define object files
OBJECT_DIRS := $(patsubst $(ROOT_SOURCE_DIR)%, $(ROOT_OBJ_DIR)%, $(SOURCE_DIRS))
OBJECTS      := $(SOURCES:$(ROOT_SOURCE_DIR)/%.cpp=$(ROOT_OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:%.o=%.d)

# creates OBJECT_DIRS if don't exist
$(shell $(MD) $(OBJECT_DIRS))


# default_goal
all: $(BINARY)
	$(RM) $(DEPENDENCIES)
	@echo BUILDING COMPLETED

# build the program
$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

# create the dependency rules
$(ROOT_OBJ_DIR)/%.d: $(ROOT_SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -MM -MT $(@:%.d=%.o) > $@

# include .d files
-include $(DEPENDENCIES)

# building rules for .o files
%.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@


# release configuration
.PHONY: release
release: CXXFLAGS := -std=c++17 -Wall -Weffc++ -Wextra -Werror -pedantic -O3 -s
release: $(BINARY)
	@echo "RELEASE CONFIGURATION BUILDING COMPLETED"

# clean obj directory and binary
.PHONY: clean
clean:
	$(RM) $(ROOT_OBJ_DIR) $(BINARY)
	@echo
	@echo CLEANUP COMPLETE!

# build and run
.PHONY: run
run: all
	./$(BINARY)

