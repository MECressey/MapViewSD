//
//	MapWin.hpp - implementation for the MapWindow class which is a tool for doing map display operations
//  Copyright(C) 2024 Michael E. Cressey
//
//	This program is free software : you can redistribute it and /or modify it under the terms of the
//	GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//	implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with this program.
//  If not, see https://www.gnu.org/licenses/
//
#include <math.h>

#include "mapwin.hpp"

MapWindow::MapWindow( int invertX, int invertY )
{
  this->mapProj = 0;
  this->flags = 0;
  this->rotation = 0;
  this->scale = 1;
  this->yscale = 1;
  if( invertX )
		this->invert_x = -1.0;
  else
		this->invert_x = 1.0;

  if( invertY )
		this->invert_y = -1.0;
  else
		this->invert_y = 1.0;
}

MapWindow::~MapWindow()
{
}

void MapWindow::Forward( XY_t *out, const XY_t &in ) const
{
  XY_t pt;
  
  if( this->mapProj )
  {
		this->mapProj->Forward( &pt, in );
/*	pt.x = ::RadToDeg( pt.x );
	pt.y = ::RadToDeg( pt.y );*/
  }
  else
    pt = in;

  this->TransMatrix::Forward( out, pt );
}

void MapWindow::Reverse( XY_t *out, const XY_t &in ) const
{
  XY_t pt;
  
  this->TransMatrix::Reverse( &pt, in );

  if( this->mapProj )
  {
		this->mapProj->Reverse( out, pt );
		/*out->x = ::RadToDeg(out->x);
		out->y = ::RadToDeg( out->y );*/
  }
  else
    *out = pt;

/*  XY_t pt;
  
  if( this->mapProj )
	this->mapProj->Reverse( &pt, in );
  else
    pt = in;

  this->TransMatrix::Reverse( out, pt );*/
}

//	Returns the range of data (database units) covered by the window.
int MapWindow::GetRange( Range2D *range ) const
{
  XY_t corner_in,
		corner_out;

//	Reverse transform the corners of the viewport and determine the
//	surrounding range

//	Lower left corner
	corner_in.x = this->viewPort.x.min;
	corner_in.y = this->viewPort.y.min;
	this->Reverse( &corner_out, corner_in );

	range->Range2D::Init( corner_out );

//	Upper left corner
	corner_in.y = this->viewPort.y.max;
	this->Reverse( &corner_out, corner_in );
	range->Range2D::Add( corner_out );

//	Upper right corner
	corner_in.x = this->viewPort.x.max;
	this->Reverse( &corner_out, corner_in );
	range->Range2D::Add( corner_out );

//	Lower right corner
	corner_in.y = this->viewPort.y.min;
	this->Reverse( &corner_out, corner_in );
	range->Range2D::Add( corner_out );

	return( 1 );
}


//	Sets the viewport in the window
void MapWindow::SetViewport( const Range2D &viewport )
{
  this->viewPort = viewport;
}

//	Builds a transform matrix from fields in the window.
//	2D transformation setup only for now !!!!!!
void MapWindow::SetTransMatrix( void )
{
  double matrix[4][4];

//	Compute the rotation and scale portion of the matrix using
//	the scale, rotation, and inversion factors.
  {
		double rot_sin = sin( this->rotation );
		double rot_cos = cos( this->rotation );

		matrix[0][0] = this->scale * rot_cos * this->invert_x;
		matrix[0][1] = - this->scale * rot_sin * this->invert_x;
		matrix[0][2] = 	matrix[0][3] = 0.0;
		matrix[1][0] = this->yscale * rot_sin * this->invert_y;
		matrix[1][1] = this->yscale * rot_cos * this->invert_y;
		matrix[1][2] = matrix[1][3] = matrix[2][0] =
		matrix[2][1] = matrix[2][2] = matrix[2][3] = 0.0;
  }

//	Compute the offsets (4,1), (4,2) so that the desired center point will
//	fall at the middle of the viewport.  This is done by subtracting
//	the converted center point (passed through the scale & rotation
//	portion of the matrix) from the center of the viewport.
  matrix[3][0] = ( this->viewPort.x.max + this->viewPort.x.min ) * 0.5 -
			 ( this->center.x * matrix[0][0] + this->center.y * matrix[1][0] );
  matrix[3][1] = ( this->viewPort.y.max + this->viewPort.y.min ) * 0.5 -
				 ( this->center.x * matrix[0][1] +
					this->center.y * matrix[1][1] );
  matrix[3][2] = 0.0;
  matrix[3][3] = 1.0;

//	Send the matrix to the transformation object and resize the scalable
//	cursor using the new scaling factor.

  this->TransMatrix::Init( matrix, Point::_2D );
}


