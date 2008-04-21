/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, you can redistribute and/or modify this software under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#include "config.h"

#include "FTOutlineGlyph.h"
#include "FTVectoriser.h"


FTOutlineGlyph::FTOutlineGlyph( FT_GlyphSlot glyph, bool useDisplayList)
:   FTGlyph( glyph),
    glList(0)
{
    if( ft_glyph_format_outline != glyph->format)
    {
        err = 0x14; // Invalid_Outline
        return;
    }

    FTVectoriser vectoriser( glyph);

    size_t numContours = vectoriser.ContourCount();
    if ( ( numContours < 1) || ( vectoriser.PointCount() < 3))
    {
        return;
    }

    if(useDisplayList)
    {
        glList = glGenLists(1);
        glNewList( glList, GL_COMPILE);
    }
    
    for( unsigned int c = 0; c < numContours; ++c)
    {
        const FTContour* contour = vectoriser.Contour(c);
        
        glBegin( GL_LINE_LOOP);
            for( unsigned int pointIndex = 0; pointIndex < contour->PointCount(); ++pointIndex)
            {
                FTPoint point = contour->Point(pointIndex);
                glVertex2f( point.X() / 64.0f, point.Y() / 64.0f);
            }
        glEnd();
    }

    if(useDisplayList)
    {
        glEndList();
    }
}


FTOutlineGlyph::~FTOutlineGlyph()
{
    glDeleteLists( glList, 1);
}


const FTPoint& FTOutlineGlyph::Render(const FTPoint& pen)
{
    if(glList)
    {
        glTranslatef(pen.X(), pen.Y(), 0.0f);
        glCallList(glList);
        glTranslatef(-pen.X(), -pen.Y(), 0.0f);
    }
    
    return advance;
}

