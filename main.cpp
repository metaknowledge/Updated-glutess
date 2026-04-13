#include "tessellate.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cstdint>

std::vector<float> createContour(std::string vals) {
    std::vector<float> fvals;
    std::istringstream ss(vals); 
    float f;
    while (ss >> f) fvals.push_back(f);
    return fvals;
}

struct pt {
  float x;
  float y;
} pt;

int main()
{
  //Create 3x contours including one that intersects the other ...
	
    std::vector<std::vector<float>> contours;
    contours.push_back(createContour("0 0 300 0 300 300 0 300"));
    contours.push_back(createContour("100 100 200 100 420 420 100 200"));
    contours.push_back(createContour("400 100 450 150 400 200 350 150"));
  
  //Tessellate the contours into triangles and store the results in 'tris' array ...
	
    std::vector<float> tris;  /* store triangles in tris array - each triangle is 9 floats (3x XYZ) */
    std::vector<int> indexs;
    std::vector<float> verts = tessellate(&contours, &tris, NULL, &indexs, false);
  
    // std::vector<std::vector<float>> edges;
    // tessellate(&contours, NULL, &edges, NULL, true);	//Get outer edges with corrected windings etc..
	
    printf("\ncontours:\n");

  
    // uint32_t vc = tris.size() / 3;
    // std::vector<short> lindexes;
    // for (size_t i = 0; i < tris.size(); i++) lindexes.push_back(i);
    std::vector<struct pt> pts;
    for (auto vec : contours) {
      for (int i = 0; i < vec.size(); i += 2) {
        struct pt point;
        point.x = vec[i];
        point.y = vec[i+1];
        pts.push_back(point);
        printf("(%0.2f, %0.2f)", point.x, point.y);
      }
      printf("\n");
    }
    printf("\n trinagles:\n");
    for (int i = 0; i < indexs.size(); i += 3) {
      printf("[%i, %i, %i]", indexs[i], indexs[i+1], indexs[i+2]);
    }
    printf("\n");
  
  // Here's a basic means of rendering the triangles and their outlines ...
  
/*  if (vc > 1) {
	glColor4ub(255, 255, 255, 255);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &tris.front());
	glDrawElements(GL_TRIANGLES, vc, GL_UNSIGNED_SHORT, &lindexes.front());		//Draw triangles
	glColor4ub(0, 255, 0, 255);
	glDrawElements(GL_LINES, vc, GL_UNSIGNED_SHORT, &lindexes.front());		//Draw triangle outlines
    }  */
    
    return 0;
}
