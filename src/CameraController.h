//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"

class CameraController : public kick::Component, public kick::Updatable {
    kick::Transform* target = nullptr;

public:
    float distance = 30.0;
// the height we want the camera to be above the target
    float height = 5.0;
// How much we
    float heightDamping = 2.0;
    float rotationDamping = 0.000003;

    CameraController(kick::GameObject *gameObject) : Component(gameObject) {
    }

    virtual void update() override;

    kick::Transform * getTarget() const;

    void setTarget(kick::Transform *target);
};



