#include "lu5_font.h"
#include "static/lu5_default_font.h"
#include "./geometry/lu5_geometry.h"
#include "lu5_logger.h"

#include "lu5_state.h"
#include "lu5_style.h"
#include "lu5_list.h"

#include <lauxlib.h>
#include <math.h>

void lu5_init_freetype(lu5_State *l5) 
{
	if (FT_Init_FreeType(&(l5->ft)))
	{
		LU5_ERROR("Failed to initialize FreeType");
	}
}

int lu5_load_font(lu5_State *l5, lu5_font **fontId, const char *fontPath) 
{

	lu5_font *font = (lu5_font*)malloc(sizeof(lu5_font));
	if (font == NULL) {
		return FT_Err_Out_Of_Memory;
	}

	int err;
	if (fontPath == NULL) {
		err = FT_New_Memory_Face(l5->ft, lu5_default_font, sizeof(lu5_default_font), 0, &(font->face));
		if (err != LU5_LOADFONT_NONE) return err;
	} else {
		err = FT_New_Face(l5->ft, fontPath, 0, &(font->face));
		if (err != LU5_LOADFONT_NONE) return err;
	}

	// Set font to the current style size
	err = FT_Set_Pixel_Sizes(font->face, 0, MAX_FONT_SIZE_PX);
	if (err != FT_Err_Ok) {
		lu5_close_font(font);
		return err;
	}
	
	// Iterate over characters and create a texture
	for (unsigned char character = 32; character < 128; character++) 
	{
		// Load character glyph into face->glyph
		if (FT_Load_Char(font->face, character, FT_LOAD_RENDER) != FT_Err_Ok) {
			LU5_WARN("Could not load character '%c'\n", character);
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			font->face->glyph->bitmap.width,
			font->face->glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			font->face->glyph->bitmap.buffer
		);

		glBindTexture(GL_TEXTURE_2D, 0);

		// Add font texture
		font->textures[character] = texture;
	}

	// If fontId pointer is invalid, 
	if (fontId != NULL) 
	{
		// set the value to the next fontId
		*fontId = font;
	}

	// Set default font size
	if (FT_Set_Pixel_Sizes(font->face, 0, lu5_style(l5)->fontSize) != FT_Err_Ok) {
		lu5_close_font(font);
		luaL_error(l5->L, "Something went wrong when resizing the font");
		return 0;
	}

	return FT_Err_Ok;
}

void lu5_measure_text(const char *text, int *width, int *height, int *max_bearing_y, lu5_font *font) 
{
    int w = 0, h = 0;
    int max_bearing_y_local = 0;
    for (const char *p = text; *p; p++) {
		if(FT_Load_Char(font->face, *p, FT_LOAD_DEFAULT)) continue;
        max_bearing_y_local = fmax(max_bearing_y_local, font->face->glyph->bitmap_top);

        w += font->face->glyph->advance.x >> 6;
        h = fmax(h, font->face->glyph->bitmap.rows - font->face->glyph->bitmap_top + max_bearing_y_local);

    }
    *width = w;
    *height = h;
    *max_bearing_y = max_bearing_y_local;
}

void lu5_render_text(const char *text, float x, float y, float fontSize, lu5_font *font) 
{
	int text_width = 0, text_height = 0, max_bearing_y = 0;
	lu5_measure_text(text, &text_width, &text_height, &max_bearing_y, font);
			
	switch(lu5_style(&lu5)->textAlign)
	{
		case LU5_TEXTALIGN_LEFT: 
			y -= text_height;
			break;
		case LU5_TEXTALIGN_CENTER:
			x -= text_width / 2;
			y -= text_height;
			break;
		case LU5_TEXTALIGN_RIGHT:
			x -= text_width;
			y -= text_height;
			break;
	}

	glEnable(GL_TEXTURE_2D);
	const char *p;
	float x_advance = 0.0f, y_advance = 0.0f;
	for (p = text; *p; p++) 
	{		
		// Load glyph from freetype, or skip if failed
		if(FT_Load_Char(font->face, *p, FT_LOAD_DEFAULT)) continue;
		
		// Adjust height
		float y_adjusted = (font->face->size->metrics.ascender >> 6) - font->face->glyph->bitmap_top;

		// Calculate the new bottom-left origin adjusted Y-coordinate
		float y_bottom_left = y - max_bearing_y / 2 + y_advance + y_adjusted;

		glBindTexture(GL_TEXTURE_2D, font->textures[(int)(*p)]);
		glBegin(GL_QUADS);
		{

			lu5_glTexCoord2(0,  0); lu5_glVertex2(x + x_advance,                                   y_bottom_left);
			lu5_glTexCoord2(1,  0); lu5_glVertex2(x + x_advance + font->face->glyph->bitmap.width, y_bottom_left);
			lu5_glTexCoord2(1,  1); lu5_glVertex2(x + x_advance + font->face->glyph->bitmap.width, y_bottom_left + font->face->glyph->bitmap.rows);
			lu5_glTexCoord2(0,  1); lu5_glVertex2(x + x_advance,                                   y_bottom_left + font->face->glyph->bitmap.rows);
		}
		glEnd();
		x_advance += (font->face->glyph->advance.x >> 6);
		y_advance += (font->face->glyph->advance.y >> 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void lu5_load_default_font(lu5_State *l5) 
{
	// Load default font statically
	int err = lu5_load_font(l5, &(l5->font_default), NULL);
	if (err != FT_Err_Ok) {
		luaL_error(l5->L, "Error loading default font, FT_Err: %i", err);
		return;
	}

	// Set the current as the default font
	lu5_style(l5)->font_current = l5->font_default;
}

void lu5_close_font(lu5_font *font) 
{
	if (font != NULL) {
		for (int i = 0; i < 128; i++) {
			glDeleteTextures(1, &font->textures[i]);
		}
		FT_Done_Face(font->face);
	}
}

void lu5_close_fonts(lu5_State *l5) 
{
	// Clear default font
	lu5_close_font(l5->font_default);
	l5->font_default = NULL;

	// Clear dangling reference
	lu5_style(l5)->font_current = NULL;

	// Clear all fonts
	lu5_list_iter_close(l5->fonts, (void(*)(void*))lu5_close_font);
	l5->fonts = NULL;
}
