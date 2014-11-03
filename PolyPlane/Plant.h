//
// Created by Morten Nobel-Jørgensen on 31/10/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"

enum class PlantType{
    Tree,
    PalmTree,
    PalmTree2,
    Plant,
};

class Plant : public kick::Component {
public:

    PlantType type = PlantType::Tree;

    Plant(kick::GameObject *gameObject, PlantType type = PlantType::Tree);

};



