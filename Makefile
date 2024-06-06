NAME = libasm.a

# En-dessous : pour compiler la bibliothèque libasm.a
LIB = ar rcs
# on spécifie le compilateur assembleur. Sujet = nasm (= Netwide Assembler)
ASM = nasm
# option du compilateur assembleur. elf64(Executable and Linkable Format 64 bits) -> pour Linux/GNU
ASMFLAGS = -f elf64
INC = -Iincludes

# En-dessous : pour compiler le main de test !
CC = clang # NON ! Il vaut mieux compiler avec clang pour éviter les flags PIE (Clang sécurise cela par défaut ! Par contre il faudra revoir strcpy...)
CCFLAGS = -Wall -Wextra -Werror
SANITIZE = -g3 -fomit-frame-pointer

ASM_SRCS =  srcs/ft_strlen.s \
			srcs/ft_strcpy.s \
			srcs/ft_strcmp.s \
			srcs/ft_write.s \
			srcs/ft_read.s \
			srcs/ft_strdup.s \

ASM_OBJS = $(ASM_SRCS:%.s=%.o)

all: $(NAME)

$(NAME): $(ASM_OBJS)
	$(LIB) $(NAME) $(ASM_OBJS)

test: re
	$(CC) $(CCFLAGS) $(SANITIZE) main.c -o test_libasm $(NAME)
	touch test_file.txt

%.o: %.s
	$(ASM) $(ASMFLAGS) -o $@ $< $(INC)

clean:
	rm -rf $(ASM_OBJS)

fclean: clean
	rm -rf $(NAME) test_libasm test_file.txt

re: fclean all

# .PHONY: all bonus test clean fclean re
.PHONY: all test clean fclean re
