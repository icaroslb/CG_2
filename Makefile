LIBS = -lSDL2 -lGL -lGLEW
FLAGS = -O3
VERSION = --std=c++11
MAIN = main
OBJ = obj/

OBJETOS = $(wildcard objetos/*.h)

all: $(OBJ) $(MAIN)

$(OBJ):
	if test ! -d $(OBJ); then mkdir $(OBJ); fi

$(OBJ)Engine_OpenGl.o: engines/Engine_OpenGl.cpp engines/Engine_OpenGl.h
	g++ -g -c $< -o $@ $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(OBJ)Engine_SDL.o: engines/Engine_SDL.cpp engines/Engine_SDL.h
	g++ -g -c $< -o $@ $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(OBJ)Shader.o: shaders/Shader.cpp shaders/Shader.h
	g++ -g -c $< -o $@ $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(MAIN): $(OBJ)Engine_OpenGl.o $(OBJ)Engine_SDL.o $(OBJ)Shader.o camera/Canvas.h $(OBJETOS) $(MAIN).cpp
	g++ $^ -o $@ $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

clean:
	rm -r $(MAIN) $(OBJ)*.o

