//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"

class Exhaustion : public kick::Component, public kick::Updatable{

public:
    float particleTime = -999;

    Exhaustion(kick::GameObject *gameObject);

    virtual void update() override;

    void spawn(glm::vec3 pos);
};



