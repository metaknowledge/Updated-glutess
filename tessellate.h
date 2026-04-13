#pragma once
#include <vector>

extern std::vector<float> tessellate(std::vector<std::vector<float>> *contours_in, std::vector<float> *tris_out, 
                       std::vector<std::vector<float>> *edges, std::vector<int> *indexs, bool getBounds = false, float z = -0.9f);

