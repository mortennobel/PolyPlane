//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Plant.h"
#include "NormalToNoise.h"

using namespace kick;
using namespace std;

Plant::Plant(kick::GameObject *gameObject, PlantType type) : Component(gameObject), type(type) {
    MeshRenderer* mr = gameObject->addComponent<MeshRenderer>();
    Material *material = new Material();
    material->setShader(Project::loadShader("poly-assets/shaders/diffuse_vertex_colored.shader"));
    mr->setMaterial(material);
    Mesh *mesh = new Mesh();

    string name;
    switch (type){
        case PlantType::PalmTree:
            name = "palmtree";
            break;
        case PlantType::PalmTree2:
            name = "palmtree2";
            break;
        case PlantType::Plant:
            name = "plant";
            break;
        case PlantType::Tree:
            name = "tree";
            break;

    }
    mesh->setMeshData(AddNoise(loadPlyData("poly-assets/models",name+".ply")));
    mr->setMesh(mesh);
}