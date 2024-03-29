#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "camera/Camera.h"
#include "engines/Engine_OpenGl.h"
#include "engines/Engine_SDL.h"
#include "shaders/Shader.h"

#include "objetos/Mundo.h"
#include "camera/Canvas.h"

#include "objetos/Esfera.h"
#include "objetos/Face.h"

#include "objetos/Luz_pontual.h"
#include "objetos/Luz_cone.h"

int main (int argc, char *argv[]) {
    Camera<float> camera( Vec_3f(  0.0f,  0.0f,  0.0f ), // Posição
	                      Vec_3f(  0.0f,  0.0f,  1.0f ), // Look at
	                      Vec_3f(  0.0f,  1.0f,  0.0f ), // View up
	                      -5.0f, 5.0f,                   // Esquerda e direita
	                      -5.0f, 5.0f,                   // Baixo e cima
	                      -1.0f, 1.0f, ORTHO );          // Near, far e o tipo de visão*
    
    Engine_SDL tela( "CG 2", 500, 500 );
	Engine_OpenGl opengl;
	Shader shader( "shaders/shader.vs", "shaders/shader.fs" );
	
	SDL_Event evento;
	bool loop = true;

	Mundo<float> mundo;
	Canvas<float> canvas( 500, 500, opengl );

	printf( "Versão do OpenGl: %s\n", tela.obter_versao_opengl() );

	Vec_3f cor;
	Vec_3f vetor( 0.0f, 0.0f, 1.0f );
	Vec_4f origem( 0.0f, 0.0f, -20.0f, 1.0f );
	float t = 0;

	Esfera<float> *teste_o_1 = new Esfera<float>( Vec_4f( 0.0f, 0.0f, 0.0f, 1.0f )
	                                            , 4.0f
	                                            , Vec_3f( 0.19225f, 0.19225f, 0.19225f )//Vec_3f( 0.0215f, 0.1745f, 0.0215f )
												, Vec_3f( 0.50754f, 0.50754f, 0.50754f )//Vec_3f( 0.07568f, 0.61424f, 0.07568f )
												, Vec_3f( 0.508273f, 0.508273f, 0.508273f )//Vec_3f( 0.633f, 0.727811f, 0.633f )
												, 0.4f
												, 0.0f
												);

	Esfera<float> *teste_o_2 = new Esfera<float>( Vec_4f( 0.0f, 0.0f, 0.0f, 1.0f )
	                                            , 2.0f
	                                            , Vec_3f( 0.1745f, 0.01175f, 0.01175f )
												, Vec_3f( 0.61424f, 0.04136f, 0.04136f )
												, Vec_3f( 0.727811f, 0.626959f, 0.626959f )
												, 0.6f
												, 0.8f
												);
	
	Face<float> *teste_o_3 = new Face<float>( Vec_4f( -3.0f, -3.0f, 0.0f, 1.0f )
	                                        , Vec_4f(  3.0f, -3.0f, 0.0f, 1.0f )
											, Vec_4f(  0.0f,  3.0f, 0.0f, 1.0f )
	                                        , Vec_3f( 0.19225f, 0.19225f, 0.19225f )
											, Vec_3f( 0.50754f, 0.50754f, 0.50754f )
											, Vec_3f( 0.508273f, 0.508273f, 0.508273f )
											, 0.4f
											, 1.0f
											);

	Luz_pontual<float> *teste_l_1 = new Luz_pontual<float>( Vec_4f( -20.0f, 0.0f, -10.0f, 1.0f )//Vec_4f( 0.0f, 20.0f, -10.0f, 1.0f )
	                                                      , Vec_3f( 1.0f, 1.0f, 1.0f )
														  );

	Luz_cone<float> *teste_l_2 = new Luz_cone<float>( Vec_4f( 0.0f, -50.0f, 0.0f, 1.0f )
	                                                , Vec_3f( 1.0f, 1.0f, 1.0f )
													, Vec_3f( -1.0f, -1.0f, 0.0f )
													, float(M_PI_4 * 0.25)
													);
	
	mundo.objetos.push_back( (Objeto<float>*)teste_o_1 );
	mundo.objetos.push_back( (Objeto<float>*)teste_o_2 );
	mundo.objetos.push_back( (Objeto<float>*)teste_o_3 );
	mundo.luzes.push_back( (Luz<float>*)teste_l_1 );
	mundo.luzes.push_back( (Luz<float>*)teste_l_2 );

	mundo.objetos[0]->matriz_tranformacao = transladar( 0.0f, 0.0f, 5.0f )
	                                      * rotacionar( Ori_transf::xy, float(M_PI_4) )
										  * escalar( 1.0f, 2.0f, 1.0f );
	mundo.objetos[0]->matriz_tranformacao_inversa = inversa_TRS( 1.0f, 2.0f, 1.0f,
	                                                             Ori_transf::xy, float(M_PI_4),
															     0.0f, 0.0f, 5.0f );
	
	mundo.objetos[1]->matriz_tranformacao = transladar( 0.0f, 5.0f, 0.0f )
	                                       * escalar( 2.0f, 1.0f, 1.0f );
	mundo.objetos[1]->matriz_tranformacao_inversa = inversa_TRS( 2.0f, 1.0f, 1.0f,
	                                                             Ori_transf::xy, 0.0f,
																 0.0f, 5.0f, 0.0f );

	//teste_o_1->posicao = teste_o_1->matriz_tranformacao * teste_o_1->posicao;
	//teste_o_2->posicao = teste_o_2->matriz_tranformacao * teste_o_2->posicao;
	while ( loop ) {

		while ( SDL_PollEvent( &evento ) ) {
			
			if ( evento.type == SDL_QUIT ) {
				loop = false;
			}
		}

		glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//teste_l_2->posicao._x = float( cos( t ) ) * 20.0f;
		//teste_l->posicao._y = float( sin( t ) ) * 20.0f;
		//teste_l_2->posicao._z = float( sin( t ) ) * 20.0f;

		//teste_o_2->posicao._z = float( sin( t ) ) * 2.0f;

		//teste_l_2->direcao = unitario( teste_o_1->posicao - teste_l_2->posicao );

		mundo.objetos[1]->matriz_tranformacao = transladar( 0.0f, 5.0f, float( sin( t ) ) * 2.0f )
	                                          * escalar( 2.0f, 1.0f, 1.0f );
		mundo.objetos[1]->matriz_tranformacao_inversa = inversa_TRS( 2.0f, 1.0f, 1.0f,
	                                                             Ori_transf::xy, 0.0f,
																 0.0f, 5.0f, float( sin( t ) ) * 2.0f );

		for ( int i = canvas.altura - 1; i >= 0 ; i-- ) {
			for ( int j = 0; j < canvas.largura; j++ ) {
				#if 1
				vetor._x = -( 50.0f ) + ( 50.0f / canvas.largura ) + ( float(j) * 100.0f / canvas.largura );
				vetor._y =  ( 50.0f ) - ( 50.0f / canvas.altura ) - ( float(i) * 100.0f / canvas.altura );
				vetor._z = 100.0f;
				vetor = unitario( vetor );

				//canvas(i, j) = mundo.calcular_cor( origem, vetor, 0.0001f );
				canvas(i, j) = mundo.calcular_cor_recusivo( origem, vetor, 0.0001f, 5 );
				#else
				float x_min = -( 50.0f ) + ( float(j) * 100.0f / canvas.largura );
				float x_max = -( 50.0f ) + ( float(j + 1) * 100.0f / canvas.largura );
				float y_min =  ( 50.0f ) - ( float(i) * 100.0f / canvas.altura );
				float y_max =  ( 50.0f ) - ( float(i + 1) * 100.0f / canvas.altura );
				float z = 100.0f; 
				
				canvas(i, j) = mundo.calcular_cor_recusivo_sample( origem, x_min, x_max, y_min, y_max, z, 0.0001f, 1, 5 );
				#endif
			}
		}

		canvas.atualizar();
		canvas.printar( shader );

		tela.swap_tela();

		t += 0.1f;
	}

    return 0;
}
