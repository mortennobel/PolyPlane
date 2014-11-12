//
// Created by Morten Nobel-Jørgensen on 01/11/14.
// Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//


#pragma once

#include "kick/kick.h"

#include <vector>

class Terrain : public kick::Component {
    std::vector<kick::Mesh*> plants;
public:
    Terrain(kick::GameObject *gameObject);
    void buildTerrain(glm::vec2 offset, kick::Mesh *mesh, glm::vec3 min, glm::vec3 max);

    void addPlant(kick::Transform *parent, glm::vec3 pos);

    void addCloud(glm::vec3 pos,glm::vec3 min, glm::vec3 max);
};


/*
    /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ -arch x86_64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk -L/Users/morten/Programmering/cpp/PolyPlane/bin/debug -F/Users/morten/Programmering/cpp/PolyPlane/bin/debug -F/Users/morten/Programmering/cpp/PolyPlane/../kick/lib/debug -filelist /Users/morten/Programmering/cpp/PolyPlane/obj/Debug/polyplane.build/Objects-normal/x86_64/polyplane.LinkFileList -mmacosx-version-min=10.10 -F/Library/Frameworks/ -framework Cocoa -framework GLUT -framework OpenGL -framework SDL2 -framework SDL2_image -lkick -Xlinker -dependency_info -Xlinker /Users/morten/Programmering/cpp/PolyPlane/obj/Debug/polyplane.build/Objects-normal/x86_64/polyplane_dependency_info.dat -o /Users/morten/Programmering/cpp/PolyPlane/bin/debug/polyplane
* */

