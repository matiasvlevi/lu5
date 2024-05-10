#include "lu5_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <lauxlib.h>

lu5_image *lu5_load_image(lu5_State *l5, const char* image_path) 
{

	int width, height, comp;

	unsigned char* image = stbi_load(image_path, &width, &height, &comp, STBI_rgb_alpha); //rgba channels 
	if (image == NULL) {
		luaL_error(l5->L, "Could not load image");
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		width, 
		height, 
		0, 
		GL_RGBA, 
		GL_UNSIGNED_BYTE, 
		image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	lu5_image *img = (lu5_image*)malloc(sizeof(lu5_image));
	img->texture = texture;
	img->width = width;
	img->height = height;

	// Add the texture's GLuint ptr to the list
	lu5_list_push(&(l5->images), img, sizeof(lu5_image));

	return img;
}

void lu5_render_image(lua_State* L, GLuint texture, double x, double y, double w, double h) 
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0); glVertex2f(x, y);
        glTexCoord2f(1, 0); glVertex2f(x + w, y);
        glTexCoord2f(1, 1); glVertex2f(x + w, y + h);
        glTexCoord2f(0, 1); glVertex2f(x, y + h);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}