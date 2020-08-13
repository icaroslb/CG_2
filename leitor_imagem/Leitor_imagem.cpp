#define STB_IMAGE_IMPLEMENTATION
#include "Leitor_imagem.h"

Imagem ler_imagem ( std::string nomeImagem ) {
	Imagem img;
	unsigned char *data;
	
	stbi_set_flip_vertically_on_load(true);
	
	glGenTextures( 1, &img.id );
	glBindTexture( GL_TEXTURE_2D, img.id );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	data = stbi_load( nomeImagem.data(), &img.largura, &img.altura, &img.nCanais, 0 );
	
	if ( data ) {
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, img.largura, img.altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
    	glGenerateMipmap( GL_TEXTURE_2D );
	} else {
		std::cout << "Falha ao ler a imagem " << nomeImagem << "!" << std::endl;
	}
	
	stbi_image_free( data );
	
	return img;
}
