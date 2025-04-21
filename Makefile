##
## EPITECH PROJECT, 2025
## Raytracer
## File description:
## Makefile
##

NAME = raytracer

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	T1 = $(shell pkg-config --cflags criterion)
	T2 = $(shell pkg-config --libs criterion)
	TEST_FLAGS = $(T1) $(T2) -Wno-deprecated-declarations -Wno-unused-parameter
else
	TEST_FLAGS = -lcriterion
endif

SRC = src/Main.cpp src/Ray.cpp src/Sphere.cpp src/Plane.cpp src/DirectionalLight.cpp src/Camera.cpp src/Scene.cpp src/SceneLoader.cpp src/Material.cpp src/Utils.cpp
OBJ = $(SRC:.cpp=.o)

TEST_SRC = unitest/criterion.cpp
TEST_NAME = unit_tests
COV_DIR = unitest
COV_FILE = $(COV_DIR)/coverage.txt

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

##### UNIT TESTS #####
tests_run: $(COV_DIR)/$(TEST_NAME)
	@echo "---------- Running tests on $(UNAME_S) ----------"
	./$(COV_DIR)/$(TEST_NAME)
	@echo "---------- COVERAGE ----------"
	cd $(COV_DIR) && gcovr --root .. > coverage.txt && gcovr -b --root .. --append >> coverage.txt
	@echo "---------- Coverage written to $(COV_FILE) ----------"

$(COV_DIR)/$(TEST_NAME): $(TEST_SRC) src/Utils.cpp
	@mkdir -p $(COV_DIR)
	$(CXX) $(TEST_SRC) src/Utils.cpp -o $@ $(CXXFLAGS) -fprofile-arcs -ftest-coverage $(TEST_FLAGS) -o $@

test: tests_run
##### UNIT TESTS #####

clean:
	rm -f $(OBJ) src/Main.o
	rm -rf $(COV_DIR)/*.o $(COV_DIR)/*.gcno $(COV_DIR)/*.gcda

fclean: clean
	rm -f $(NAME) $(COV_DIR)/$(TEST_NAME) $(COV_FILE)

re: fclean all
