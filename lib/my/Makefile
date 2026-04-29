##
## EPITECH PROJECT, 2026
## libmy.a
## File description:
## Makefile
##

CC	:=	epiclang

CPPFLAGS	+=	-iquote ./include/
CFLAGS		+=	-Wall -Wextra
LDFLAGS		+=	-L lib
LDLIBS		+=	-l my


TESTS_FOLDER	=	tests/



GCOVR_FLAGS		=	--gcov-executable "llvm-cov-20 gcov" --exclude $(TESTS_FOLDER)
GCOVR_BRANCH	=	--branch
VALGRIND_FLAGS	=	--leak-check=full --show-leak-kinds=all



SRC			=	my_compute_power_rec.c						\
				my_file_tool_functions.c					\
				my_free_tools_functions.c					\
				my_getnbr.c									\
				my_nbr_to_str_functions.c					\
				my_put_nbr.c								\
				my_putchar.c								\
				my_putstr.c									\
				my_search_into_str_functions.c				\
				my_show_word_array.c						\
				my_str_concat.c								\
				my_str_isnum.c								\
				my_str_tools_functions.c					\
				my_strcmp.c									\
				my_strdup.c									\
				my_strlen.c									\
				my_word_array_len.c							\
				my_word_array_tools.c

MAIN_SRC	=	# main file

TESTS_SRC	=	# unit tests src files


OBJ			=	$(SRC:.c=.o)
MAIN_OBJ	=	$(MAIN_SRC:.c=.o)
TESTS_OBJ	=	$(TESTS_SRC:.c=.o)


DELIVERY_NAME	=	../libmy.a # delivery binary name
MAIN_NAME		=	libmy_test # binary including main name
TESTS_NAME		=	unit_tests



all: $(OBJ) $(MAIN_OBJ)
	ar rc $(DELIVERY_NAME) $(OBJ)



clean:
	$(RM) -f *~ \#*\#
	$(RM) -f $(OBJ)
	$(RM) $(MAIN_OBJ) $(TESTS_OBJ)

fclean: clean
	$(RM) -f $(NAME)
	$(RM) -f $(MAIN_NAME) $(TESTS_NAME)
	$(RM) -f *.gc*

re: fclean all


build_main: all
	$(CC) -o $(MAIN_NAME) $(OBJ) $(MAIN_OBJ) -L lib -l my

runmain: build_main
	./$(MAIN_NAME)



tests_clean: fclean

unit_tests: LDFLAGS += --coverage -lcriterion -lgcov
unit_tests: fclean $(OBJ) $(TESTS_OBJ)
	$(CC) -o $(TESTS_NAME) $(OBJ) $(TESTS_OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

tests_run: unit_tests
	./$(TESTS_NAME)

cover: unit_tests
	gcovr $(GCOVR_FLAGS)
	gcovr $(GCOVR_FLAGS) $(GCOVR_BRANCH)

tests_all: tests_run cover



gdebug: CFLAGS += -g
gdebug: fclean all

vdebug: CPPFLAGS += -g3
vdebug: fclean all

debug: CFLAGS += -g
debug: CPPFLAGS += -g3
debug: fclean all



.PHONY: all clean fclean re build_main runmain tests_clean unit_tests tests_run cover tests_all gdebug vdebug debug
