#ifndef		__FTGLTextureFont
#define		__FTGLTextureFont
#include	"FTFont.h"

#include "FTGL.h"

class FTTextureGlyph;

class	FTGLTextureFont : public FTFont
{
	public:
		// methods
		FTGLTextureFont();
		virtual ~FTGLTextureFont();
		
		virtual int TextureWidth() const { return textureWidth;}
		virtual int TextureHeight() const { return textureHeight;}
		
		virtual void render( const char* string);

		
	private:
		// attributes
		FTTextureGlyph* tempGlyph;
		
		long maxTextSize;
		int textureWidth;
		int textureHeight;
		
		unsigned long glTextureID[16];
		int numTextures;
		unsigned char* textMem;
		
		int glyphHeight;
		int glyphWidth;

		int horizGlyphs;
		int vertGlyphs;

		int padding;
		
		// methods
		bool MakeGlyphList();
		void CreateTexture( int id, int width, int height, unsigned char* data);
		void GetSize();
		int FillGlyphs( int glyphStart, int textID, int textureWidth, int textureHeight, unsigned char* textMem);
		
		
};
#endif
