CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror 
INC			=	-Iincludes
MLX			=	-Iminilibx -L. -lmlx -framework OpenGL -framework Appkit
NAME		=	cub3D
SRC_PATH	=	srcs/
SRC_NAME	=	main.c			\
				check.c			\
				main_loop.c		\
				cub_val_1.c		\
				cub_val_2.c		\
				get_next_line.c	\
				map.c			\
				check_map.c		\
				floor_ceiling.c	\
				raycasting_1.c	\
				raycasting_2.c	\
				load_texture.c	\
				sprite.c		\
				draw.c			\
				bmp.c			\
				key_press.c		\
				set.c			\
				utils.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ_PATH	=	objs/
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB			=	libft

MFLAG = -fsanitize=address -g

all : $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	mkdir objs 2>/dev/null || true
	$(CC) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	make -C $(LIB)
	make -C mlx
	cp mlx/libmlx.a .
	$(CC) $(MLX) $(OBJ) $(LIB)/$(LIB).a -o $(NAME)

clean :
	make clean -C $(LIB)
	make clean -C mlx
	rm -rf $(OBJ_PATH)

fclean : clean
	make fclean -C $(LIB)
	rm $(NAME)
	rm libmlx.a

re : fclean all

