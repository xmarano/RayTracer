##
## EPITECH PROJECT, 2024
## B-OOP-400-MAR-4-1-raytracer-selim.bouasker
## File description:
## Makefile
##
NAME		= raytracer

FLAGS		= -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS		= -L/opt/homebrew/lib -lconfig++
SFML		= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC			= src/Main.cpp \
				src/ConfigParser.cpp \
				src/Display.cpp \
				src/Ray.cpp \
				src/Sphere.cpp \
				src/Plane.cpp \
				src/DirectionalLight.cpp \
				src/Camera.cpp \
				src/Scene.cpp \
				src/Material.cpp \
				src/Utils.cpp \
				src/Math3D.cpp \
				src/AmbientLight.cpp

OBJ			= $(SRC:.cpp=.o)

TEST_SRC	= criterion.cpp
TEST_NAME	= unitests

OS			:= $(shell uname -s)
ifeq ($(OS), Darwin)
	T1		= -I /opt/homebrew/opt/criterion/include
	T2		= -L /opt/homebrew/opt/criterion/lib
	T3		= -lcriterion -Wno-deprecated-declarations -Wno-unused-parameter
	TEST_FLAGS = $(T1) $(T2) $(T3)
else
	TEST_FLAGS = -lcriterion
endif

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(FLAGS) $(OBJ) -o $(NAME) $(SFML) $(LDFLAGS)

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

tests_run: re
	@echo "---------- Running tests on $(OS) ----------"
	g++ $(FLAGS) $(TEST_SRC) $(OBJ) -o $(TEST_NAME) $(TEST_FLAGS) $(SFML) $(LDFLAGS) --coverage
	./$(TEST_NAME) unitest
	@echo "---------- COVERAGE ----------"
	gcovr > coverage.txt
	gcovr -b >> coverage.txt
	@echo "---------- COVERAGE.TXT ----------"
	rm -rf src/*.o *.gcno *.gcda *.gcov $(TEST_NAME) $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME) coverage.txt

re: fclean all

build: re
	./$(NAME) unitest
