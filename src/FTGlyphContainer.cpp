#include	"FTGlyphContainer.h"
#include	"FTGlyph.h"


FTGlyphContainer::FTGlyphContainer( FT_Face* f, int g, bool p)
:	preCache( p),
	numGlyphs(g),
	tempGlyph(0),
	face(f)
{
	glyphs.reserve( g);
}


// OPSignature:  FTGlyphContainer:~FTGlyphContainer() 
FTGlyphContainer::~FTGlyphContainer()
{
	vector<FTGlyph*>::iterator iter;
	for( iter = glyphs.begin(); iter != glyphs.end(); ++iter)
	{
		delete *iter;
	}
	
	glyphs.clear();
}


bool FTGlyphContainer::Add( FTGlyph* tempGlyph)
{
	glyphs.push_back( tempGlyph);
}


FT_Vector& FTGlyphContainer::render( int index, int next, FT_Vector pen)
{
	kernAdvance.x = 0; kernAdvance.y = 0;
	
	int left = FT_Get_Char_Index( *face, index);
	int right = FT_Get_Char_Index( *face, next);
	
	if( left > glyphs.size())
		return kernAdvance;
	
	if( 0 < right <=  glyphs.size())
	{
		// ft_kerning_unfitted
		err = FT_Get_Kerning( *face, left, right, ft_kerning_default, &kernAdvance);
	}
	
	advance = glyphs[left]->Render( pen);
	
	kernAdvance.x = advance + kernAdvance.x;
//	kernAdvance.y = advance.y + kernAdvance.y;
	return kernAdvance;
}
