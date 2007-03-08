#include "Object2D.h"


namespace XOR {

Object2D::Object2D()
{
}


/*
 * Save state then push attributes needed for 2D rendering
 */
void Object2D::push2DState()
{
	Dimension2D * windowSize =
		Controller::GetInstance(NULL)->getViewer()->getWindowSize();

	// Push back and cache the current state of pixel alignment.
	glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
	glPixelStorei( GL_UNPACK_SWAP_BYTES, GL_FALSE );
	glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
	glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
	glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// Push back and cache the current state of depth testing and lighting
	// and then disable them.
	glPushAttrib( GL_TEXTURE_BIT | GL_DEPTH_TEST | GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );

	// Push back the current matrices and go orthographic for text rendering.
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0, (double)windowSize->getWidth(), (double)windowSize->getHeight(), 0, -1, 1 );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	delete windowSize;
}


void Object2D::render()
{
	push2DState();
		renderObject();
	pop2DState();

}

/*
 * Pop attributes used to render in 2D
 */
void Object2D::pop2DState()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();
	glPopClientAttrib();
}

}

