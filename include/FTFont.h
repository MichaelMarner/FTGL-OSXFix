#ifndef    __FTFont__
#define    __FTFont__

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FTGL.h"
#include "FTFace.h"

class FTGlyphContainer;
class FTGlyph;


/**
 * FTFont is the public interface for the FTGL library.
 *
 * Specific font classes are derived from this class. It uses the helper
 * classes FTFace and FTSize to access the Freetype library. This class
 * is abstract and deriving classes must implement the protected
 * <code>MakeGlyph</code> function to create glyphs of the
 * appropriate type.
 *
 * @see     FTFace
 * @see     FTSize
 * @see     FTGlyphContainer
 * @see     FTGlyph
 */
class FTGL_EXPORT FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontname  font file name.
         */
        FTFont( const char* fontname);
        
        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes);
        
        /**
         * Destructor
         */
        virtual ~FTFont();
        
        /**
         * Attach auxilliary file to font e.g font metrics.
         *
         * Note: not all font formats implement this function.
         *
         * @param filename  auxilliary font file name.
         * @return          <code>true</code> if file has been attached
         *                  successfully.
         */
        bool Attach( const char* filename);

        /**
         * Set the character map for the face.
         *
         * @param encoding      Freetype enumerate for char map code.
         * @return              <code>true</code> if charmap was valid and
         *                      set correctly
         */
        bool CharMap( FT_Encoding encoding );
        
        /**
         * Set the char size for the current face.
         *
         * @param size      the face size in points (1/72 inch)
         * @param res       the resolution of the target device.
         * @return          <code>true</code> if size was set correctly
         */
        bool FaceSize( const unsigned int size, const unsigned int res = 72);
        
        /**
         * Get the the current face.
         *
         * @return face size
         */
        unsigned int FaceSize() const;
        
        /**
         * Set the extrusion distance for the font. Only availbale for
         * Extruded fonts
         *
         * @param d  The extrusion distance.
         */
        virtual void Depth( float d){}

        /**
         * Get the global ascender height for the face.
         *
         * @return  Ascender height
         */
        float Ascender() const;
        
        /**
         * Gets the global descender height for the face.
         *
         * @return  Descender height
         */
        float Descender() const;

        /**
         * Get the bounding box for a string.
         *
         * @param string    a char string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox( const char* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz);

        /**
         * Get the bounding box for a string.
         *
         * @param string    a wchar_t string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox( const wchar_t* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz);

        /**
         * Get the advance width for a string.
         *
         * @param string    a wchar_t string
         * @return      advance width
         */
        float Advance( const wchar_t* string);

        /**
         * Get the advance width for a string.
         *
         * @param string    a char string
         * @return      advance width
         */
        float Advance( const char* string);

        /**
         * Render a string of characters
         * 
         * @param string    'C' style string to be output.   
         */
        virtual void render( const char* string );

        /**
         * Render a string of characters
         * 
         * @param string    wchar_t string to be output.     
         */
        virtual void render( const wchar_t* string );

        /**
         * Queries the Font for errors.
         *
         * @return  The current error code.
         */
        FT_Error Error() const { return err;}

    protected:
        /**
         * Construct a glyph of the correct type.
         *
         * Clients must overide the function and return their specialised
         * FTGlyph.
         *
         * @param g The glyph index NOT the char code.
         * @return  An FT****Glyph or <code>null</code> on failure.
         */
        inline virtual FTGlyph* MakeGlyph( unsigned int g) = 0;
        
        /**
         * Construct the internal glyph cache.
         *
         * This a list of glyphs processed for openGL rendering NOT
         * freetype glyphs.
         *
         * @return  <code>true</code> on success.
         */
        virtual bool MakeGlyphList();
        
        /**
         * Current face object
         */
        FTFace face;
        
        /**
         * Number of faces in this font
         */
        unsigned int numFaces;
        
        /**
         * Current size object
         */
        FTSize charSize;

        /**
         * An object that holds a list of glyphs
         */
        FTGlyphContainer* glyphList;
        
        /**
         * Current pen or cursor position;
         */
        FTPoint pen;
        
        /**
         * Current error code. Zero means no error.
         */
        FT_Error err;
        
    private:
        /**
         * Get the advance width for a character.
         * This function does an implicit conversion on it's arguments.
         *
         * @param chr       current character
         * @param nextChr   next character
         * @return          advance width
         */
        inline float doAdvance( const unsigned int chr, const unsigned int nextChr);

        /**
         * Render a character
         * This function does an implicit conversion on it's arguments.
         * 
         * @param chr       current character
         * @param nextChr   next character
         */
        inline void doRender( const unsigned int chr, const unsigned int nextChr);
        
        /**
         *
         */
        inline void CheckGlyph( const unsigned int chr);

};


#endif  //  __FTFont__

