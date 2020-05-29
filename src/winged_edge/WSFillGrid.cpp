
//
//  Copyright (C) : Please refer to the COPYRIGHT file distributed 
//   with this source distribution. 
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
///////////////////////////////////////////////////////////////////////////////

#include "WEdge.h"
#include "WSFillGrid.h"

void WSFillGrid::fillGrid() {
  if (!_winged_edge || !_grid)
    return;

  vector<WShape*>	wshapes = _winged_edge->getWShapes();
  vector<WVertex*>	fvertices;
  vector<Vec3r>		vectors;
  vector<WFace*>	faces;

  for (vector<WShape*>::const_iterator it = wshapes.begin();
       it != wshapes.end();
       it++) {
    faces = (*it)->GetFaceList();

    for (vector<WFace*>::const_iterator f = faces.begin();
	 f != faces.end();
	 f++) {
      (*f)->RetrieveVertexList(fvertices);

      for (vector<WVertex*>::const_iterator wv = fvertices.begin();
	   wv != fvertices.end();
	   wv++)
        vectors.push_back(Vec3r((*wv)->GetVertex()));

      // occluder will be deleted by the grid
      Polygon3r *occluder =
	new Polygon3r(vectors, (*f)->GetNormal());
      occluder->setId(_polygon_id++);
      occluder->userdata = (void*)(*f);
      _grid->insertOccluder(occluder);
      vectors.clear();
      fvertices.clear();
    }
    faces.clear();
  }
}