//
//  Filename         : WXEdge.h
//  Author(s)        : Stephane Grabli
//  Purpose          : Classes to define an Extended Winged Edge data structure.
//  Date of creation : 26/10/2003
//
///////////////////////////////////////////////////////////////////////////////


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

#ifndef  WXEDGE_H
# define WXEDGE_H

# include "WEdge.h"
# include "Nature.h"
# include "Curvature.h"

typedef Nature::EdgeNature WXNature;

                  /**********************************/
                  /*                                */
                  /*                                */
                  /*             WXVertex           */
                  /*                                */
                  /*                                */
                  /**********************************/

class WXVertex : public WVertex
{  
private:
  // Curvature info
  CurvatureInfo *_curvatures;

public:
  inline WXVertex(const Vec3r &v)
    : WVertex(v)
  {_curvatures = 0;}
  /*! Copy constructor */
  WXVertex(WXVertex& iBrother)
    : WVertex(iBrother)
  {_curvatures = new CurvatureInfo(*iBrother._curvatures);}
  virtual WVertex * dupplicate()
  {
    WXVertex *clone = new WXVertex(*this);
    return clone;
  }
  virtual ~WXVertex() {if(_curvatures) delete _curvatures;}
  virtual void Reset() {if(_curvatures) _curvatures->Kr = 0.0;}
  inline void setCurvatures(CurvatureInfo *ci) {_curvatures = ci;}
  
  inline bool isFeature();
  inline CurvatureInfo* curvatures() {return _curvatures;}

};



                  /**********************************/
                  /*                                */
                  /*                                */
                  /*             WXEdge             */
                  /*                                */
                  /*                                */
                  /**********************************/
class WXEdge : public WEdge
{
private:
  WXNature _nature; // flag to indicate whether the edge is a silhouette edge or not
  int _order; // 0: the order doesn't matter. 1: the order is the orginal one. -1: the order is not good
  bool _front;  // a front facing edge is an edge for which the bording face which is the nearest 
                // from the viewpoint is front. A back facing edge is the opposite.
   
public:
  inline WXEdge()
    : WEdge(){
    _nature = Nature::NO_FEATURE;
    _front = false;
    _order=0;
  }

  inline WXEdge(WOEdge *iOEdge)
    : WEdge(iOEdge)
  { _nature = Nature::NO_FEATURE;_front = false;_order=0;}

  inline WXEdge(WOEdge *iaOEdge, WOEdge *ibOEdge)
    : WEdge(iaOEdge, ibOEdge)
  { _nature = Nature::NO_FEATURE;_front = false;_order=0;}

  /*! Copy constructor */
  inline WXEdge(WXEdge& iBrother)
    : WEdge(iBrother)
  {_nature = iBrother.nature();_front = iBrother._front;_order = iBrother._order;}
  virtual WEdge * dupplicate()
  {
    WXEdge *clone = new WXEdge(*this);
    return clone;
  }

  virtual ~WXEdge()
  {}

  virtual void Reset(){
    _nature  = _nature & ~Nature::SILHOUETTE;
    _nature  = _nature & ~Nature::SUGGESTIVE_CONTOUR;
  }

  /*! accessors */
  inline WXNature nature() {return _nature;}
  inline bool front() {return _front;}
  inline int order() const {return _order;}
  
  /*! modifiers */
  inline void SetFront(bool iFront) {_front = iFront;}
  inline void SetNature(WXNature iNature) {_nature = iNature;}
  inline void AddNature(WXNature iNature) {_nature = _nature|iNature;}
  inline void SetOrder(int i) {_order = i;}
  
};

                  /**********************************/
                  /*                                */
                  /*                                */
                  /*             WXFace             */
                  /*                                */
                  /*                                */
                  /**********************************/

/*! Class to store a smooth edge (i.e Hertzman & Zorin smooth silhouette edges) */
class WXSmoothEdge{
public:
  typedef enum{
    EDGE_EDGE,
    VERTEX_EDGE,
    EDGE_VERTEX
  } Configuration;

  WOEdge *_woea; // Oriented edge from which the silhouette edge starts
  WOEdge *_woeb; // Oriented edge where the silhouette edge ends
  real _ta;    // The silhouette starting point's coordinates are : _woea[0]+ta*(_woea[1]-_woea[0])
  real _tb;    // The silhouette ending point's coordinates are : _woeb[0]+ta*(_woeb[1]-_woeb[0])
  bool _front;
  Configuration _config;

