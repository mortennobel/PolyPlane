//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Cloud.h"

using namespace glm;
using namespace kick;

Cloud::Cloud(kick::GameObject *gameObject, glm::vec3 min, glm::vec3 max)
        : Component(gameObject), min(min), max(max) {

}

void Cloud::update() {
    vec3 velocity{11.1,0,22.22};
    vec3 pos = velocity*Time::delta() + transform()->position();
    for (int i=0;i<3;i=i+2){
        if (pos[i] > max[i]){
            pos[i] = min[i];
        }
    }
    transform()->setPosition(pos);
}

