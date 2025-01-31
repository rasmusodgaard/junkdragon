#pragma once

#include "sre/Camera.hpp"
#include "glm/glm.hpp"
#include "Component.hpp"

class CameraFollow : public Component {
public:
    explicit CameraFollow(GameObject *gameObject);
    
    void update(float deltaTime) override;
    
    void setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset);
    void unsetFollowObject();
    sre::Camera& getCamera();
private:
    sre::Camera camera;
    std::shared_ptr<GameObject> followObject;
    glm::vec2 offset;
};
