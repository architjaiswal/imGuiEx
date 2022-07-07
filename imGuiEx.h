// imGuiEx.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "UseImGui.h"
#include "stb_image.h"


// Simple helper function to load image into a OpenGL texture with common settings

bool LoadTexutreFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

