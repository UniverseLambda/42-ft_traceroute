.PHONY: all clean fclean re prod_reminder run

NAME := ft_traceroute

BUILD_TYPE := PROD

SRC_FILES := cli.c \
				ft_icmp.c \
				ft_socket.c \
				ft_stdutil.c \
				ft_store_val.c \
				ft_store.c \
				ft_time.c \
				main.c \
				numutil.c \
				print_time.c \
				resolve.c \
				resp_inf.c \
				slice_char.c \
				slice_charptr.c \
				slice.c \
				window.c

INC_FILES := base.h \
				cli.h \
				ft_icmp.h \
				ft_socket.h \
				ft_stdutil.h \
				ft_store.h \
				ft_time.h \
				numutil.h \
				print_time.h \
				resolve.h \
				resp_inf.h \
				slice.h \
				window.h

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
