# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/12 10:04:51 by ealexa            #+#    #+#              #
#    Updated: 2021/01/21 17:22:55 by ealexa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	sources/main.c sources/other.c sources/parce_map.c sources/errors.c sources/parce_init_int.c sources/parce_init_map.c sources/parce_init_param.c sources/sprite.c sources/screen.c sources/utils.c sources/keys.c sources/hooks.c sources/render.c sources/drow_column.c



OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm libftprintf.a
MLX				= libmlx.dylib
LIBFT			= libftprintf.a

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C printf
				@mv printf/$(LIBFT) .
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				@$(MAKE) -C mlx clean
				@$(MAKE) -C printf clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX) $(LIBFT)

re:				fclean $(NAME)

bonus:			all

.PHONY:			all clean fclean re