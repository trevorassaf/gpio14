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
UNIT_TEST_EXEC = unit-tests
DEVICE_TEST_EXEC = device-tests

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
UNIT_TEST_MAIN_SOURCE = unit_test_main.cpp
DEVICE_TEST_MAIN_SOURCE = device_test_main.cpp

##########################
######### Recipes ########
##########################
# Scan for source files 
SOURCE_FILES := $(shell find $(SOURCE_DIR) -type f | grep -P '.*(?<!Test)\.cpp')
OBJECT_FILES := 
OBJECT_FILES_WITH_ROOT_SANS_MAIN = $(addprefix $(OBJECT_DIR)/,$(SOURCE_FILES:%.cpp=%.o))
UNIT_TEST_SOURCE_FILES := $(shell find $(SOURCE_DIR) -type f -name "*UnitTest.cpp")
DEVICE_TEST_SOURCE_FILES := $(shell find $(SOURCE_DIR) -type f -name "*DeviceTest.cpp")
SOURCE_INCLUDE_FLAGS = -I$(INCLUDE_DIR)
LIBS_LINKER_FLAGS = -L$(LIBS_DIR)

# GPIO object paths
GPIO_SOURCE_FILES = $(SOURCE_FILES) $(GPIO_MAIN_SOURCE) 
GPIO_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(GPIO_SOURCE_FILES:%.cpp=%.o))
GPIO_OBJECT_FILES = $(GPIO_SOURCE_FILES:%.cpp=%.o)

# I2C_SCAN object paths
I2C_SCAN_SOURCE_FILES = $(SOURCE_FILES) $(I2C_SCAN_MAIN_SOURCE) 
I2C_SCAN_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(I2C_SCAN_SOURCE_FILES:%.cpp=%.o))
I2C_SCAN_OBJECT_FILES = $(I2C_SCAN_SOURCE_FILES:%.cpp=%.o)

# Unit test paths
UNIT_TEST_AND_NON_UNIT_TEST_SOURCE_FILES = $(UNIT_TEST_SOURCE_FILES) $(UNIT_TEST_MAIN_SOURCE)
UNIT_TEST_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(UNIT_TEST_AND_NON_UNIT_TEST_SOURCE_FILES:%.cpp=%.o))
UNIT_TEST_OBJECT_FILES = $(UNIT_TEST_AND_NON_UNIT_TEST_SOURCE_FILES:%.cpp=%.o)

# Device test paths
DEVICE_TEST_AND_NON_DEVICE_TEST_SOURCE_FILES = $(DEVICE_TEST_SOURCE_FILES) $(DEVICE_TEST_MAIN_SOURCE)
DEVICE_TEST_OBJECT_FILES_WITH_ROOT = $(addprefix $(OBJECT_DIR)/,$(DEVICE_TEST_AND_NON_DEVICE_TEST_SOURCE_FILES:%.cpp=%.o))
DEVICE_TEST_OBJECT_FILES = $(DEVICE_TEST_AND_NON_DEVICE_TEST_SOURCE_FILES:%.cpp=%.o)

TEST_INCLUDE_FLAGS = -I$(GOOGLE_TEST_INCLUDE_DIR)
TEST_LIBRARY_FLAGS = -lgtest

# Compiler
CC_RASPBERRYPI = clang++-3.5
CC_LINUX = clang++
CC :=

# Compilation flags
CC_CORE_FLAGS_RASPBERRYPI = -w -Werror -Wall -pedantic -g -std=c++14 -I$(INCLUDE_DIR) -L$(LIBS_DIR) -lpthread
CC_CORE_FLAGS_LINUX = $(CC_CORE_FLAGS_RASPBERRYPI) -stdlib=libc++
CC_CORE_FLAGS :=

# Removed files
FILES_TO_REMOVE = \
		$(BINARY_DIR)/ \
		$(OBJECT_DIR)/

IS_HOST_RASPBERRYPI = $(shell uname -a | grep raspberrypi -c)

ifeq ($(IS_HOST_RASPBERRYPI),1)
	CC := $(CC_RASPBERRYPI)
	CC_CORE_FLAGS := $(CC_CORE_FLAGS_RASPBERRYPI)
else
	CC := $(CC_LINUX)
	CC_CORE_FLAGS := $(CC_CORE_FLAGS_LINUX)
endif

# Create compilation directories
.PHONY: directories

# Build all binaries
all: directories $(GPIO_EXEC) $(I2C_SCAN_EXEC) $(UNIT_TEST_EXEC) $(DEVICE_TEST_EXEC)

directories:
	@${MKDIR_P} $(BINARY_DIR)

# Compile blink binary
$(GPIO_EXEC): $(GPIO_OBJECT_FILES) 
	@$(CC) $(GPIO_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(GPIO_EXEC) $(CC_CORE_FLAGS)

$(I2C_SCAN_EXEC): $(I2C_SCAN_OBJECT_FILES) 
	@$(CC) $(I2C_SCAN_OBJECT_FILES_WITH_ROOT) -o $(BINARY_DIR)/$(I2C_SCAN_EXEC) $(CC_CORE_FLAGS)

$(UNIT_TEST_EXEC): $(UNIT_TEST_OBJECT_FILES)
	@$(CC) -o $(BINARY_DIR)/$(UNIT_TEST_EXEC) $(UNIT_TEST_OBJECT_FILES_WITH_ROOT) $(OBJECT_FILES_WITH_ROOT_SANS_MAIN) $(CC_CORE_FLAGS) $(TEST_INCLUDE_FLAGS) $(TEST_LIBRARY_FLAGS)

$(DEVICE_TEST_EXEC): $(DEVICE_TEST_OBJECT_FILES)
	@$(CC) -o $(BINARY_DIR)/$(DEVICE_TEST_EXEC) $(DEVICE_TEST_OBJECT_FILES_WITH_ROOT) $(OBJECT_FILES_WITH_ROOT_SANS_MAIN) $(CC_CORE_FLAGS) $(TEST_INCLUDE_FLAGS) $(TEST_LIBRARY_FLAGS)

# Compile non-test source
%.o: %.cpp
	@echo $(OBJECT_DIR)/$@
	@if [ -e $(dir $@) ] ; \
		then \
			${MKDIR_P} $(OBJECT_DIR)/$(dir $@) ; \
	fi;
	@$(CC) -c $< -o $(OBJECT_DIR)/$@ $(CC_CORE_FLAGS) $(TEST_INCLUDE_FLAGS)

# To remove generated files
clean:
	rm -rf $(FILES_TO_REMOVE) 
