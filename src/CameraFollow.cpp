//
//  CameraFollow.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 31/10/2018.
//

#include "CameraFollow.hpp"
#include "JunkDragonGame.hpp"

using namespace glm;

CameraFollow::CameraFollow(GameObject *gameObject)
: Component(gameObject)
{
    camera.setOrthographicProjection(JunkDragonGame::windowSize.y,-1,1);
}

sre::Camera &CameraFollow::getCamera() {
    return camera;
}

void CameraFollow::update(float deltaTime) {
    auto position = followObject->getPosition();
    
    position.x += offset.x;
    position.y += offset.y;
    
    gameObject->setPosition(position);
    
    vec3 eye (position, 0);
    vec3 at (position, -1);
    vec3 up (0, 1, 0);
    camera.lookAt(eye, at, up);
}


void CameraFollow::setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset) {
    this->followObject = followObject;
    this->offset = offset;
}
