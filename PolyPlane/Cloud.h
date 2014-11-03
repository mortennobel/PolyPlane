//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"

class Cloud : public kick::Component, public kick::Updatable {
    glm::vec3 max;
    glm::vec3 min;
public:
    Cloud(kick::GameObject *gameObject, glm::vec3 min, glm::vec3 max);

    virtual void update() override;
};



