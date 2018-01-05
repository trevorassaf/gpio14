##########################
###### Dependencies ######
##########################
# clang 5.0

##########################
######## Commands ########
##########################
MKDIR_P = mkdir -p
RM_R = rm -rf

##########################
######## Binaries ########
##########################
GPIO_EXEC = gpio
I2C_SCAN_EXEC = i2c-scan

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
GPIO_MAIN_SOURCE = gpio_main.cpp
I2C_SCAN_MAIN_SOURCE = i2c_scan_main.cpp

##########################
######### Recipes ########
##########################

# Scan for source files 
SOURCE_FILES := $(shell find $(SOURCE_DIR) -name '*.cpp')

# GPIO object paths
GPIO_SOURCE_FILES = $(SOURCE_FILES) $(GPIO_MAIN_SOURCE) 
GPIO_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(GPIO_SOURCE_FILES:%.cpp=%.o))
GPIO_OBJECT_FILES = $(GPIO_SOURCE_FILES:%.cpp=%.o)

# I2C_SCAN object paths
I2C_SCAN_SOURCE_FILES = $(SOURCE_FILES) $(I2C_SCAN_MAIN_SOURCE) 
I2C_SCAN_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(I2C_SCAN_SOURCE_FILES:%.cpp=%.o))
I2C_SCAN_OBJECT_FILES = $(I2C_SCAN_SOURCE_FILES:%.cpp=%.o)

# Compiler
CC_RASPBERRYPI = clang++-3.5
CC_LINUX = clang++
CC = ${CC_LINUX}

# Compilation flags
CC_FLAGS_RASPBERRYPI = -w -I$(INCLUDE_DIR) -std=c++14 -g
CC_FLAGS_LINUX = ${CC_FLAGS_RASPBERRYPI} -stdlib=libc++
CC_FLAGS = ${CC_FLAGS_LINUX}

# Removed files
FILES_TO_REMOVE = \
		$(BINARY_DIR)/ \
		$(OBJECT_DIR)/

# Create compilation directories
.PHONY: directories

# Build all binaries
all: detect-host directories $(GPIO_EXEC) $(I2C_SCAN_EXEC)

detect-host:
	@host_name=$(uname -a)
	@if [ $$host_name == *"raspberrypi"* ] ; \
		then \
			CC=${CC_RASPBERRYPI} ; \
			CC_FLAGS=${CC_FLAGS_RASPBERRYPI} ; \
	fi;

directories:
	${MKDIR_P} $(BINARY_DIR)

# Compile blink binary
$(GPIO_EXEC): $(GPIO_OBJECT_FILES) 
	@$(CC) $(GPIO_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(GPIO_EXEC) $(CC_FLAGS) -lpthread

$(I2C_SCAN_EXEC): $(I2C_SCAN_OBJECT_FILES) 
	@$(CC) $(I2C_SCAN_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(I2C_SCAN_EXEC) $(CC_FLAGS) -lpthread

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
