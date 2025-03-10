##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## this is the makefile for matchstick
##

NAME		=		terramorphus

NAMET		=		${NAME}_tests

NAMEB		=		${NAME}_bonus

NAMES		=		server

SRC_PATH	=		src

TEST_PATH	=		tests

BONUS_PATH	=		bonus/src

SRC			=		${SRC_PATH}/main.c							\
					${SRC_PATH}/usage.c							\
					${SRC_PATH}/live_coding.c					\
					${SRC_PATH}/error_handling.c				\
					${SRC_PATH}/map.c							\
					${SRC_PATH}/button.c				\

SRCT		=		${TEST_PATH}/tests.c						\

OBJ			=		${SRC:.c=.o}

OBJT		=		${SRCT:.c=.o}

RM			=		rm -rf

CFLAGS		=		-Wall -Wextra

CPPFLAGS	=		-I./includes

LDFLAGS		=		-L./lib

LDLIBS		=		-lmy -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

CC			=		gcc

all:	${NAME}

${NAME}:	${OBJ} make_lib
	${CC} -o ${NAME} ${OBJ} ${LDFLAGS} ${LDLIBS} -g3

debug:	CFLAGS += -g

debug:	${OBJ} make_debug_lib
	${CC} -o ${NAME} ${OBJ} ${LDFLAGS} ${LDLIBS}

make_debug_lib:
	make debug -C lib

make_lib:
	make -C lib

clean:
	${RM} ${OBJ}
	${RM} ${OBJT}
	make clean -C lib

fclean:	clean
	${RM} ${NAME}
	${RM} ${NAMET} ${TEST_PATH}/*.gc* ${SRC_PATH}/*.gc*
	make fclean -C lib

re:	fclean	${NAME}

unit_test:	CFLAGS += -fprofile-arcs -ftest-coverage

unit_test:	LDLIBS += -lcriterion -lgcov

unit_test:
	${CC} -o ${NAMET} tests/test_my_rpg.c src/usage.c -lcriterion -lgcov -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

tests_run:	unit_test
	./${NAMET}

coverage:
	gcovr --exclude tests

branches:
	gcovr --branches --exclude tests

.PHONY:	all ${NAME} make_lib clean fclean re unit_test tests_run
.PHONY:	coverage branches bonus
