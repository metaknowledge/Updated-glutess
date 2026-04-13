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
    std::vector<int> indices; // reference pointer for the indices.
    std::vector<float> verts = tessellate(&contours, &tris, NULL, &indices, false);
    
    printf("\ncontours:\n");
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

    printf("\n triangles:\n");
    for (int i = 0; i < indices.size(); i += 3) {
      printf("[%i, %i, %i]", indices[i], indices[i+1], indices[i+2]);
    }
    printf("\n");
  
    return 0;
}
