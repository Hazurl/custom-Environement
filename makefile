SRC_DIR := src/bash src

SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))

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
	g++ $(FLAGS) -o $(DEST) $(OBJ) $(LIBS)
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"

build/%.o: %.cpp
	g++ -c $(OPTIM) $(FLAGS) -o "$@" "$<"

$(BUILD_DIR):
	@mkdir -p $@

# Clean every build files by destroying the build/ folder.
clean:
	rm -rf build
	@echo "----------------"
	@echo "Project  Cleaned"
	@echo "----------------"


run: build/customEnv
	@clear
	@echo "----------------"
	@echo "      Run       "
	@echo "----------------"
	@$(DEST)
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"

again:
	@make clean
	@make build/customEnv

test: build/customEnv
	@clear
	@echo "----------------"
	@echo "    Run Test    "
	@echo "----------------"
	@$(DEST) -t
	@echo "----------------"
	@echo "      Stop      "
	@echo "----------------"
