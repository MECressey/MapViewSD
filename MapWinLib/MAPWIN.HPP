//
//	Copyright (c) 1994-1995, Object-Based Technologies.
//	All rights reserved.
//
#if ! defined( MAPWIN_HPP )
#define MAPWIN_HPP

#include "transmat.hpp"
#include "range.hpp"
#include "mapproj.hpp"

class MapWindow : public TransMatrix
{
  public :
		MapWindow( int invertX = 0, int invertY = 0 );
		~MapWindow();
		void Forward( XY_t *out, const XY_t &in ) const;
		void Reverse( XY_t *out, const XY_t &in ) const;
		int GetRange( Range2D * ) const;
		void SetViewport( const Range2D & );	// graphic device units
		void SetRotation( double );				// Rotation angle (radians)
		void Set( MapProjection * );			// 0 turns off
		void Set( const Range2D & );			// Range to be mapped
		void Set( const XY_t &Center );			// New center point
		void ScaleByFactor( double );			// Scaling factor (must be > 0)
		void SlideByOffset( const XY_t & );		// Center offset values
		void PanByDisplay( const XY_t & );		// Offset in normalized units (viewport)
//	void Get( XY_t *, const XY_t & ) const;
//	const TransMatrix &GetTransform( void ) const;
	MapProjection *GetMapProjection( void ) const;
	
  private :
		Range2D viewPort;
		unsigned flags;
		double rotation;
		double scale;
		double yscale;
		XY_t center;
		double invert_x;
		double invert_y;
//	TransMatrix transform;
		MapProjection *mapProj;
	
	void SetTransMatrix( void );
};

/*inline const TransMatrix &MapWindow::GetTransform( void ) const
{
  return( this->transform );
}
*/

inline MapProjection *MapWindow::GetMapProjection( void ) const
{
  return( this->mapProj );
}

#endif
