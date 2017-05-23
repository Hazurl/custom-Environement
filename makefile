SRC_DIR := lib/Logger/src src/bash/AST src/bash src/system src
EXCLUDE := lib/Logger/src/main.cpp

SRC_ALL := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))
SRC := $(filter-out $(EXCLUDE),$(SRC_ALL))

BUILD_DIR := $(addprefix build/,$(SRC_DIR))

DEST := build/customEnv

OBJ := $(patsubst %.cpp,build/%.o,$(SRC))

OPTIM := -O2
FLAGS := -std=c++17 -g3 -Wall -Wextra -Wno-pmf-conversions
LIBS := 
MAKEFLAGS += --no-print-directory

all: build/customEnv

# Main build task
build/customEnv: $(BUILD_DIR) $(OBJ)
	@echo -n "\033[32m"
	g++ $(FLAGS) -o $(DEST) $(OBJ) $(LIBS)
	@echo -n "\033[34m"
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"
	@echo -n "\033[0m"

build/%.o: %.cpp
	g++ -c $(OPTIM) $(FLAGS) -o "$@" "$<"

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

again:
	@make clean
	@make build/customEnv

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
