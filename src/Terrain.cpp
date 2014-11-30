//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#include "Terrain.h"
#include "glm/gtc/noise.hpp"
#include "glm/gtc/random.hpp"
#include "NormalToNoise.h"
#include "Cloud.h"
#include <vector>

using namespace glm;
using namespace kick;
using namespace std;

float worldScale = 4;

vec3 createVertex(vec2 pos2d){
//    vec3 pos{pos2d.x, simplex<float>(pos*3.0f), pos2d.y};
    vec3 pos{pos2d.x, sin(pos2d.x/10)*20, pos2d.y};
    return pos;
}

vec4 createColor(vec3 pos, bool randomize){
    float height = (float)round(pos.y*2);
    bool isDeepSea = height <= -4;
    bool isDeepSea2 = height <= -3;
    bool isSea = height <= -2;
    bool isSea2 = height <= -1;
    bool isSand = height <= 0;
    bool isSand2 = height <= 1;
    bool isStone = height <= 2;
    bool isStone2 = height <= 3;
    bool isGrass = height <= 4;
    bool isGrass2 = height <= 5;

    vec4 deepSea {.2f, .42f, .49f, 1};
    vec4 sea{.3f,.66f,.62f,1};
    vec4 sand{.96f, .95f, .49f, 1};
    vec4 stone{.81f,.57f,.33f,1};
    vec4 grass{.65f,.86f,.49f,1};
    vec4 grassDark{.65f*0.8f,.86f*0.8f,.49f*0.8f,1};
    vec4 color{1};
    if (isDeepSea) {
        color = deepSea;
    } else if (isDeepSea2){
        color = (deepSea+sea)*0.5f;
    }
    else if (isSea){
        color = sea;
    }
    else if (isSea2){
        color = (sea+sand)*0.5f;
    }
    else if (isSand) {
        color = sand;
    }
    else if (isSand2) {
        color = (sand+stone)*0.5f;
    }
    else if (isStone){
        color = stone;
    }
    else if (isStone2){
        color = (grass+stone)*0.5f;
    }
    else if (isGrass){
        color = grass;
    }
    else if (isGrass2){
        color = (grass+grassDark)*0.5f;
    }
    else {
        color = grassDark;
    }
    if (randomize){
        color = color * linearRand (0.95f,1.05f);
        color = clamp(color, vec4(0),vec4(1));
        color.w = 1;
    }
    return color;
}

MeshData* colorTerrain(MeshData* meshData){
    auto& indices = meshData->submeshIndices(0);

    const vector<vec3>& pos = meshData->position();
    vector<vec3> newPos;

    vector<vec4> colors(pos.size());
    float min = 999;
    float max = -999;
    for (int i=0;i<indices.size();i=i+3){
        int i1 = indices[i];
        int i2 = indices[i+1];
        int i3 = indices[i+2];

        vec3 avgPos = (pos[i1]+pos[i2]+pos[i3])*(1/3.0f);
        min = std::min(avgPos.y, min );
        max = std::max(avgPos.y, max );
        vec4 color = createColor(avgPos, false);
        colors[i1] = color;
        colors[i2] = color;
        colors[i3] = color;
    }
    meshData->setColor(colors);
    for (auto p:pos){
        p.y*=3;
        newPos.push_back(p);
    }
    meshData->setPosition(newPos);
    return meshData;
}

void Terrain::addPlant(Transform *parent, vec3 pos){
    static int plantCounter = 0;
    plantCounter++;
    Mesh* plantMesh = plants[plantCounter % plants.size()];
    auto gameObject = Engine::activeScene()->createGameObject("Terrain");
    MeshRenderer* meshRenderer = gameObject->addComponent<MeshRenderer>();
    meshRenderer->setMesh(plantMesh);
    Material *material = new Material();
    material->setShader(Project::loadShader("poly-assets/shaders/diffuse_vertex_colored.shader"));
    meshRenderer->setMaterial(material);

    vec3 finalPos = (vec3)(parent->globalMatrix()*vec4(pos,1.0f));
    gameObject->transform()->setLocalPosition(finalPos);
    gameObject->transform()->setLocalScale(vec3(1)*linearRand(0.5f,1.5f));
    gameObject->transform()->setLocalRotationEuler(vec3(0,(float)linearRand(-M_PI,M_PI),0));
}

