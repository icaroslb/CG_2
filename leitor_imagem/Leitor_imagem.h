#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "stb_image.h"

struct Imagem {
	unsigned int id;
	int largura, altura, nCanais;
};

Imagem ler_imagem ( std::string nomeImagem );

