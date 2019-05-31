#include <Texture.h>
#include <stb/stb_image.h>
#include <slam/slam.h>
#include <stdexcept>
#include <string>

Texture::Texture(const char* filename)
{
    gl::glGenTextures(1, &tid);
    gl::glBindTexture(gl::GL_TEXTURE_2D, tid);

    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_S, gl::GL_REPEAT);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_T, gl::GL_REPEAT);

    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_NEAREST);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);

    unsigned char* data = stbi_load(filename, &w, &h, &channels, 0);

    if(data == nullptr)
    {
        throw std::runtime_error(std::string("File not loaded successfully: ") + filename);
    }


    gl::GLenum format;
    
    if(channels == 3)
    {
        format = gl::GL_RGB;
    }
    else if(channels == 4)
    {

        format = gl::GL_RGBA;
    }
    else
    {
        throw std::runtime_error("Unrecognize channel number");
    }

    
    gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, format, w, h, 0, format, gl::GL_UNSIGNED_BYTE, data);
    gl::glGenerateMipmap(gl::GL_TEXTURE_2D);
    stbi_image_free(data);
}