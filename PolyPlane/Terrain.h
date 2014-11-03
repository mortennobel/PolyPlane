//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"

#include <vector>

class Terrain : public kick::Component {
    std::vector<kick::Mesh*> plants;
public:
    Terrain(kick::GameObject *gameObject);
    void buildTerrain(glm::vec2 offset, kick::Mesh *mesh, glm::vec3 min, glm::vec3 max);

    void addPlant(kick::Transform *parent, glm::vec3 pos);

    void addCloud(glm::vec3 pos,glm::vec3 min, glm::vec3 max);
};



