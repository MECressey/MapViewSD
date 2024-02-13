#include "geotools.hpp"

void DrawLine( const Transform &, CDC *dc, XY_t pts[], int nPts, bool drawDir = false );

void DrawPolygon(const Transform&, CDC* dc, XY_t pts[], int nPt);
