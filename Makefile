##
## EPITECH PROJECT, 2026
## G2 - Elementary Programming in C - Corewar
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



SRC			=	# src files

MAIN_SRC	=	src/main.c # main file

TESTS_SRC	=	# unit tests src files


OBJ			=	$(SRC:.c=.o)
MAIN_OBJ	=	$(MAIN_SRC:.c=.o)
TESTS_OBJ	=	$(TESTS_SRC:.c=.o)


DELIVERY_NAME	=	delivery # delivery binary name
TESTS_NAME		=	unit_tests



all: $(OBJ) $(MAIN_OBJ)
	$(MAKE) -C lib/my/
	$(CC) -o $(DELIVERY_NAME) $(OBJ) $(MAIN_OBJ) $(LDFLAGS) $(LDLIBS)



clean:
	$(MAKE) clean -C lib/my/
	$(RM) -f *~ \#*\#
	$(RM) -f $(OBJ) $(MAIN_OBJ) $(TESTS_OBJ)

fclean: clean
	$(MAKE) fclean -C lib/my/
	$(RM) -f $(DELIVERY_NAME) $(TESTS_NAME)
	$(RM) -f *.gc*

re: fclean all



runmain: all
	./$(DELIVERY_NAME)



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



glibmy:
	$(MAKE) gdebug -C lib/my/

vlibmy:
	$(MAKE) vdebug -C lib/my/

dlibmy:
	$(MAKE) debug -C lib/my/


gdebug: CFLAGS += -g
gdebug: clean glibmy all
	gdb ./$(DELIVERY_NAME)

vdebug: CPPFLAGS += -g3
vdebug: clean vlibmy all
	valgrind $(VALGRIND_FLAGS) ./$(DELIVERY_NAME)

debug: CFLAGS += -g
debug: CPPFLAGS += -g3
debug: clean dlibmy re



.PHONY: all clean fclean re runmain tests_clean unit_tests tests_run cover tests_all glibmy vlibmy dlibmy gdebug vdebug debug
