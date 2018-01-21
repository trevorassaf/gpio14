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
TEST_EXEC = test

##########################
####### Directories ######
##########################
BINARY_DIR = bin
OBJECT_DIR = bits
SOURCE_DIR = src
INCLUDE_DIR = include
LIBS_DIR = libs
EXTERNAL_DIR = external
GOOGLE_TEST_DIR = $(EXTERNAL_DIR)/googletest
GOOGLE_TEST_INCLUDE_DIR = $(GOOGLE_TEST_DIR)/include

##########################
####### Main Files #######
##########################
GPIO_MAIN_SOURCE = gpio_main.cpp
I2C_SCAN_MAIN_SOURCE = i2c_scan_main.cpp
TEST_MAIN_SOURCE = test_main.cpp

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

# Test paths
TEST_SOURCE_FILES = $(SOURCE_FILES) $(TEST_MAIN_SOURCE)
TEST_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(TEST_SOURCE_FILES:%.cpp=%.o))
TEST_OBJECT_FILES = $(TEST_SOURCE_FILES:%.cpp=%.o)

# Compiler
CC_RASPBERRYPI = clang++-3.5
CC_LINUX = clang++
CC = ${CC_LINUX}

# Compilation flags
CC_FLAGS_RASPBERRYPI = -w -I$(INCLUDE_DIR) -L$(LIBS_DIR) -std=c++14 -g -lpthread
CC_FLAGS_LINUX = $(CC_FLAGS_RASPBERRYPI) -stdlib=libc++
CC_FLAGS = $(CC_FLAGS_LINUX)
CC_FLAGS_TEST_CORE = -I$(GOOGLE_TEST_INCLUDE_DIR) -lgtest
CC_FLAGS_TEST_RASPBERRYPI = $(CC_FLAGS_RASPBERRYPI) $(CC_FLAGS_TEST_CORE)
CC_FLAGS_TEST_LINUX = $(CC_FLAGS_LINUX) $(CC_FLAGS_TEST_CORE)
CC_FLAGS_TEST = $(CC_FLAGS_TEST_LINUX)

# Removed files
FILES_TO_REMOVE = \
		$(BINARY_DIR)/ \
		$(OBJECT_DIR)/

IS_HOST_RASPBERRYPI = $(shell uname -a | grep raspberrypi)
NON_RASPBERRYPI_TEST_STRING = ""

# Create compilation directories
.PHONY: directories

# Build all binaries
all: detect-host directories $(GPIO_EXEC) $(I2C_SCAN_EXEC) $(TEST_EXEC)

detect-host:
	@if [ "${IS_HOST_RASPBERRYPI}" = "${NON_RASPBERRYPI_TEST_STRING}" ] ; \
		then \
			CC="${CC_RASPBERRYPI}" ; \
			CC_FLAGS="${CC_FLAGS_RASPBERRYPI}" ; \
	fi;

directories:
	@${MKDIR_P} $(BINARY_DIR)

# Compile blink binary
$(GPIO_EXEC): $(GPIO_OBJECT_FILES) 
	$(CC) $(GPIO_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(GPIO_EXEC) $(CC_FLAGS)

$(I2C_SCAN_EXEC): $(I2C_SCAN_OBJECT_FILES) 
	$(CC) $(I2C_SCAN_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(I2C_SCAN_EXEC) $(CC_FLAGS)

$(TEST_EXEC): $(TEST_OBJECT_FILES)
	$(CC) $(TEST_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(TEST_EXEC) $(CC_FLAGS_TEST)
	#clang++ test_main.cpp -Igoogletest/googletest/include -Lgoogletest-build/googlemock/gtest -lgtest -lpthread -o test

# Compile source
%.o: %.cpp
	@echo $(OBJECT_DIR)/$@
	@if [ -e $(dir $@) ] ; \
		then \
			${MKDIR_P} $(OBJECT_DIR)/$(dir $@) ; \
	fi;
	$(CC) -c $< -o $(OBJECT_DIR)/$@ $(CC_FLAGS_TEST)

# To remove generated files
clean:
	rm -rf $(FILES_TO_REMOVE) 
