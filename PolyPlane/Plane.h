//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"
#include "Exhaustion.h"
#include <vector>

class Plane : public kick::Component, public kick::Updatable {
    kick::Transform* propeller;
    float propellerSpeed = 0;
    float propellerRotation = 0;
    float speed = 0;
    glm::vec2 torque = glm::vec2 {0};
    glm::vec2 rotation = glm::vec2 {0};
    std::vector<Exhaustion*> particles;
    int currentParticle = 0;
public:
    Plane(kick::GameObject *gameObject);

    virtual void update();
};



