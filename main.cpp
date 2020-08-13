#include <iostream>
#include "camera/Camera.h"
#include "engines/Engine_OpenGl.h"
#include "engines/Engine_SDL.h"
#include "shaders/Shader.h"

#include "objetos/Mundo.h"
#include "camera/Canvas.h"

#include "objetos/Esfera.h"
#include "objetos/Luz_pontual.h"

int main (int argc, char *argv[]) {
    Camera<float> camera( Vec_3f(  0.0f,  0.0f,  0.0f ), // Posição
	                      Vec_3f(  0.0f,  0.0f,  1.0f ), // Look at
	                      Vec_3f(  0.0f,  1.0f,  0.0f ), // View up
	                      -5.0f, 5.0f,                   // Esquerda e direita
	                      -5.0f, 5.0f,                   // Baixo e cima
	                      -1.0f, 1.0f, ORTHO );          // Near, far e o tipo de visão*
    
    Engine_SDL tela( "Projeto", 500, 500 );
	Engine_OpenGl opengl;
	Shader shader( "shaders/shader.vs", "shaders/shader.fs" );
	
	SDL_Event evento;
	bool loop = true;

	Mundo<float> mundo;
	Canvas<float> canvas( 1000, 1000, opengl );

	printf( "Versão do OpenGl: %s\n", tela.obter_versao_opengl() );

	Vec_3f cor;
	Vec_3f vetor(0.0f, 0.0f, 1.0f);
	float t = 0;

	Esfera<float> *teste_o_1 = new Esfera<float>( Vec_3f( 0.0f, 0.0f, 5.0f )
	                                            , 4.0f
	                                            , Vec_3f( 0.0215f, 0.1745f, 0.0215f )
												, Vec_3f( 0.07568f, 0.61424f, 0.07568f )
												, Vec_3f( 0.633f, 0.727811f, 0.633f )
												, 0.6 );

	Esfera<float> *teste_o_2 = new Esfera<float>( Vec_3f( 0.0f, 5.0f, 2.0f )
	                                            , 2.0f
	                                            , Vec_3f( 0.1745f, 0.01175f, 0.01175f )
												, Vec_3f( 0.61424f, 0.04136f, 0.04136f )
												, Vec_3f( 0.727811f, 0.626959f, 0.626959f )
												, 0.6
												);

	Luz_pontual<float> *teste_l = new Luz_pontual<float>( Vec_3f( 0.0f, 20.0f, 0.0f )
	                                                    , Vec_3f( 1.0f, 1.0f, 1.0f )
														);
	
	mundo.objetos.push_back( (Objeto<float>*)teste_o_1 );
	mundo.objetos.push_back( (Objeto<float>*)teste_o_2 );
	mundo.luzes.push_back( (Luz<float>*)teste_l );

	while ( loop ) {

		while ( SDL_PollEvent( &evento ) ) {
			
			if ( evento.type == SDL_QUIT ) {
				loop = false;
			}
		}

		glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		teste_l->posicao._x = float( cos( t ) ) * 10.0f;
		//teste_l->posicao._y = float( sin( t ) ) * 10.0f;
		teste_l->posicao._z = float( sin( t ) ) * 10.0f;

		for ( int i = canvas.altura - 1; i >= 0 ; i-- ) {
			for ( int j = 0; j < canvas.largura; j++ ) {
				vetor._x = -( 50.0f ) + ( 50.0f / canvas.largura ) + ( float(j) * 100.0f / canvas.largura );
				vetor._y =  ( 50.0f ) - ( 50.0f / canvas.altura ) - ( float(i) * 100.0f / canvas.altura );
				vetor._z = 100.0f;
				vetor = unitario( vetor );
				
				canvas(i, j) = mundo.calcular_cor( Vec_3f( 0.0f, 0.0f, -20.0f ), vetor, 0.0001f );
			}	
		}

		canvas.atualizar();
		canvas.printar( shader );

		tela.swap_tela();

		t += 0.1f;
	}

    return 0;
}
