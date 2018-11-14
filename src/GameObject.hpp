// Includes
#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "sre/SpriteBatch.hpp"
#pragma once

// Forward declaration
class Component;

class GameObject {
    public:

        ~GameObject();

        template <class T>
        std::shared_ptr<T> addComponent();

        template <class T>
        std::shared_ptr<T> getComponent();

        bool removeComponent(std::shared_ptr<Component> component);

        void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
        void update(float deltaTime);

        const glm::vec2 &getPosition() const;

        void setPosition(const glm::vec2 &position);

        float getRotation() const;

        void setRotation(float rotation);

        void setDeleteMe(bool i_deleteMe);

        bool getDeleteMe();

        const std::vector<std::shared_ptr<Component>>& getComponents();

        std::string name = "_";
    private:
        GameObject() = default;
        std::vector<std::shared_ptr<Component>> components;

        glm::vec2 position;
        float rotation;

        bool deleteMe = false;

        friend class JunkDragonGame;
};

template <class T>
inline std::shared_ptr<T> GameObject::addComponent(){
    auto obj = std::shared_ptr<T>(new T(this));
    components.push_back(obj);

    return obj;
}

template <class T>
inline std::shared_ptr<T> GameObject::getComponent(){
    for (auto c : components){
        std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(c);
        if (res != nullptr) {
            return res;
        }
    }
    return std::shared_ptr<T>();
}