void Terrain::addCloud(vec3 pos, vec3 min, vec3 max){
    static MeshData* cloudMesh = loadPlyData("poly-assets/models","cloud.ply");
    static Mesh *mesh = new Mesh();
    mesh->setMeshData(cloudMesh);

    auto gameObject = Engine::activeScene()->createGameObject("Cloud");
    gameObject->addComponent<Cloud>(min, max);
    MeshRenderer* meshRenderer = gameObject->addComponent<MeshRenderer>();
    meshRenderer->setMesh(mesh);
    Material *material = new Material();
    material->setShader(Project::loadShader("poly-assets/shaders/unlit_vertex_colored.shader"));
    meshRenderer->setMaterial(material);


    gameObject->transform()->setLocalPosition(pos);
    gameObject->transform()->setLocalScale(vec3(1)*linearRand(0.5f,5.0f));
    gameObject->transform()->setLocalRotationEuler(vec3(0,(float)linearRand(-M_PI,M_PI),0));
}

void Terrain::buildTerrain(vec2 offset, Mesh *mesh, MeshData* meshData, vec3 min, vec3 max){
    auto gameObject = Engine::activeScene()->createGameObject("Terrain");
    MeshRenderer* meshRenderer = gameObject->addComponent<MeshRenderer>();
    meshRenderer->setMesh(mesh);
    Material *material = new Material();
    material->setShader(Project::loadShader("poly-assets/shaders/unlit_vertex_colored.shader"));
    meshRenderer->setMaterial(material);

    gameObject->transform()->setPosition(vec3{offset.x*200*worldScale, 0, offset.y*200*worldScale});
    gameObject->transform()->setLocalScale(vec3{worldScale, 1, worldScale});
    gameObject->transform()->setLocalRotationEuler(vec3{0,M_PI*(offset.x+offset.y),0});

    auto& indices = meshData->submeshIndices(0);
    auto& pos = meshData->position();
    for (int i=0;i<190;i++){
        // find random triangle
        int index = (int)linearRand(0.0f, indices.size()/3-1.0f)*3;

        vec3 p1 = pos[index];
        vec3 p2 = pos[index+1];
        vec3 p3 = pos[index+2];
        if (p1.y <-0.1){
            continue;
        }
        bool horizontal =glm::abs(p1.y- p2.y)+glm::abs(p2.y-p3.y)<0.1f;
        if (horizontal){
            vec3 midpoint = (p1+p2+p3)*(1/3.0f);
            addPlant (gameObject->transform(), midpoint);
        }
    }

    for (int i=0;i<20;i++){
        float x= linearRand((-100.0f),(100.0f));
        float z= linearRand((-100.0f),(100.0f));
        vec3 cloudPos = vec3(x,0,z) * worldScale + gameObject->transform()->position();
        cloudPos.y = linearRand(20.0f,50.0f);

        addCloud(cloudPos, min, max);
    }
}

Terrain::Terrain(kick::GameObject *gameObject)
: Component(gameObject)
{
    for (int i=0;i<4;i++) {
        Mesh *mesh = new Mesh();

        string name;
        switch (i){
            case 0:
                name = "palmtree";
                break;
            case 1:
                name = "palmtree2";
                break;
            case 2:
                name = "plant";
                break;
            case 3:
                name = "tree";
                break;

        }
        mesh->setMeshData(AddNoise(loadPlyData("poly-assets/models",name+".ply")));
        plants.push_back(mesh);
    }


    Mesh *mesh = new Mesh();
    MeshData* meshData = colorTerrain(loadPlyData("poly-assets/models","terrain.ply"));
    mesh->setMeshData(meshData);

    vec3 min {200*-2.5f*worldScale};
    vec3 max {200*2.5f*worldScale};
    for (int x=-2;x<=2;x++){
        for (int y=-2;y<=2;y++) {
            buildTerrain(vec2{x,y}, mesh, meshData, min, max);
        }
    }
}


