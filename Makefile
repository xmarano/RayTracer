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
              src/PointLight.cpp    \


OBJ         = $(SRC:.cpp=.o)

PLUGIN_SO   = plugins/libsphere.so \
              plugins/libplane.so \
              plugins/libcylinder.so \
              plugins/libcone.so

PLUGIN_DEP  = src/Math3D.cpp src/Material.cpp
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

all: $(NAME) $(PLUGIN_SO)

$(NAME): $(OBJ)
	g++ $(FLAGS) $(OBJ) -o $(NAME) $(SFML) $(LDFLAGS) -ldl

plugins/libsphere.so: plugins/Sphere/Sphere.cpp $(PLUGIN_DEP)
	g++ $(FLAGS) -shared -fPIC -o $@ $^

plugins/libplane.so: plugins/Plane/Plane.cpp $(PLUGIN_DEP)
	g++ $(FLAGS) -shared -fPIC -o $@ $^

plugins/libcylinder.so: plugins/Cylinder/Cylinder.cpp $(PLUGIN_DEP)
	g++ $(FLAGS) -shared -fPIC -o $@ $^

plugins/libcone.so: plugins/Cone/Cone.cpp $(PLUGIN_DEP)
	g++ $(FLAGS) -shared -fPIC -o $@ $^

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
	rm -f $(PLUGIN_SO)

fclean: clean
	rm -f $(NAME) $(TEST_NAME) coverage.txt toto.ppm

re: fclean all

build: re
	./$(NAME) unitest