//	Adjust the window transformation so that the specified range will fit
//	within the window display area.  The area drawn may be larger than the
//	requested range but the entire requested range must be drawn.  The rotation
//	should not be effected by this command.
void MapWindow::Set( const Range2D &area )
{
  double inSize_x,
		 inSize_y,
		 rot_sin = sin( this->rotation ),
		 rot_cos = cos( this->rotation );
  Range2D range = area;

  if( this->mapProj )
  {
		XY_t ll,
			 ur,
			 center;

		range.Corners( &ll, &ur );
		range.Center( &center );
		this->mapProj->Set( center.x, center.y );

		this->mapProj->Forward( &ll, ll );
		this->mapProj->Forward( &ur, ur );
		range.Init( ll, ur );
  }

//	Compute the size of the rotated input range.
  {
		double xdiff,
				   ydiff;

		xdiff = range.x.max - range.x.min;
		ydiff = range.y.max - range.y.min;
		inSize_x = fabs( xdiff * rot_cos ) + fabs( ydiff * rot_sin );
		inSize_y = fabs( xdiff * rot_sin ) + fabs( ydiff * rot_cos );
  }

//	Compute the scale required to fit the rotated input into the output
//	viewport.
  {
		double scale_temp;

		this->scale = ( this->viewPort.x.max - this->viewPort.x.min ) / inSize_x;
		scale_temp = ( this->viewPort.y.max - this->viewPort.y.min ) / inSize_y;
		if( scale_temp < this->scale )
		  this->scale = scale_temp;
		this->yscale = this->scale;
  }

//	Compute the center of the input range.
  this->center.x = ( range.x.min + range.x.max ) * 0.5;
  this->center.y = ( range.y.min + range.y.max ) * 0.5;

//	Setup the transformation matrix and pass it to the transformation.
  this->SetTransMatrix();
}


//	Adjust the window transformation so that input to output units are rotated
//	around the center by the specified rotation angle.
//	NOTE: For fit and other commands to work properly, the rotation angle
//	must be set before they are called.
void MapWindow::SetRotation( double rotation )
{
  this->rotation = rotation;
  this->SetTransMatrix();
}

void MapWindow::Set( MapProjection *mp )
{
  this->mapProj = mp;
}

//	Adjust the window transformation so that the specified location will fall
//	at the center of the display area.  Neither scale nor rotation should be
//	effected by this command.
void MapWindow::Set( const XY_t &Center )
{
  XY_t pt = Center;

  if( this->mapProj )
  {
		this->mapProj->Set( pt.x, pt.y );
		this->mapProj->Forward( &pt, pt );
  }

  this->center = pt;
  this->SetTransMatrix();
}


//	Adjust the window transformation so that the current scale is multiplied by
//	the specified factor.  Neither the center nor the rotation should be
//	effected by this command.
//	NOTE: A factor of 1.0 will have no effect on the transformation.
//	A factor of 2.0 will show an any 1/4 the size in the window.  A factor
//	of 0.5 will show an area 4 times larger in the window.
void MapWindow::ScaleByFactor(  double scale_factor )
{
  this->scale *= scale_factor;
  this->yscale *= scale_factor;
  this->SetTransMatrix();
}

