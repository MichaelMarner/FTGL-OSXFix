#include	"FTFace.h"
#include	"FTLibrary.h"
#include	"FTGL.h"


FTFace::FTFace()
:	ftFace(0),
	numCharMaps(0),
	numGlyphs(0)
{}


FTFace::~FTFace()
{
	if( ftFace)
	{
		Close();
		delete ftFace; // is this a prob?
		ftFace = 0;
	}
}


bool FTFace::Open( const char* filename)
{
	ftFace = new FT_Face;
	err = FT_New_Face( *FTLibrary::Instance().GetLibrary(), filename, 0, ftFace);

	if( err)
    {
		delete ftFace;
		ftFace = 0;
	    return false;
    }
    else
    {
		return true;
	}
}


void FTFace::Close()
{
	FT_Done_Face( *ftFace);
}


FTSize& FTFace::Size( const int size, const int res )
{
	charSize.CharSize( ftFace, size, res, res);
	return charSize;
}


bool FTFace::CharMap( CHARMAP encoding )
{
//Insert your own code here.

//End of user code.   
	return false;     
}


FT_Glyph FTFace::Glyph( int index )
{
//Insert your own code here.

//End of user code.         
}


FT_Vector FTFace::KernAdvance( int index1, int index2 )
{
//Insert your own code here.

//End of user code.         
}
