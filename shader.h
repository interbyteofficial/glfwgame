#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

class Shader
{
private:
    GLuint id;

public:
    Shader();
    ~Shader();
    Shader(char* vertex,char* fragment);
    bool loadShader(char* vertex,char *fragment);
    void use();
    GLuint getId();
};

#endif // SHADER_H_INCLUDED