//	Adjust the window transformation so that the specified center will fall at
//	the current center adjusted by (plus) the specified offset values.  Neither
//	scale nor rotation should be effected by this command.
void MapWindow::SlideByOffset( const XY_t &offset )
{
  this->center.x += offset.x;
  this->center.y += offset.y;

  this->SetTransMatrix();
}


//	Adjust the window transformation so that the window is offset as if the
//	viewport had been moved the specified amount.  The viewport movement is
//	specified in units such that 1 unit in x equals the viewport width and 1
//	unit in y equals the viewport height.  Thus a specification of (0,1) would
//	cause the window to be adjusted such that the top of the old window becomes
//	the bottom of the new window, and (-1,0) would cause the right side of the
//	old window to become the left side of the new window.  Neither scale nor
//	rotation should be effected by this command.
void MapWindow::PanByDisplay( const XY_t &viewport_loc )
{
  XY_t vcenter_new;
  double vfactor;

//	Compute the new center in viewport space.
//	NOTE: If the viewport is inverted in X or Y the factor must be
//	subtracted rather than added.

//	Compute X
  vcenter_new.x = ( this->viewPort.x.max + this->viewPort.x.min ) * 0.5;
  vfactor = ( this->viewPort.x.max - this->viewPort.x.min ) * viewport_loc.x;
  if( this->invert_x < 0.0 )
		vcenter_new.x -= vfactor;
  else
		vcenter_new.x += vfactor;
//

//	Compute Y
  vcenter_new.y = ( this->viewPort.y.max + this->viewPort.y.min ) * 0.5;
  vfactor = ( this->viewPort.y.max - this->viewPort.y.min ) * viewport_loc.y;
  if( this->invert_y < 0.0 )
		vcenter_new.y -= vfactor;
  else
		vcenter_new.y += vfactor;

  this->TransMatrix::Reverse( &this->center, vcenter_new );
  this->SetTransMatrix();
}

#ifdef SAVE_FOR_NOW

void MapWindow::Draw( CDC *dc, XY_t pts[], int nPts )
{
  int count = 0;
  XY_t prevPt;
  CPoint prevCPt;

  if( this->mapProj )
	this->mapProj->Forward( &prevPt, pts[ 0 ] );
  else
    prevPt = pts[0];
  this->transform.Forward( &prevPt, prevPt );
  unsigned poscode1 = this->viewPort.Position( prevPt );
  BOOL doMove = TRUE;
  for( int i = 1; i < nPts; i++ )
  {
	XY_t currPt,
	     clipPt1,
	     clipPt2;
	
	if( this->mapProj )
	  this->mapProj->Forward( &currPt, pts[ i ] );
	else
	  currPt = pts[ i ];  
	this->transform.Forward( &currPt, currPt );
    unsigned poscode2 = this->viewPort.Position( currPt );

    if( this->viewPort.Clip( prevPt, poscode1, currPt, poscode2,
    	&clipPt1, &clipPt2 ) == 0 )
    {
	  if( ! doMove )
	  {
	    dc->LineTo( prevCPt );
		doMove = TRUE;
	  }
	  goto NEXT_POINT;
	}
//
//	If the points are the same, ignore them for they are either outside or
//	a duplicate point???
	if( clipPt1.x != clipPt2.x ||  clipPt1.y != clipPt2.y )
	{
	  CPoint cPt1( (int)clipPt1.x, (int)clipPt1.y );
	  CPoint cPt2( (int)clipPt2.x, (int)clipPt2.y );
	
	  if( doMove )
	  {
	    dc->MoveTo( cPt1 );
	    prevCPt = cPt2;
		doMove = FALSE;
	  }
	  else
	  {
	    dc->LineTo( prevCPt );
		prevCPt = cPt2;
/*		if( poscode2 != 0 )
		{
		  dc->MoveTo( cPt2 );
		}*/
	  }

	  if( poscode2 != 0 )
	  {
	    dc->LineTo( prevCPt );
		doMove = TRUE;
	  }
	}

NEXT_POINT :	
    prevPt = currPt;
    poscode1 = poscode2;
  }

  if( ! doMove )
	dc->LineTo( prevCPt );
}

#endif


