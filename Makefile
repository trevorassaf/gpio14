##########################
######## Commands ########
##########################
MKDIR_P = mkdir -p
RM_R = rm -rf

##########################
######## Binaries ########
##########################
GPIO_EXEC = gpio

##########################
####### Directories ######
##########################
BINARY_DIR = bin
OBJECT_DIR = bits
SOURCE_DIR = src
INCLUDE_DIR = include

##########################
####### Main Files #######
##########################
MAIN_SOURCE = main.cpp

##########################
######### Recipes ########
##########################

# Scan for source files 
SOURCE_FILES := $(shell find $(SOURCE_DIR) -name '*.cpp')

# Client object paths
GPIO_SOURCE_FILES = $(SOURCE_FILES) $(MAIN_SOURCE) 
GPIO_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(GPIO_SOURCE_FILES:%.cpp=%.o))
GPIO_OBJECT_FILES = $(GPIO_SOURCE_FILES:%.cpp=%.o)

# Declaration of variables
CC = g++
CC_FLAGS = -w -I$(INCLUDE_DIR) -std=c++1y -g

# Removed files
FILES_TO_REMOVE = \
		$(BINARY_DIR)/ \
		$(OBJECT_DIR)/

# Create compilation directories
.PHONY: directories

# Build all binaries
all: directories $(GPIO_EXEC)

directories:
	${MKDIR_P} $(BINARY_DIR)

# Compile blink binary
$(GPIO_EXEC): $(GPIO_OBJECT_FILES) 
	@$(CC) $(GPIO_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(GPIO_EXEC) -lpthread

# Compile source
%.o: %.cpp
	@echo $(OBJECT_DIR)/$@
	@if [ -e $(dir $@) ] ; \
		then \
			${MKDIR_P} $(OBJECT_DIR)/$(dir $@) ; \
	fi;
	@$(CC) -c $< -o $(OBJECT_DIR)/$@ $(CC_FLAGS) -lpthread

# To remove generated files
clean:
	rm -rf $(FILES_TO_REMOVE) 
