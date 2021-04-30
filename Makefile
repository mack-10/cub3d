CC			=	gcc
CFLAGS		=	-fsanitize=address -Wall -Wextra -Werror 
INC			=	-Iincludes
MLX			=	-Iminilibx -L. -lmlx -framework OpenGL -framework Appkit
NAME		=	cub3d
SRC_PATH	=	srcs/
SRC_NAME	=	main.c			\
				map.c			\
				raycasting_1.c	\
				raycasting_2.c	\
				floor_ceiling.c	\
				texture.c		\
				key_press.c		\
				parsing.c		\
				get_next_line.c	\
				set.c			\
				utils.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ_PATH	=	objs/
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB			=	libft

all : $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	mkdir objs 2>/dev/null || true
	$(CC) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	make -C $(LIB)
	make -C mlx
	cp mlx/libmlx.dylib .
	$(CC) $(MLX) $(OBJ) $(LIB)/$(LIB).a -o $(NAME)
	./cub3d sample.cub

clean :
	make clean -C $(LIB)
	make clean -C mlx
	rm -rf $(OBJ_PATH)

fclean : clean
	make fclean -C $(LIB)
	rm $(NAME)
	rm libmlx.dylib

re : fclean all

