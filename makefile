NAME					= philo

CC						= cc
CFLAGS					= -Wall -Wextra -Werror
HEADERS					= -I inc

SRC_DIR					= src
OBJ_DIR					= .obj

SOURCES					=	cleanup.c \
							dinner_monitor.c \
							main.c \
							parse_args.c \
							routine_activities.c \
							routine.c \
							set_dining_table.c \
							threads.c \
							utils.c

OBJECTS					= $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)


$(NAME): $(OBJ_DIR) $(OBJECTS)
				@echo "Building $(NAME)..."
				@$(CC) $(OBJECTS) $(CFLAGS) -o $(NAME) -g 
#-fsanitize=thread

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				@echo "Compiling $< into $@..."
				@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
				@echo "Removed object files..."
				@rm -fr $(OBJ_DIR)

fclean: clean
				@echo "Removed executable..."
				@rm -fr $(NAME)

re:	 fclean all

.PHONY: all clean fclean re