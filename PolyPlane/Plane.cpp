//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Plane.h"
#include "NormalToNoise.h"
#include <iostream>

using namespace kick;
using namespace glm;
using namespace std;

ThePlane::ThePlane(kick::GameObject *gameObject) : Component(gameObject) {
    MeshRenderer* mr = gameObject->addComponent<MeshRenderer>();
    Material *material = new Material();
    material->setShader(Project::loadShader("shaders/diffuse_vertex_colored.shader"));
    mr->setMaterial(material);
    Mesh *mesh = new Mesh();
    mesh->setMeshData(AddNoise(loadPlyData("blender-models","plane.ply")));
    mr->setMesh(mesh);

    {
        auto propellerGO = Engine::activeScene()->createGameObject("Propeller");
        MeshRenderer* mr = propellerGO->addComponent<MeshRenderer>();
        Material *material = new Material();
        material->setShader(Project::loadShader("shaders/diffuse_vertex_colored.shader"));
        mr->setMaterial(material);
        Mesh *mesh = new Mesh();
        mesh->setMeshData(AddNoise(loadPlyData("blender-models","plane-propeller.ply")));
        mr->setMesh(mesh);
        propeller = propellerGO->transform();
        propeller->setParent(transform());
    }
    transform()->setPosition(vec3{0,20,0});


    if (particles.size() == 0){
        for (int i=0;i<50;i++){
            auto p = Engine::activeScene()->createGameObject("Particle");
            particles.push_back(p->addComponent<Exhaustion>());
        }
    }
}

void ThePlane::update() {

    static float exCount = 0;
    if (KeyInput::pressed(Key::SPACE)) {
        exCount += Time::delta();
    }
    if (exCount>0.25f){
        exCount = 0;
        currentParticle++;
        if (currentParticle >= particles.size()){
            currentParticle = 0;
        }
        particles[currentParticle]->spawn(transform()->position());
    }
    auto trans = transform();
    if (KeyInput::pressed(Key::SPACE)){
        float acc = 10;
        propellerSpeed += Time::delta()*acc;
        propellerSpeed = std::min(500.0f,propellerSpeed);
    } else {
        float deacc = 0.5f;
        propellerSpeed -= propellerSpeed*deacc*Time::delta();
        propellerSpeed = std::max(10.0f,propellerSpeed);
    }
    propellerRotation += propellerSpeed * Time::delta();

    float speedFactor = 0.5f;
    trans->setPosition(trans->position() + trans->forward()*propellerSpeed*speedFactor*Time::delta());

    float torqueAcc = 10;
    if (KeyInput::pressed(Key::LEFT)){
        torque.x += Time::delta()*torqueAcc;
    }
    if (KeyInput::pressed(Key::RIGHT)){
        torque.x -= Time::delta()*torqueAcc;
    }
    /*
    if (keyInput.pressed(Key::UP)){
        torque.y += Time::getDeltaTime()*torqueAcc;
    }
    if (keyInput.pressed(Key::DOWN)){
        torque.y -= Time::getDeltaTime()*torqueAcc;
    } */

    torque = glm::clamp(torque, vec2{-1.0f},vec2{1.0f});
    float deTorqueAcc = 5;
    torque -= torque*deTorqueAcc *Time::delta();

    rotation.x += torque.x * Time::delta();

    rotation.y += sin(rotation.x) * Time::delta();

    trans->setRotation(angleAxis(rotation.y, vec3{0,1,0}) * angleAxis(rotation.x, vec3{0,0,1}));

    propeller->setRotationEuler(vec3{0,0,propellerRotation });
}
