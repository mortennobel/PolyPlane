//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "CameraController.h"


void CameraController::update() {
    if (!target){
        return;
    }

    // Calculate the current rotation angles
    float wantedRotationAngle = target->rotationEuler().y;
    float wantedHeight = target->position().y + height;

    float currentRotationAngle = transform()->rotationEuler().y;
    float currentHeight = transform()->position().y;

    // Damp the rotation around the y-axis
    currentRotationAngle = kick::lerpAngle (currentRotationAngle, wantedRotationAngle, rotationDamping * kick::Time::delta());

    // Damp the height
    currentHeight = glm::mix(currentHeight, wantedHeight, heightDamping * kick::Time::delta());

    // Convert the angle into a rotation
    auto rot = glm::yawPitchRoll(0.0f, currentRotationAngle, 0.0f);

    auto currentRotation =  glm::quat_cast(rot);

    // Set the position of the camera on the x-z plane to:
    // distance meters behind the target
    auto position = target->position();
    position -= currentRotation * glm::vec3(0,0,-1) * distance;

    // Set the height of the camera
    position.y = currentHeight;
    transform()->setPosition(position);

    // Always look at the target
    transform()->lookAt(target);
}

kick::Transform *CameraController::getTarget() const {
    return target;
}

void CameraController::setTarget(kick::Transform *target) {
    CameraController::target = target;
}
