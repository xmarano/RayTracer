##
## EPITECH PROJECT, 2025
## B-OOP-400-MAR-4-1-raytracer-selim.bouasker
## File description:
## Makefile
##

NAME        = raytracer

FLAGS       = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS     = -L/opt/homebrew/lib -lconfig++
SFML        = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC         = src/main.cpp \
              src/ConfigParser.cpp \
              src/Display.cpp \
              src/Ray.cpp \
              src/DirectionalLight.cpp \
              src/Camera.cpp \
              src/Scene.cpp \
              src/Material.cpp \
              src/Utils.cpp \
              src/Math3D.cpp \
              src/AmbientLight.cpp \
              src/PointLight.cpp

OBJ         = $(SRC:.cpp=.o)

PLUGIN_SPHERE_SRC    = plugins/Sphere/Sphere.cpp src/Math3D.cpp
PLUGIN_PLANE_SRC     = plugins/Plane/Plane.cpp src/Math3D.cpp
PLUGIN_CONE_SRC      = plugins/Cone/Cone.cpp src/Math3D.cpp
PLUGIN_CYLINDER_SRC  = plugins/Cylinder/Cylinder.cpp src/Math3D.cpp

PLUGIN_SPHERE_OBJ    = $(PLUGIN_SPHERE_SRC:.cpp=.o)
PLUGIN_PLANE_OBJ     = $(PLUGIN_PLANE_SRC:.cpp=.o)
PLUGIN_CONE_OBJ      = $(PLUGIN_CONE_SRC:.cpp=.o)
PLUGIN_CYLINDER_OBJ  = $(PLUGIN_CYLINDER_SRC:.cpp=.o)

PLUGIN_SPHERE_SO     = plugins/libsphere.so
PLUGIN_PLANE_SO      = plugins/libplane.so
PLUGIN_CONE_SO       = plugins/libcone.so
PLUGIN_CYLINDER_SO   = plugins/libcylinder.so

TEST_SRC    = criterion.cpp
TEST_NAME   = unitests

OS          := $(shell uname -s)
ifeq ($(OS), Darwin)
    T1      = -I /opt/homebrew/opt/criterion/include
    T2      = -L /opt/homebrew/opt/criterion/lib
    T3      = -lcriterion -Wno-deprecated-declarations -Wno-unused-parameter
    TEST_FLAGS = $(T1) $(T2) $(T3)
else
    TEST_FLAGS = -lcriterion
endif

all: $(NAME) $(PLUGIN_SPHERE_SO) $(PLUGIN_PLANE_SO) $(PLUGIN_CONE_SO) $(PLUGIN_CYLINDER_SO)

$(NAME): $(OBJ)
	g++ $(FLAGS) $(OBJ) -o $(NAME) $(SFML) $(LDFLAGS)

$(PLUGIN_SPHERE_SO): $(PLUGIN_SPHERE_OBJ)
	g++ -shared -o $(PLUGIN_SPHERE_SO) $(PLUGIN_SPHERE_OBJ) $(FLAGS)

$(PLUGIN_PLANE_SO): $(PLUGIN_PLANE_OBJ)
	g++ -shared -o $(PLUGIN_PLANE_SO) $(PLUGIN_PLANE_OBJ) $(FLAGS)

$(PLUGIN_CONE_SO): $(PLUGIN_CONE_OBJ)
	g++ -shared -o $(PLUGIN_CONE_SO) $(PLUGIN_CONE_OBJ) $(FLAGS)

$(PLUGIN_CYLINDER_SO): $(PLUGIN_CYLINDER_OBJ)
	g++ -shared -o $(PLUGIN_CYLINDER_SO) $(PLUGIN_CYLINDER_OBJ) $(FLAGS)

%.o: %.cpp
	g++ $(FLAGS) -fPIC -c $< -o $@

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
	rm -f $(OBJ) $(PLUGIN_SPHERE_OBJ) $(PLUGIN_PLANE_OBJ) $(PLUGIN_CONE_OBJ) $(PLUGIN_CYLINDER_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME) coverage.txt toto.ppm \
          $(PLUGIN_SPHERE_SO) $(PLUGIN_PLANE_SO) $(PLUGIN_CONE_SO) $(PLUGIN_CYLINDER_SO)

re: fclean all

build: re
	./$(NAME) unitest
