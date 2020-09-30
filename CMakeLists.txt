cmake_minimum_required( VERSION 2.8 )
project( CG_2 )

find_package( SDL2 REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )

include_directories( ${SDL2_INCLUDE_DIRS} ${OPENGL_gl_LIBRARY} ${GLEW_INCLUDE_DIRS} )

file( GLOB SOURCES main.cpp
                   camera/Camera.h camera/Camera.inl
                   camera/Canvas.h
                   engines/Engine_OpenGl.h engines/Engine_OpenGl.cpp
                   engines/Engine_SDL.h    engines/Engine_SDL.cpp
                   shaders/Shader.h shaders/Shader.cpp
                   objetos/Cone.h  objetos/Esfera.h   objetos/Face.h
                   objetos/Luz.h   objetos/Luz_cone.h objetos/Luz_pontual.h
                   objetos/Mundo.h objetos/Objeto.h )

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} PRIVATE  ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )
