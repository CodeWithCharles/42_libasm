# ---------------------------------------------------------------------------- #
#                                     CONFIG                                   #
# ---------------------------------------------------------------------------- #

ASCOMPILER	:=	nasm
ASFLAGS		:=	-felf64

CCOMPILER	:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -Iinclude

NAME		:=	bin/libasm.a

SRC_DIR		:=	src/mandatory
BONUS_DIR	:=	src/bonus

OBJ_DIR		:=	obj
BUILD_DIR	:=	bin

# ---------------------------------------------------------------------------- #
#                                  SOURCES                                     #
# ---------------------------------------------------------------------------- #

MANDATORY_SRCS	?=
BONUS_SRCS		?=

include Files_mandatory.mk
include Files_bonus.mk

MANDATORY_OBJS	:=	$(MANDATORY_SRCS:%=$(OBJ_DIR)/%.o)
BONUS_OBJS		:=	$(BONUS_SRCS:%=$(OBJ_DIR)/%.o)

# ---------------------------------------------------------------------------- #
#                                    TESTING                                   #
# ---------------------------------------------------------------------------- #

TEST_DIR	:=	tests
TEST_BIN	:=	$(BUILD_DIR)/tester
TEST_SRC	:=	main.c
TEST_OBJ	:=	$(OBJ_DIR)/main.o

# ---------------------------------------------------------------------------- #
#                                    RULES                                     #
# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re bonus test

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	@mkdir -p $(dir $@)
	@ar rcs $(NAME) $^

bonus: $(MANDATORY_OBJS) $(BONUS_OBJS)
	@mkdir -p $(dir $(NAME))
	@ar rcs $(NAME) $^

# ---------------------------------------------------------------------------- #
#                                   OBJECTS                                    #
# ---------------------------------------------------------------------------- #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(ASCOMPILER) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.s
	@mkdir -p $(dir $@)
	$(ASCOMPILER) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/main.o: $(TEST_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	$(CCOMPILER) -c -o $@ $< $(CFLAGS)

# ---------------------------------------------------------------------------- #
#                                     TESTS                                    #
# ---------------------------------------------------------------------------- #

test: $(TEST_BIN)

run_tests: test
	@./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(NAME)
	$(CCOMPILER) -o $@ $^ $(CFLAGS)

# ---------------------------------------------------------------------------- #
#                                    CLEAN                                     #
# ---------------------------------------------------------------------------- #

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BUILD_DIR)/libasm.a $(BUILD_DIR)/tester

re: fclean all