  WXSmoothEdge(){
    _woea = 0;
    _woeb = 0;
    _ta = 0;
    _tb = 0;
    _front = false;
    _config = EDGE_EDGE;
  }
  WXSmoothEdge(const WXSmoothEdge& iBrother){
    _woea = iBrother._woea;
    _woeb = iBrother._woeb;
    _ta = iBrother._ta;
    _tb = iBrother._tb;
    _config = iBrother._config;
    _front = iBrother._front;
  }
  ~WXSmoothEdge() {}

  inline WOEdge * woea() {return _woea;}
  inline WOEdge * woeb() {return _woeb;}
  inline real ta() const {return _ta;}
  inline real tb() const {return _tb;}
  inline bool front() const {return _front;}
  inline Configuration configuration() const {return _config;} 
  
  /*! modifiers */
  inline void SetWOeA(WOEdge *iwoea) {_woea = iwoea;}
  inline void SetWOeB(WOEdge *iwoeb) {_woeb = iwoeb;}
  inline void SetTa(real ta) {_ta = ta;}
  inline void SetTb(real tb) {_tb = tb;}
  inline void SetFront(bool iFront) {_front = iFront;}
  inline void SetConfiguration(Configuration iConf) {_config = iConf;}
  
};
/* Class to store a value per vertex and a smooth edge. 
 * The WXFace stores a list of these 
 */
class WXFace;
class LIB_WINGED_EDGE_EXPORT WXFaceLayer{
public:
  void * userdata;
  WXFace * _pWXFace;
  vector<real> _DotP;// in case of silhouette: the values obtained when computing the normal-view direction 
                         // dot product. _DotP[i] is this value for the vertex i for that 
                          // face.
  WXSmoothEdge * _pSmoothEdge;
  WXNature _Nature;

  //tmp values
  unsigned _nPosDotP; // count the number of positive dot products for vertices.
                      // if this number is != 0 and !=_DotP.size() -> it is a silhouette fac

  unsigned _nNullDotP; // count the number of null dot products for vertices.
  unsigned _ClosestPointIndex;
  bool _viewDependant;

  WXFaceLayer(WXFace *iFace, WXNature iNature, bool viewDependant){
    _pWXFace = iFace;
    _pSmoothEdge = 0;
    _nPosDotP = 0;
    _nNullDotP=0;
    _Nature = iNature;
    _viewDependant = viewDependant;
    userdata = 0;
  }
  WXFaceLayer(const WXFaceLayer& iBrother){
    _pWXFace = iBrother._pWXFace;
    _pSmoothEdge = 0;
    _DotP = iBrother._DotP;
    _nPosDotP = iBrother._nPosDotP;
    _nNullDotP = iBrother._nNullDotP;
    _Nature = iBrother._Nature;
    if(0 != iBrother._pSmoothEdge)
    {
      _pSmoothEdge = new WXSmoothEdge(*(iBrother._pSmoothEdge));
    }
    _viewDependant = iBrother._viewDependant;
    userdata = 0;
  }
  virtual ~WXFaceLayer() {
    if(!_DotP.empty())
      _DotP.clear();
    if(0 != _pSmoothEdge){
      delete _pSmoothEdge;
      _pSmoothEdge = 0;
    }
  }
  inline const real dotP(int i) const {return _DotP[i];}
  inline unsigned nPosDotP() const {return _nPosDotP;}
  inline unsigned nNullDotP() const {return _nNullDotP;}
  inline int closestPointIndex() const {return _ClosestPointIndex;}
  inline Nature::EdgeNature nature() const {return _Nature;}
  inline bool hasSmoothEdge() const {if(_pSmoothEdge) return true; return false;}
  inline WXFace * getFace() {return _pWXFace;}
  inline WXSmoothEdge * getSmoothEdge() {return _pSmoothEdge;}
  inline bool isViewDependant() const {return _viewDependant;}
  inline void SetClosestPointIndex(int iIndex) {_ClosestPointIndex = iIndex;}

  inline void removeSmoothEdge() {
    if(!_DotP.empty())
      _DotP.clear();
    if (_pSmoothEdge) {
      delete _pSmoothEdge;
      _pSmoothEdge = 0;
    }
  }

  /*! If one of the face layer vertex has a DotP equal
   *  to 0, this method returns the vertex where it happens
   */
  unsigned int Get0VertexIndex() const ;

