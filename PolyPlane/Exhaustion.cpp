//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Exhaustion.h"

#include <iostream>

using namespace glm;
using namespace kick;

Exhaustion::Exhaustion(kick::GameObject *gameObject) : Component(gameObject) {
    MeshRenderer* mr = gameObject->addComponent<MeshRenderer>();
    Material *material = new Material();
    material->setShader(Project::loadShader("shaders/unlit_vertex_colored.shader"));
    mr->setMaterial(material);
    Mesh *mesh = new Mesh();

    mesh->setMeshData(loadPlyData("blender-models","cloud.ply"));
    mr->setMesh(mesh);
}

void Exhaustion::update() {
    float scaleSpeed = 0.05f;
    float scale = 1-std::min((Time::total() - particleTime)*scaleSpeed, 0.9999f);

    scale *= 0.5f;

    transform()->setLocalScale(vec3{scale});
}

void Exhaustion::spawn(glm::vec3 pos) {
    transform()->setPosition(pos);
    particleTime = Time::total();
}
