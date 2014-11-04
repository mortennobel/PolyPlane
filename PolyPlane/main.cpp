//
//  main.cpp
//  PoetryEd
//
//  Created by Morten Nobel-Jørgensen on 29/10/14.
//  Copyright (c) 2014 Morten Nobel-Jørgensen. All rights reserved.
//

#include <iostream>

#include "kick/kick.h"
#include "Plant.h"
#include "Plane.h"
#include "Terrain.h"
#include "CameraController.h"

using namespace kick;

int main(int argc, char * argv[])
{
    WindowConfig config = WindowConfig::plain;
    config.width = 1280;
    config.height = 800;
    Engine::init(argc, argv/*, config*/);
    auto scene = Engine::activeScene();
    auto camera = scene->createPerspectiveCamera();

    camera->setClearColor({0.5f,0.5f,0.5f,1.0f});
    camera->gameObject()->transform()->setLocalPosition({0,10,30});
    camera->setFar(5000);
    scene->createDirectionalLight();
    scene->createAmbientLight(0.5f, glm::vec3(1));

    ThePlane* plane = scene->createGameObject("Plane")->addComponent<ThePlane>();
    scene->createGameObject("Plane")->addComponent<Terrain>();
    Plant* plant = scene->createGameObject("Plant")->addComponent<Plant>(PlantType::Plant);

    plant->transform()->setPosition(glm::vec3{0,0,-50});
    CameraController *cameraController = camera->gameObject()->addComponent<CameraController>();
    cameraController->setTarget(plane->transform());

    auto skybox = camera->gameObject()->addComponent<Skybox>();
    Material *mat = new Material();
    mat->setShader(Project::loadShader("shaders/skybox.shader"));
    mat->setUniform("mainTexture", Project::loadTexture2D("shaders/skybox.png"));
    skybox->setMaterial(mat);
    Engine::startMainLoop();

    return 0;
}
