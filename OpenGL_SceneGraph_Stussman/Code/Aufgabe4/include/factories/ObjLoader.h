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

#include <vector>
#include <fstream>

using namespace std;

struct vertex3D										// Struct for a 3D vertex
{
	float x;
	float y;
	float z;
};

struct vertex2D										// Struct for a 2D vertex (texture coordinates)
{
	float x;
	float y;
};

struct triang										// Struct for all values for a triangle
{
	vertex3D vertex1;
	vertex3D vertex2;
	vertex3D vertex3;

	vertex3D normal1;
	vertex3D normal2;
	vertex3D normal3;

	vertex2D tCoord1;
	vertex2D tCoord2;
	vertex2D tCoord3;

};

struct mat											// Material definitions
{
	float matAmbient[4];
	float matDiffuse[4];
	float matSpecular[4];
	float matShininess;
};

struct group										// Definition for an object group
{
	triang* triangle;									// Pointer to an array of triangles
	mat material;
	char* textureName;
	int textureID;
	int size;
};

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

		void open(const char* fn_geo, const char* fn_mat);
		void groupsizes(int* sizeofgroup);
		void close();


		void load(int groupIndex, group *Gruppe);
					
		int numTriangles;
		int numGeom;
		int border[20];  // max. 20 geometries!

};

#endif
