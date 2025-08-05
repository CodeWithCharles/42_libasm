# ---------------------------------------------------------------------------- #
#                                     CONFIG                                   #
# ---------------------------------------------------------------------------- #

ASCOMPILER	:= nasm
ASFLAGS		:= -felf64

CCOMPILER	:= cc
CFLAGS		:= -Wall -Wextra -Werror -Iinclude

OBJ_DIR		:= obj
BUILD_DIR	:= bin
TEST_DIR	:= tests

# ---------------------------------------------------------------------------- #
#                                  SOURCES                                     #
# ---------------------------------------------------------------------------- #

SRC_DIR		:= src/mandatory
BONUS_DIR	:= src/bonus

MANDATORY_SRCS ?=
BONUS_SRCS ?=

include Files_mandatory.mk
include Files_bonus.mk

MANDATORY_OBJS := $(MANDATORY_SRCS:%=$(OBJ_DIR)/mandatory/%.o)
BONUS_OBJS     := $(BONUS_SRCS:%=$(OBJ_DIR)/bonus/%.o)

# ---------------------------------------------------------------------------- #
#                               LIBRARY NAMES                                  #
# ---------------------------------------------------------------------------- #

MANDATORY_LIB := $(BUILD_DIR)/libasm.a
BONUS_LIB     := $(BUILD_DIR)/libasm_bonus.a

# ---------------------------------------------------------------------------- #
#                                 TEST FILES                                   #
# ---------------------------------------------------------------------------- #

MANDATORY_TEST_SRC := $(TEST_DIR)/main_mandatory.c
BONUS_TEST_SRC     := $(TEST_DIR)/main_bonus.c

MANDATORY_TEST_OBJ := $(OBJ_DIR)/main_mandatory.o
BONUS_TEST_OBJ     := $(OBJ_DIR)/main_bonus.o

MANDATORY_TEST_BIN := $(BUILD_DIR)/tester_mandatory
BONUS_TEST_BIN     := $(BUILD_DIR)/tester_bonus

# ---------------------------------------------------------------------------- #
#                                    RULES                                     #
# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re bonus test test_mandatory test_bonus run_mandatory run_bonus

all: $(MANDATORY_LIB)

bonus: $(BONUS_LIB)

# Build mandatory library
$(MANDATORY_LIB): $(MANDATORY_OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

# Build bonus library (includes mandatory + bonus)
$(BONUS_LIB): $(MANDATORY_OBJS) $(BONUS_OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

# Compile mandatory .s files to obj/mandatory/%.o
$(OBJ_DIR)/mandatory/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(ASCOMPILER) $(ASFLAGS) -o $@ $<

# Compile bonus .s files to obj/bonus/%.o
$(OBJ_DIR)/bonus/%.o: $(BONUS_DIR)/%.s
	@mkdir -p $(dir $@)
	$(ASCOMPILER) $(ASFLAGS) -o $@ $<

# Compile test files
$(MANDATORY_TEST_OBJ): $(MANDATORY_TEST_SRC)
	@mkdir -p $(dir $@)
	$(CCOMPILER) $(CFLAGS) -c $< -o $@

$(BONUS_TEST_OBJ): $(BONUS_TEST_SRC)
	@mkdir -p $(dir $@)
	$(CCOMPILER) $(CFLAGS) -c $< -o $@

# Link test binaries
$(MANDATORY_TEST_BIN): $(MANDATORY_TEST_OBJ) $(MANDATORY_LIB)
	$(CCOMPILER) $^ -o $@

$(BONUS_TEST_BIN): $(BONUS_TEST_OBJ) $(BONUS_LIB)
	$(CCOMPILER) $^ -o $@

# Test targets
test_mandatory: $(MANDATORY_TEST_BIN)
	./$(MANDATORY_TEST_BIN)

test_bonus: $(BONUS_TEST_BIN)
	./$(BONUS_TEST_BIN)

# Convenience aliases
run_mandatory: test_mandatory
run_bonus: test_bonus

# ---------------------------------------------------------------------------- #
#                                    CLEAN                                     #
# ---------------------------------------------------------------------------- #

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BUILD_DIR)

re: fclean all
