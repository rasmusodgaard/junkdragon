//
//  CameraFollow.cpp
//  SRE
//

#include "CameraFollow.hpp"
#include "JunkDragonGame.hpp"

using namespace glm;

CameraFollow::CameraFollow(GameObject *gameObject)
: Component(gameObject)
{
    camera.setOrthographicProjection(JunkDragonGame::windowSize.y,-1,1);
}

// Provide access to the camera object
sre::Camera &CameraFollow::getCamera() {
    return camera;
}

void CameraFollow::update(float deltaTime) {
    if(followObject != nullptr) {
        auto position = followObject->getPosition();

        // Apply offset
        position.x += offset.x;
        position.y += offset.y;
        
        gameObject->setPosition(position);
        
        // Set 2D Camera
        vec3 eye (position, 0);
        vec3 at (position, -1);
        vec3 up (0, 1, 0);
        camera.lookAt(eye, at, up);
    }
}

// The camera will position itself so followObject is at the center + offset vector
void CameraFollow::setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset) {
    this->followObject = followObject;
    this->offset = offset;
}

// Call to avoid following a nullptr
void CameraFollow::unsetFollowObject() {
    this->followObject  = nullptr;
    this->offset        = glm::vec2(0.0f,0.0f);
}
