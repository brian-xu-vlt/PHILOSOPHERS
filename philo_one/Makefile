NAME := $(lastword $(subst /, ,$(dir $(realpath $(lastword $(MAKEFILE_LIST))))))
INCLUDES = ./includes/
SRCS_DIR = ./srcs/
CC = gcc
OBJ_DIR = ../objs/$(NAME)/

CFLAGS += -pthread
CFLAGS += -Wall
CFLAGS += -Wextra
# CFLAGS += -fPIC

ifeq ($(help), 1)
	CFLAGS += -Wconversion
else ifeq ($(help), 2)
	CFLAGS += -Wsuggest-attribute=pure
else ifeq ($(help), 3)
	CFLAGS += -Wsuggest-attribute=const
else ifeq ($(help), 4)
	CFLAGS += -Wsuggest-attribute=noreturn
else ifeq ($(help), 5)
	CFLAGS += -fsanitize-undefined-trap-on-error
else ifneq ($(no_error), 1)
	CFLAGS += -Werror
endif

ifeq ($(debug), 1)
	CFLAGS += -g3
else ifeq ($(debug), 2)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
else ifeq ($(debug), 3)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
	ifneq ($(CC), gcc)
		CFLAGS += -Weverything
	endif
endif

ifeq ($(opti), 1)
	CFLAGS += -O3
endif

ifeq ($(debug_mode), 1)
	CFLAGS += -D DEBUG_MODE=1
endif

HEADER += $(INCLUDES)philo.h

SRCS += main.c
SRCS += process_threads.c
SRCS += process_threads_utils.c
SRCS += general_utils.c
SRCS += state_machine.c
SRCS += state_machine_action_handlers.c
SRCS += state_machine_fork_acquisition.c
SRCS += state_machine_utils.c
SRCS += monitor.c
SRCS += status_printer.c
SRCS += status_printer_str.c
SRCS += status_printer_nbr.c
SRCS += arguments_process.c
SRCS += timer.c
SRCS += cleanup_routine.c

vpath %.c ./
vpath %.c ./srcs
vpath %.c ./srcs/monitor
vpath %.c ./srcs/state_machine
vpath %.c ./srcs/thread_processor
vpath %.c ./srcs/utils

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all :
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -o $@
	@echo "\033[32m$@ is ready !\033[0m"

$(OBJ_DIR):
	mkdir -p $@

FORCE :

clean :
	$(RM) -R $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean
	$(MAKE)

norme :
	~/.norminette/norminette.rb $(SRCS_DIR) $(INCLUDES)

f : all
	./$(NAME)

.PHONY: all clean fclean mclean re FORCE
#.SILENT:
