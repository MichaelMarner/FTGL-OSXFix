#include	"FTGlyphContainer.h"
#include	"FTGlyph.h"
#include	"FTFace.h"


FTGlyphContainer::FTGlyphContainer( FTFace* f, int g, bool p)
:	preCache( p),
	numGlyphs(g),
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
	// At the moment we are using a vector. Vectors don't return bool.
	glyphs.push_back( tempGlyph);
	return true;
}


FT_Vector& FTGlyphContainer::render( int index, int next, FT_Vector pen)
{
	kernAdvance.x = 0; kernAdvance.y = 0;
	
	int left = face->CharIndex( index);
	int right = face->CharIndex( next);
	
	kernAdvance = face->KernAdvance( left, right);	
	if( !face->Error())
		advance = glyphs[left]->Render( pen);
	
	kernAdvance.x = advance + kernAdvance.x;
//	kernAdvance.y = advance.y + kernAdvance.y;
	return kernAdvance;
}
