/**************************************************/
/*                                                */
/*  OBJECT-FILE LOADER SOURCECODE                 */
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

//#include "main.h"
#include  <iostream>
#include "factories/ObjLoader.h"
using namespace std;

/**************************************************/
/* Constructor                                    */
/**************************************************/

ObjLoader::ObjLoader() {
	
}

/**************************************************/
/* Destructor                                     */
/**************************************************/

ObjLoader::~ObjLoader() {
	delete[] filename_geo;
	delete[] filename_mat;
}

/**************************************************/
/* Open files and getting basic information       */
/* about the object (trianglecount / groupcount)  */
/**************************************************/

void ObjLoader::open(char* fn_geo, char* fn_mat) {					//".obj"-filename, ".mtl"-filname
	
	// Variables
	////////////////////////////////////////////////
	
	int sizeT=0;
	int sizeG=0;
	filename_geo = fn_geo;
	filename_mat = fn_mat;
	
	// Open the ".obj"-file (where the groups
	// and geometries are defined)
	////////////////////////////////////////////////
	
	objfile.open(filename_geo, ios::in | ios::binary);
	if ((objfile.bad())||(objfile.fail())) {
		cout << "ERROR: couldn't read " << filename_geo << endl;
		exit(1);
	}
	
	// Open the ".mtl"-file (where the materials
	// are defined)
	////////////////////////////////////////////////
	
	if (strcmp(filename_mat, "")!=0) { 
		matfile.open(filename_mat, ios::in | ios::binary);
		if ((matfile.bad())||(matfile.fail())) {
			cout << "ERROR: couldn't read " << filename_mat << endl;
			exit(1);
		}
	}
	
	// reading the ".obj"-file and count the
	// triangles (lines starting with an "f")
	// and the groups (lines starting with a "g")
	// These values ar used to define the arrays
	////////////////////////////////////////////////
	
	while (!objfile.eof()) {		
		objfile.getline(line, 100);		
		if (line[0] == 'g'){
			sizeG++;
		}
	}
		
	cout << endl << "Objloader: " << filename_geo << endl;	
	cout << sizeG << " groups, " << sizeT << " triangles" << endl; 
	
	numTriangles = sizeT;
	numGeom = sizeG;	
}

void ObjLoader::groupsizes(int* sizeofgroup)
{
	objfile.clear();												//reset file
	objfile.seekg(0);

	int countG = 0;
	int countT = 0;
	
	while (!objfile.eof()) {		
		objfile.getline(line, 100);		
		if (line[0] == 'f') {
			countT++;
		}
		if (line[0] == 'g') {
			if(countG>0){
				sizeofgroup[countG - 1] = countT;				
			}
			countT=0;
			countG++;
		}
	}
	sizeofgroup[countG - 1] = countT;
}


/**************************************************/
/* Close the opened files                         */
/**************************************************/

void ObjLoader::close() {	
	objfile.close();
	if (strcmp(filename_mat, "")!=0) {
		matfile.close();
	}
}