  /*! In case one of the edge of the triangle 
   *  is a smooth edge, this method 
   *  allows to retrieve the concerned edge
   */
  unsigned int GetSmoothEdgeIndex() const;
  /*! retrieves the edges of the triangle for which 
   *  the signs are different (a null value is not considered) for the dotp 
   *  values at each edge extrimity
   */
  void RetrieveCuspEdgesIndices(vector<int>& oCuspEdges);
  WXSmoothEdge * BuildSmoothEdge();
  inline void SetDotP(const vector<real>& iDotP) {_DotP = iDotP;}
  inline void PushDotP(real iDotP) {
    _DotP.push_back(iDotP);
    if(iDotP > 0)
      ++_nPosDotP;
    if(iDotP == 0)
      ++_nNullDotP;
  }
  inline void ReplaceDotP(unsigned int index, real newDotP){
    _DotP[index] = newDotP;
    updateDotPInfos();
  }
  inline void updateDotPInfos() {
    for(vector<real>::iterator d=_DotP.begin(), dend=_DotP.end();
    d!=dend;
    ++d){
      _nPosDotP = 0;
      _nNullDotP = 0;
      if((*d) > 0)
        ++_nPosDotP;
      if((*d) == 0)
        ++_nNullDotP;
    }
  }
};


class WXFace : public WFace
{
protected:
  Vec3r _center; // center of the face
  real _Z; // distance from viewpoint to the center of the face
  bool _front; // flag to tell whether the face is front facing or back facing
  real _dotp;  // value obtained when computing the normal-viewpoint dot product
 
  vector<WXFaceLayer*> _SmoothLayers; // The data needed to store one or several smooth edges that traverse the face
public:
  inline WXFace() : WFace() {_Z=0.0;_front = false;}
  /*! Copy constructor */
  WXFace(WXFace& iBrother)
    : WFace(iBrother)
  {
    _center = iBrother.center();
    _Z = iBrother.Z();
    _front = iBrother.front();
    for(vector<WXFaceLayer*>::iterator wxf = iBrother._SmoothLayers.begin(), wxfend = iBrother._SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      _SmoothLayers.push_back(new WXFaceLayer(**wxf));
    }
  }
  virtual WFace * dupplicate()
  {
    WXFace * clone = new WXFace(*this);
    return clone;
  }

  virtual ~WXFace() {
    if(!_SmoothLayers.empty()){
      for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
      wxf != wxfend;
      ++wxf){
        delete (*wxf);
      }
      _SmoothLayers.clear();
    } 
  }

  /*! designed to build a specialized WEdge 
   *  for use in MakeEdge
   */
  virtual WEdge * instanciateEdge() const {return new WXEdge;}
  
  /*! accessors */
  inline Vec3r& center() {return _center;}
  inline real Z() {return _Z;}
  inline bool front() {return _front;}
  inline real dotp() {return _dotp;}
  inline bool hasSmoothEdges() const {
    for(vector<WXFaceLayer*>::const_iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      if( ((*wxf)->hasSmoothEdge())){
        return true;
      }
    }
    return false;
  }
  vector<WXFaceLayer*>& getSmoothLayers() {return _SmoothLayers;}
  /*! retrieve the smooth edges that match the Nature given as argument */
  void retrieveSmoothEdges(WXNature iNature, vector<WXSmoothEdge*>& oSmoothEdges){
    for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      if( ((*wxf)->hasSmoothEdge()) && ((*wxf)->_Nature & iNature) ){
        oSmoothEdges.push_back((*wxf)->_pSmoothEdge);
      }
    }
  }
  void retrieveSmoothEdgesLayers(WXNature iNature, vector<WXFaceLayer*>& oSmoothEdgesLayers){
    for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      if( ((*wxf)->hasSmoothEdge()) && ((*wxf)->_Nature & iNature) ){
        oSmoothEdgesLayers.push_back((*wxf));
      }
    }
  }
  void retrieveSmoothLayers(WXNature iNature, vector<WXFaceLayer*>& oSmoothLayers){
    for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      if((*wxf)->_Nature & iNature){
        oSmoothLayers.push_back(*wxf);
      }
    }
  }
  /*! modifiers */
  inline void SetCenter(const Vec3r& iCenter) {_center = iCenter;}
  void ComputeCenter();
  inline void SetZ(real z) {_Z = z;}
  inline void SetFront(bool iFront) {_front = iFront;}
  inline void SetDotP(real iDotP) 
  {
    _dotp = iDotP;
    if(_dotp > 0)
      _front = true;
    else
      _front = false;
  }
  inline void AddSmoothLayer(WXFaceLayer * iLayer){
    _SmoothLayers.push_back(iLayer);
  }
  inline void Reset() {
    vector<WXFaceLayer*> layersToKeep;
    for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      if((*wxf)->isViewDependant())
        delete (*wxf);
      else
        layersToKeep.push_back(*wxf);
    }
    _SmoothLayers = layersToKeep;
  }
  /*! Clears everything */
  inline void Clear() {
    for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      delete (*wxf);
    }
    _SmoothLayers.clear();
  }
  virtual void ResetUserData() {
    WFace::ResetUserData();
    for(vector<WXFaceLayer*>::iterator wxf = _SmoothLayers.begin(), wxfend = _SmoothLayers.end();
    wxf != wxfend;
    ++wxf){
      (*wxf)->userdata = 0;
    }
  }
};


                  /**********************************/
                  /*                                */
                  /*                                */
                  /*             WXShape            */
                  /*                                */
                  /*                                */
                  /**********************************/


