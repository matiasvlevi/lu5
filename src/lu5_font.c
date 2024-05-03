#include "lu5_font.h"

#include "lu5_logger.h"

FT_Library ft;
FT_Face face;

GLuint font_textures[128]; // ASCII 0x20-0x7E

void lu5_init_freetype() {
    if (FT_Init_FreeType(&ft))
    {
        LU5_ERROR("Failed to initialize FreeType");
    }
}

int lu5_load_font(const char *fontPath) {
    int error = FT_New_Face( 
        ft,
        fontPath,
        0,
        &face);

    if (error == FT_Err_Unknown_File_Format)
    {
        LU5_ERROR("FreeType: Unknown file format");
        return 1;
    }
    else if (error)
    {
        LU5_ERROR("FreeType: Unhandled error");
        return 1;
    }

    FT_Set_Pixel_Sizes(face, 0, 48); 

    for (unsigned char c = 32; c < 128; c++) {
        // Load character glyph into face->glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            LU5_WARN("Could not load character '%c'\n", c);
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        font_textures[c] = texture;
    }

    return 0;

}

void lu5_render_text(const char *text, float x, float y, float fontSize) {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    // Use font ascender for uniform baseline alignment
    int ascender = face->size->metrics.ascender >> 6;
    
    // Iterate over string characters
    const char *p;
    for (p = text; *p; p++) {

        // Skip non-text
        if (*p < 32 || *p > 126)
           continue;
        
        // Get texture
        GLuint texture = font_textures[(int)(*p)];
        
        // Load glyph from freetype, or skip if failed
        if(FT_Load_Char(face, *p, FT_LOAD_DEFAULT)) continue;
        
        // Adjust height
        float y_adjusted = y + ascender - face->glyph->bitmap_top;
        
        // Calculate the pen advances
        float x_advance = (face->glyph->metrics.horiBearingX >> 6) + (face->glyph->metrics.width >> 6);
        float y_advance = (face->glyph->advance.y >> 6);

        // Add space if space char found
        if (*p == 32) x_advance += fontSize/2.5;

        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0, 0); glVertex2f(                        0, y_adjusted                           );
            glTexCoord2f(1, 0); glVertex2f(face->glyph->bitmap.width, y_adjusted                           );
            glTexCoord2f(1, 1); glVertex2f(face->glyph->bitmap.width, y_adjusted + face->glyph->bitmap.rows);
            glTexCoord2f(0, 1); glVertex2f(                        0, y_adjusted + face->glyph->bitmap.rows);
        }
        glEnd();

       // Move to next glyph position
       glTranslatef(x_advance, -y_advance, 0);
    }

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void lu5_font_close() 
{
    for (int i = 32; i < 128; i++) {
        glDeleteTextures(1, &font_textures[i]);
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