/**************************************************/
/* Load the geometries and materials              */
/**************************************************/
void ObjLoader::load(int groupIndex, group *Gruppe) {	
	char ch;
	char str[20];
    float x, y, z;

	vertex3D* vertex_3d;
	vertex2D* vertex_2d;
	
	int groupCount=0;
	
	vertex3D *vert0;
	vertex3D *vert1;
	vertex3D *vert2;
    vertex3D *norm0;
	vertex3D *norm1;
	vertex3D *norm2;
	vertex2D *tcoordinate0;
	vertex2D *tcoordinate1;
	vertex2D *tcoordinate2;
	
	vertex3D noValue3D;
	vertex2D noValue2D;

	cout << "loading group" << groupIndex << ": ";	

	noValue3D.x = 0.0;
	noValue3D.y = 0.0;
	noValue3D.z = 0.0;
	
	noValue2D.x = 0.0;
	noValue2D.y = 0.0;

	objfile.clear();												//resetting file
	objfile.seekg(0);
	
	
	// reading vertices
	////////////////////////////////////////////////
	
	while (!objfile.eof()) {										// read vertices
		objfile.getline(line, 100);		
		// vertices
		if (line[0] == 'v') {			
			if ((line[1] != 't') && (line[1] != 'n')){				// 3d coordinates							
				sscanf(line, "%c %f %f %f" , &ch, &x, &y, &z);
				
				vertex_3d = new vertex3D();
				vertex_3d->x = x;
				vertex_3d->y = y;
				vertex_3d->z = z;				
				v_vertex.push_back(vertex_3d);
			}
			
			else if (line[1] == 'n'){ 								// normals				
				sscanf(line, "%s %f %f %f" , &str, &x, &y, &z);
				
				vertex_3d = new vertex3D();
				vertex_3d->x = x;
				vertex_3d->y = y;
				vertex_3d->z = z;
				
				v_normal.push_back(vertex_3d);
			}
			
			else if (line[1] == 't'){ 								// texture coordinates				
				sscanf(line, "%s %f %f" , &str, &x, &y);
				
				vertex_2d = new vertex2D();
				vertex_2d->x = x;
				vertex_2d->y = y;
				
				v_texcoord.push_back(vertex_2d);				
			}			
		}				
    }
	
	// create and initialize normal vector
	////////////////////////////////////////////////
	for (unsigned int i=0; i<v_vertex.size(); i++){
		v_normal.push_back(new vertex3D());
	}
	
	char t1[20];
	char t2[20];
	char t3[20];

	int tc = 0;
	
	objfile.clear();												//reset file
	objfile.seekg(0);	
	
	while (!objfile.eof()){ 											//get triangles
		objfile.getline(line, 100);									// WARNING: Definitions can only be read if they are "x/y/z"-style
		
		//new group
		if (line[0] == 'g'){
			groupCount++;
		}
		
		//load material
		if ((strncmp(line, "usemtl",6)==0)&&(groupCount == groupIndex)){ 
			char cmd[10];
			char mat[40];
			char matd[256];

			float col_r;
			float col_g;
			float col_b;

			sscanf(line, "%s %s" , &cmd, &mat);
			
			cout << mat << endl;
			
			// reading matfile
			////////////////////////////////////////
			if (strcmp(filename_mat, "")!=0) {
				matfile.clear();
				matfile.seekg(0);
				
				bool bmat = false;
				while (!matfile.eof()) {
					matfile.getline(line, 100);
					
					// read material if "bmat" is true
					if ((bmat)&&((line[0]=='K')||(line[0]=='N'))){ 
						sscanf(line, "%s %f %f %f" , &cmd, &col_r, &col_g, &col_b);
						if (strcmp(cmd, "Ka")==0){ 					// set ambient light
							Gruppe[groupIndex-1].material.matAmbient[0] = col_r;
							Gruppe[groupIndex-1].material.matAmbient[1] = col_g;
							Gruppe[groupIndex-1].material.matAmbient[2] = col_b;
							Gruppe[groupIndex-1].material.matAmbient[3] = 0.0;
						}
						if (strcmp(cmd, "Kd")==0){ 					// set diffuse light
							Gruppe[groupIndex-1].material.matDiffuse[0] = col_r;
							Gruppe[groupIndex-1].material.matDiffuse[1] = col_g;
							Gruppe[groupIndex-1].material.matDiffuse[2] = col_b;
							Gruppe[groupIndex-1].material.matDiffuse[3] = 0.0;
						}
						if (strcmp(cmd, "Ks")==0){ 					// set specular light
							Gruppe[groupIndex-1].material.matSpecular[0] = col_r;
							Gruppe[groupIndex-1].material.matSpecular[1] = col_g;
							Gruppe[groupIndex-1].material.matSpecular[2] = col_b;
							Gruppe[groupIndex-1].material.matSpecular[3] = 0.0;
						}
						if (strcmp(cmd, "Ns")==0){ 					// set shininess
							Gruppe[groupIndex-1].material.matShininess = col_r;
						}	
					}
					
					sscanf(line, "%s %s" , &cmd, &matd);			// WARNING: Texture-filenames must not contain "whitespaces" like <SPACE>
					
					if ((strcmp(cmd, "newmtl")==0)&&(strcmp(mat, matd)==0)){
						bmat = true;
					}
					else if (strcmp(cmd, "newmtl")==0){
						bmat = false;
					}
					
					if ((bmat)&&(strcmp(cmd, "map_Kd")==0)){ 		// set texture
						printf("In ObjectLoader.load \"%s\"\n", matd); 
						Gruppe[groupIndex-1].textureName = new char[sizeof(matd)];						
						strcpy(Gruppe[groupIndex-1].textureName,matd);
					}
				}				
			}									
		}
		
		// reading geometry
		////////////////////////////////////////////
				
		if ((line[0] == 'f')&&(groupCount == groupIndex)){ 			// read "faces" (triangles)
			sscanf(line, "%c %s %s %s" , &ch, &t1, &t2, &t3);		// split line in to three four parts 
																	// Scheme:      f   vx/tx/nx   /vy/ty/ny   vz/tz/nz
																	//          FACE^   ^^VERTEX-1     ^^TEXTURE-2   ^^NORMAL-3
																	// These integer-values indcate the position of the coordinate in its array
			char * pch;
		
			int i_pos=0;
			int i_norm=0; 
			int i_tcoord=0;
			int c;
			
			// read first group of coords (x-values)
			////////////////////////////////////////

			c=0;
			pch = strtok (t1,"/");									// split first group in to three values
																	//
			while (pch != NULL)										// read each value
			{														//
				if (c==0)											//
				{													//
					i_pos = atoi(pch);								// the first value represents the position (vertex)
				}													//
				if (c==1)											//
				{													//
					i_tcoord = atoi(pch);							// the second value represents the texture coordinate
				}													//
				if (c==2)											//
				{													//
					i_norm = atoi(pch);								// the third value represents the normal
				}													//
				c++;												// increase counter
																	//
				pch = strtok (NULL, "/");							// clear pch ?????????????
			}														//
																	//
			if (i_pos>0)											//
			{														//
				vert0 = v_vertex.at(i_pos-1);						// look up the value at position "i_pos" in the position array (an array starts at zero!!!)
			}														//
			else													//
			{														//
				vert0 = &noValue3D;									// if "i_pos" is still zero there is no value
			}														//
			if (i_norm>0)											//
			{														//
				norm0 = v_normal.at(i_norm-1);						// look up the value at position "i_norm" in the normal array (an array starts at zero)
			}														//
			else													//
			{														//
				norm0 = &noValue3D;									// if "i_norm" is still zero there is no value
			}														//
			if (i_tcoord>0)											//
			{														//
				tcoordinate0 = v_texcoord.at(i_tcoord-1);			// look up the value at position "i_tcoord" in the texture coordinate array (starting at zero)
			}														//
			else													//
			{														//
				tcoordinate0 = &noValue2D;							// if "i_tcoord" is still zero there is no value
			}														//
			
			// read second group of coordinates (y-values)
			///////////////////////////////////////////////
			c=0;													
			i_pos=0;												//
			i_norm=0;												//
			i_tcoord=0;												//
			pch = strtok (t2,"/");									//
			while (pch != NULL)										//
			{														//
				if (c==0) i_pos = atoi(pch);						//
				if (c==1) i_tcoord = atoi(pch);						//
				if (c==2) i_norm = atoi(pch);						//
				c++;												//
																	//
				pch = strtok (NULL, "/");							//
			}														//
																	//
			if (i_pos>0)											//
			{														//
				vert1 = v_vertex.at(i_pos-1);						//
			}														//
			else													// same procedure as for the first group
			{														//
				vert1 = &noValue3D;									//
			}														//
			if (i_norm>0)											//
			{														//
				norm1 = v_normal.at(i_norm-1);						//
			}														//
			else													//
			{														//
				norm1 = &noValue3D;									//
			}														//
			if (i_tcoord>0)											//
			{														//
				tcoordinate1 = v_texcoord.at(i_tcoord-1);			//
			}														//
			else													//
			{														//
				tcoordinate1 = &noValue2D;							//
			}														//
			
			// read third group of coordinates (z-values)
			///////////////////////////////////////////////
			
			c=0;													//
			i_pos=0;												//
			i_norm=0;												//
			i_tcoord=0;												//
			pch = strtok (t3,"/");									//
			while (pch != NULL)										//
			{														//
				if (c==0) i_pos = atoi(pch);						//
				if (c==1) i_tcoord = atoi(pch);						//
				if (c==2) i_norm = atoi(pch);						//
				c++;												//
				pch = strtok (NULL, "/");							//
			}														//
			if (i_pos>0)											//
			{														//
				vert2 = v_vertex.at(i_pos-1);						//
			}														//
			else													// same procedure as for the first group
			{														//
				vert2 = &noValue3D;									//
			}														//
			if (i_norm>0)											//
			{														//
				norm2 = v_normal.at(i_norm-1);						//
			}														//
			else													//
			{														//
				norm2 = &noValue3D;									//
			}														//
			if (i_tcoord>0)											//
			{														//
				tcoordinate2 = v_texcoord.at(i_tcoord-1);			//
			}														//
			else													//
			{														//
				tcoordinate2 = &noValue2D;							//
			}														//
			
			// Store the loaded values
			///////////////////////////////////////////////

			Gruppe[groupIndex-1].triangle[tc].vertex1.x = vert0->x;			
			Gruppe[groupIndex-1].triangle[tc].vertex2.x = vert1->x;			
			Gruppe[groupIndex-1].triangle[tc].vertex3.x = vert2->x;
			
			Gruppe[groupIndex-1].triangle[tc].vertex1.y = vert0->y;
			Gruppe[groupIndex-1].triangle[tc].vertex2.y = vert1->y;
			Gruppe[groupIndex-1].triangle[tc].vertex3.y = vert2->y;
			
			Gruppe[groupIndex-1].triangle[tc].vertex1.z = vert0->z;
			Gruppe[groupIndex-1].triangle[tc].vertex2.z = vert1->z;
			Gruppe[groupIndex-1].triangle[tc].vertex3.z = vert2->z;
			
			Gruppe[groupIndex-1].triangle[tc].normal1.x = norm0->x;
			Gruppe[groupIndex-1].triangle[tc].normal2.x = norm1->x;
			Gruppe[groupIndex-1].triangle[tc].normal3.x = norm2->x;
			
			Gruppe[groupIndex-1].triangle[tc].normal1.y = norm0->y;
			Gruppe[groupIndex-1].triangle[tc].normal2.y = norm1->y;
			Gruppe[groupIndex-1].triangle[tc].normal3.y = norm2->y;
			
			Gruppe[groupIndex-1].triangle[tc].normal1.z = norm0->z;
			Gruppe[groupIndex-1].triangle[tc].normal2.z = norm1->z;
			Gruppe[groupIndex-1].triangle[tc].normal3.z = norm2->z;
			
			Gruppe[groupIndex-1].triangle[tc].tCoord1.x = tcoordinate0->x;
			Gruppe[groupIndex-1].triangle[tc].tCoord2.x = tcoordinate1->x;
			Gruppe[groupIndex-1].triangle[tc].tCoord3.x = tcoordinate2->x;
			
			Gruppe[groupIndex-1].triangle[tc].tCoord1.y = tcoordinate0->y;
			Gruppe[groupIndex-1].triangle[tc].tCoord2.y = tcoordinate1->y;
			Gruppe[groupIndex-1].triangle[tc].tCoord3.y = tcoordinate2->y;
			
			tc++;													// increase the counter
		}
	}
	
	Gruppe[groupIndex - 1].size = tc;
	
	cout << tc << " triangles" << endl;
	
}
