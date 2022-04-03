# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 19:32:48 by nomargen          #+#    #+#              #
#    Updated: 2022/04/03 13:34:50 by nomargen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME		=	pipex

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra

SRC			=	$(wildcard  src/*.c)

HEAD		=	$(wildcard  inc/*.h)

OBJ			=	$(SRC:.c=.o)

LIBFT_DIR	=	lib/libft

LIBFT		=	$(addsuffix .a, $(LIBFT_DIR))

RM			=	rm -rf

LDLIBS		=	-lft


%.o: %.с  
	$(CC) $(CFLAGS) -c -o $@ $<

all:	$(NAME)

$(NAME): $(HEAD) $(OBJ) $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) -Llib $(LDLIBS)

$(LIBFT): $(LIBFT_DIR)/libft.a
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(LIBFT_DIR)/libft.a:
	make --directory=$(LIBFT_DIR) bonus

lib_clean:
	make --directory=$(LIBFT_DIR) fclean
	$(RM) lib/libft.a

fclean: clean
	$(RM) $(NAME)

clean: lib_clean
	$(RM) $(OBJ)

re: fclean all

.PHONY: all clean fclean lib_clean re