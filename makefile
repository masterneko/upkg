CXX := g++
CC := gcc

SRC_DIRECTORY = src
OBJ_DIRECTORY = obj
BIN_DIRECTORY = bin

CREATE_DIRS = mkdir -p $(@D)

CFLAGS := \
		-I $(SRC_DIRECTORY)

LFLAGS :=

SOURCES := \
		$(wildcard $(SRC_DIRECTORY)/*.c) \
		$(wildcard $(SRC_DIRECTORY)/*/*.c)
HEADERS := \
		$(wildcard $(SRC_DIRECTORY)/*.h) \
		$(wildcard $(SRC_DIRECTORY)/*/*.h)

OBJECTS := $(SOURCES:$(SRC_DIRECTORY)/%.c=$(OBJ_DIRECTORY)/%.o)

all: $(BIN_DIRECTORY)/upkg.out

$(BIN_DIRECTORY)/upkg.out: $(OBJECTS)
	@$(CREATE_DIRS)
	@echo "linking"
	@$(CXX) $(OBJECTS) -o $@ $(LFLAGS)

$(OBJ_DIRECTORY)/%.o: $(SRC_DIRECTORY)/%.c $(HEADERS)
	@$(CREATE_DIRS)
	@echo "$@"
	@$(CXX) -c $< -o $@ $(CFLAGS)

clean:
	@rm -rf $(OBJ_DIRECTORY)
	@rm -rf $(BIN_DIRECTORY)