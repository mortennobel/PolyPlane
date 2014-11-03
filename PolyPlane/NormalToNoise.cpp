//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#include "NormalToNoise.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/noise.hpp"

using namespace glm;
using namespace std;

kick::MeshData *AddNoise(kick::MeshData* meshData){
    vector<vec4> newColors;
    for (int i=0;i<meshData->normal().size();i++){
        vec3 norm = meshData->normal()[i];
        vec4 color = meshData->color()[i] + vec4(vec3(simplex<float>(norm*123.0f)),0.0f)*0.2f;
        newColors.push_back(color);
    }
    meshData->setColor(newColors);
    return meshData;
}