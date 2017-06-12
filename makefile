SRC_DIR_BASH := src/bash src/bash/AST 
SRC_DIR_UTILITIES := src/utilities
SRC_DIR_SYSTEM := src/system

SRC_DIR := $(SRC_DIR_BASH)
SRC_DIR += $(SRC_DIR_UTILITIES)
SRC_DIR += $(SRC_DIR_SYSTEM)
SRC_DIR += src

SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))
SRC_BASH := $(foreach d,$(SRC_DIR_BASH),$(wildcard $(d)/*.cpp))
SRC_UTILITIES := $(foreach d,$(SRC_DIR_UTILITIES),$(wildcard $(d)/*.cpp))
SRC_SYSTEM := $(foreach d,$(SRC_DIR_SYSTEM),$(wildcard $(d)/*.cpp))

BUILD_DIR := $(addprefix build/,$(SRC_DIR))
BUILD_DIR_BASH := $(addprefix build/,$(SRC_DIR_BASH))
BUILD_DIR_UTILITIES := $(addprefix build/,$(SRC_DIR_UTILITIES))
BUILD_DIR_SYSTEM := $(addprefix build/,$(SRC_DIR_SYSTEM))

DEST := build/customEnv

OBJ := $(patsubst %.cpp,build/%.o,$(SRC))
OBJ_BASH := $(patsubst %.cpp,build/%.o,$(SRC_BASH))
OBJ_UTILITIES := $(patsubst %.cpp,build/%.o,$(SRC_UTILITIES))
OBJ_SYSTEM := $(patsubst %.cpp,build/%.o,$(SRC_SYSTEM))

OPTIM := -O2
FLAGS := -std=c++17 -g3 -Wall -Wextra -Wno-pmf-conversions
LIBS := -llogger -lsfml-graphics -lsfml-window -lsfml-system
MAKEFLAGS += --no-print-directory

all: build/customEnv

# Main build task
# Compile each file and link them
build/customEnv: $(BUILD_DIR) $(OBJ)
	@echo "\033[32m\033[1m :: Linking of all objects\033[0m"
	@g++ $(FLAGS) $(OBJ) -o $(DEST) $(LIBS)
	@echo -n "\033[34m"
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"
	@echo -n "\033[0m"

# compile a file into a object
build/%.o: %.cpp
	@echo "\033[1m :: Building" "$<" "\033[0m"
	@g++ -c $(OPTIM) $(FLAGS) -o "$@" "$<"

#make build folders
$(BUILD_DIR):
	@mkdir -p $@

# Clean every build files by destroying the build/ folder.
clean:
	rm -rf build
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "Project  Cleaned"
	@echo "----------------"
	@echo -n "\033[0m"

# run the program
run: build/customEnv
	@clear
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Run       "
	@echo "----------------"
	@echo -n "\033[0m"
	@$(DEST)
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"
	@echo -n "\033[0m"

# delete all objects and recompile them
again:
	@make clean
	@make build/customEnv

# make again and then run with the "-t" argument
test: build/customEnv
	@clear
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "    Run Test    "
	@echo "----------------"
	@echo -n "\033[0m"
	@$(DEST) -t
	@echo -n "\033[34m"
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"
	@echo -n "\033[0m"

# Recompile the bash folder
bash:
	@rm -rf $(BUILD_DIR_BASH)
	@mkdir -p $(BUILD_DIR)
	@make $(OBJ_BASH)

# Equivalent of make again but only on bash folder
lbash:
	@make bash
	@make run

# Recompile the utilities folder
utilities:
	@rm -rf $(BUILD_DIR_UTILITIES)
	@mkdir -p $(BUILD_DIR)
	@make $(OBJ_UTILITIES)

# Equivalent of make again but only on utilities folder
lutilities:
	@make utilities
	@make run

# Recompile the system folder
system:
	@rm -rf $(BUILD_DIR_SYSTEM)
	@mkdir -p $(BUILD_DIR)
	@make $(OBJ_SYSTEM)

# Equivalent of make again but only on system folder
lsystem:
	@make system
	@make run
