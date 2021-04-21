CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
INC			=	-Iincludes
MLX			=	-Iminilibx -L. -lmlx -framework OpenGL -framework Appkit
NAME		=	cub3d
SRC_PATH	=	srcs/
SRC_NAME	=	main.c			\
				map.c			\
				raycasting.c	\
				texture.c		\
				key_press.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ_PATH	=	objs/
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

all : $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	mkdir objs 2>/dev/null || true
	$(CC) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(MLX) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ_PATH)

fclean : clean
	rm $(NAME)

re : fclean all

