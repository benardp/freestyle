//
//  Filename         : Config.h
//  Author(s)        : Emmanuel Turquin
//  Purpose          : Configuration definitions
//  Date of creation : 25/02/2003
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


#ifndef  CONFIG_H
# define CONFIG_H

# include <string>

using namespace std;

namespace Config {

  // Pi definition
# ifndef M_PI
#  define M_PI 3.14159265
# endif // M_PI

  // Directory separators
# ifdef WIN32
  static const string DIR_SEP("\\");
  static const string PATH_SEP(";");
# else
  static const string DIR_SEP("/");
  static const string PATH_SEP(":");
# endif // WIN32

  // DLL import/export macros for Win32

# ifdef WIN32
#  ifdef MAKE_LIB_SYSTEM_DLL
#   define LIB_SYSTEM_EXPORT __declspec(dllexport)
#  else
#   define LIB_SYSTEM_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_SYSTEM_DLL

#  ifdef MAKE_LIB_IMAGE_DLL
#   define LIB_IMAGE_EXPORT __declspec(dllexport)
#  else
#   define LIB_IMAGE_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_IMAGE_DLL

#  ifdef MAKE_LIB_GEOMETRY_DLL
#   define LIB_GEOMETRY_EXPORT __declspec(dllexport)
#  else
#   define LIB_GEOMETRY_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_GEOMETRY_DLL

#  ifdef MAKE_LIB_SCENE_GRAPH_DLL
#   define LIB_SCENE_GRAPH_EXPORT __declspec(dllexport)
#  else
#   define LIB_SCENE_GRAPH_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_SCENE_GRAPH_DLL

#  ifdef MAKE_LIB_WINGED_EDGE_DLL
#   define LIB_WINGED_EDGE_EXPORT __declspec(dllexport)
#  else
#   define LIB_WINGED_EDGE_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_WINGED_EDGE_DLL

#  ifdef MAKE_LIB_VIEW_MAP_DLL
#   define LIB_VIEW_MAP_EXPORT __declspec(dllexport)
#  else
#   define LIB_VIEW_MAP_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_VIEW_MAP_DLL

#  ifdef MAKE_LIB_STROKE_DLL
#   define LIB_STROKE_EXPORT __declspec(dllexport)
#  else
#   define LIB_STROKE_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_STROKE_DLL

#  ifdef MAKE_LIB_RENDERING_DLL
#   define LIB_RENDERING_EXPORT __declspec(dllexport)
#  else
#   define LIB_RENDERING_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_RENDERING_DLL

#  ifdef MAKE_LIB_WRAPPER_DLL
#   define LIB_WRAPPER_EXPORT __declspec(dllexport)
#  else
#   define LIB_WRAPPER_EXPORT __declspec(dllimport)
#  endif // MAKE_LIB_WRAPPER_DLL

# else
#  ifndef LIB_SYSTEM_EXPORT
#   define LIB_SYSTEM_EXPORT
#  endif // LIB_SYSTEM_EXPORT

#  ifndef LIB_IMAGE_EXPORT
#   define LIB_IMAGE_EXPORT
#  endif // LIB_IMAGE_EXPORT

#  ifndef LIB_GEOMETRY_EXPORT
#   define LIB_GEOMETRY_EXPORT
#  endif // LIB_GEOMETRY_EXPORT

#  ifndef LIB_SCENE_GRAPH_EXPORT
#   define LIB_SCENE_GRAPH_EXPORT
#  endif // LIB_SCENE_GRAPH_EXPORT

#  ifndef LIB_WINGED_EDGE_EXPORT
#   define LIB_WINGED_EDGE_EXPORT
#  endif // LIB_WINGED_EDGE_EXPORT

#  ifndef LIB_VIEW_MAP_EXPORT
#   define LIB_VIEW_MAP_EXPORT
#  endif // LIB_VIEW_MAP_EXPORT

#  ifndef LIB_STROKE_EXPORT
#   define LIB_STROKE_EXPORT
#  endif // LIB_STROKE_EXPORT

#  ifndef LIB_RENDERING_EXPORT
#   define LIB_RENDERING_EXPORT
#  endif // LIB_RENDERING_EXPORT

#  ifndef LIB_WRAPPER_EXPORT
#   define LIB_WRAPPER_EXPORT
#  endif // LIB_WRAPPER_EXPORT

# endif // WIN32

} // end of namespace Config

#endif // CONFIG_H
