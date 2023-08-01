.PHONY: all clean fclean re prod_reminder run

NAME := ft_traceroute

BUILD_TYPE := DEV

SRC_FILES := main.c cli.c slice.c slice_char.c slice_charptr.c ft_stdutil.c resolve.c ft_socket.c
INC_FILES := slice.h

SRCS_DIR := src
INCS_DIR := inc
OBJS_DIR := .objs

SRCS := $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
INCS := $(addprefix $(SRCS_DIR)/$(INCS_DIR)/, $(INC_FILES))
OBJS :=	$(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

CC := gcc
LD := gcc
RM := rm
MKDIR := mkdir

CFLAGS := $(CFLAGS) -g3 -Wall -Wextra -Werror -std=gnu89 -fsanitize=address -fsanitize=undefined -fstack-protector-all
LDFLAGS := $(LDFLAGS) -g3 -Wall -Wextra -Werror -std=gnu89 -fsanitize=address -fsanitize=undefined -fstack-protector-all

CFLAGS += -D$(BUILD_TYPE)=

all: $(NAME)

$(NAME):	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(BUILD_OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c Makefile $(INCS)
	@$(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -rf $(OBJS_DIR)

fclean: clean
	$(RM) -rf $(NAME)

re: fclean all

prod_reminder:
	@echo "Need to change BUILD_TYPE to PROD"
	@echo "Re-check headers and sources listing in Makefile"
	@echo "Launch the norm"
	@echo "Remove the -fsanitize=undefined"

run:	all
	./ft_traceroute localhost
