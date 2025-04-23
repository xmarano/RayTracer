##
## EPITECH PROJECT, 2024
## B-OOP-400-MAR-4-1-raytracer-selim.bouasker
## File description:
## Makefile
##

NAME = raytracer

FLAGS = -std=c++17 -Wall -Wextra -Iinclude
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC =	src/Main.cpp \
		src/Display.cpp \
		src/Ray.cpp \
		src/Sphere.cpp \
		src/Plane.cpp \
		src/DirectionalLight.cpp \
		src/Camera.cpp \
		src/Scene.cpp \
		src/SceneLoader.cpp \
		src/Material.cpp \
		src/Utils.cpp \
		src/Math3D.cpp	\
		src/AmbientLight.cpp

OBJ = $(SRC:.cpp=.o)

TEST_SRC = criterion.cpp
TEST_NAME = unitests

OS := $(shell uname -s)
ifeq ($(OS), Darwin)
	T1 = -I /opt/homebrew/opt/criterion/include
	T2 = -L /opt/homebrew/opt/criterion/lib
	T3 = -lcriterion -Wno-deprecated-declarations -Wno-unused-parameter
	TEST_FLAGS = $(T1) $(T2) $(T3)
else
	TEST_FLAGS = -lcriterion
endif

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME) $(FLAGS) $(SFML)

tests_run:  re
	@echo "---------- Running tests on $(UNAME_S) ----------"
	g++ $(TEST_SRC) $(OBJ) -o $(TEST_NAME) $(FLAGS) $(TEST_FLAGS) --coverage
	./$(TEST_NAME) unitest
	@echo "---------- COVERAGE ----------"
	gcovr > coverage.txt
	gcovr -b >> coverage.txt
	@echo "---------- COVERAGE.TXT ----------"

clean:
	rm -f $(OBJ) src/Main.o
	rm -rf src/*.o *.gcno *.gcda

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all clean

build: re
	./$(NAME) unitest