class WXShape : public WShape
{
public:
  typedef WXShape type_name;
protected:
  bool _computeViewIndependant; // flag to indicate whether the view independant stuff must be computed or not
public:
  inline WXShape() : WShape() {_computeViewIndependant = true;}
  /*! copy constructor */
  inline WXShape(WXShape& iBrother)
    :WShape(iBrother)
  {
    _computeViewIndependant = iBrother._computeViewIndependant;
  }
  virtual WShape * dupplicate()
  {
    WXShape *clone = new WXShape(*this);
    return clone;
  }
  
  virtual ~WXShape()
  {
  }
 
  inline bool getComputeViewIndependantFlag() const {return _computeViewIndependant;}
  inline void setComputeViewIndependantFlag(bool iFlag) {_computeViewIndependant = iFlag;}

  /*! designed to build a specialized WFace 
   *  for use in MakeFace
   */
  virtual WFace * instanciateFace() const {return new WXFace;}

 /*! adds a new face to the shape 
  *  returns the built face.
  *   iVertexList 
  *      List of face's vertices. These vertices are 
  *      not added to the WShape vertex list; they are 
  *      supposed to be already stored when calling MakeFace.
  *      The order in which the vertices are stored in the list 
  *      determines the face's edges orientation and (so) the 
  *      face orientation.
  */
  virtual WFace * MakeFace(vector<WVertex*>& iVertexList, unsigned iMaterialIndex);

  /*! adds a new face to the shape. The difference with 
   *  the previous method is that this one is designed 
   *  to build a WingedEdge structure for which there are 
   *  per vertex normals, opposed to per face normals.
   *  returns the built face.
   *   iVertexList 
   *      List of face's vertices. These vertices are 
   *      not added to the WShape vertex list; they are 
   *      supposed to be already stored when calling MakeFace.
   *      The order in which the vertices are stored in the list 
   *      determines the face's edges orientation and (so) the 
   *      face orientation.
   *   iNormalsList
   *     The list of normals, iNormalsList[i] corresponding to the 
   *     normal of the vertex iVertexList[i] for that face.
   *   iTexCoordsList
   *     The list of tex coords, iTexCoordsList[i] corresponding to the 
   *     normal of the vertex iVertexList[i] for that face.
   */
  virtual WFace * MakeFace(vector<WVertex*>& iVertexList, vector<Vec3r>& iNormalsList, vector<Vec2r>& iTexCoordsList, unsigned iMaterialIndex);

  /*! Reset all edges and vertices flags (which might
   *  have been set up on a previous pass)
   */
  virtual void Reset(){
    // Reset Edges
    vector<WEdge*>& wedges = GetEdgeList();
    for(vector<WEdge*>::iterator we=wedges.begin(),weend=wedges.end();
    we!=weend;
    we++){
      ((WXEdge*)(*we))->Reset();
    }

    //Reset faces:
    vector<WFace*>& wfaces = GetFaceList();
    for(vector<WFace*>::iterator wf=wfaces.begin(),wfend=wfaces.end();
    wf!=wfend;
    wf++){
      ((WXFace*)(*wf))->Reset();
    }
  }
  /*! accessors */
};

/*
  
  #############################################
  #############################################
  #############################################
  ######                                 ######
  ######   I M P L E M E N T A T I O N   ######
  ######                                 ######
  #############################################
  #############################################
  #############################################
  
*/
/* for inline functions */

bool WXVertex::isFeature() 
{ 
  int counter = 0;
  vector<WEdge*>& vedges = GetEdges();
  for(vector<WEdge*>::iterator ve=vedges.begin(), vend=vedges.end();
  ve!=vend;
  ve++)
  {
    if(((WXEdge*)(*ve))->nature() != Nature::NO_FEATURE)
      counter++;
  }
  
  if((counter == 1) || (counter > 2))
    return true;
  
  return false;
}


#endif
