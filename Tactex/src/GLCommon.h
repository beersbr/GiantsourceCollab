#ifndef __GL_COMMON__
#define __GL_COMMON__

#include <OpenGL/gl3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif // __GL_COMMON__