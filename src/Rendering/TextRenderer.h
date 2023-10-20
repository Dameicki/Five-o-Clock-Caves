#pragma once
#include "ft2build.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <map>
#include <string>
#include <Learnopengl/shader.h>
#include <glad/glad.h>
#include <Core/Time.h>
#include FT_FREETYPE_H
/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
    unsigned int size;
    // holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    // shader used for text rendering
    Shader TextShader = Shader("res/shaders/text.vs", "res/shaders/text.fs");
    // constructor
    TextRenderer();
    TextRenderer(unsigned int width, unsigned int height);
    // pre-compiles a list of characters from the given font
    void Load(std::string font, unsigned int fontSize);
    // renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // render state
    unsigned int VAO, VBO;
    glm::mat4 proj;
};