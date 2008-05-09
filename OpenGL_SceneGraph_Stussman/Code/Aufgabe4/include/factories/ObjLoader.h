/**************************************************/
/*                                                */
/*  OBJECT-FILE LOADER HEADER                     */
/*                                                */
/**************************************************/
/*  Concept & Design:       D. Bachofen (ZHW)     */
/*                          bcd@zhwin.ch          */
/*                                                */
/*  Adaption & Redesign:    R.Bollinger           */
/*                          bolliret@zhwin.ch     */
/**************************************************/
/*  Date:                   15. October 2004      */
/**************************************************/

#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include "main.h"
#include <vector>
#include <fstream>

/**************************************************/
/* Class, function & variable definition          */
/**************************************************/

class ObjLoader {

private:

	char line[100];
	
	char* filename_geo;
	char* filename_mat;
	
	vector<vertex3D*> v_vertex;
	vector<vertex3D*> v_normal;
	vector<vertex2D*> v_texcoord;
	vector<vertex3D*>::iterator k;
		
	ifstream objfile;
	ifstream matfile;

public:
		ObjLoader();
		~ObjLoader();

		void open(char* fn_geo, char* fn_mat);
		void groupsizes(int* sizeofgroup);
		void close();


		void load(int groupIndex, group *Gruppe);
					
		int numTriangles;
		int numGeom;
		int border[20];  // max. 20 geometries!

};

#endif
