/*
Date: 11/11/2024

Scene class stores one scene of the application and all the objects in it.
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "command.hpp"
#include "object.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace System
{
        class Scene
        {
        public: // Methods
        // Class methods
                explicit Scene(const std::string& name);
                ~Scene();
                Scene(const Scene&) = delete;
                Scene& operator=(const Scene&) = delete;
                Scene(Scene&& other) noexcept;
                Scene& operator=(Scene&& other) noexcept;
        // Scene methods
                void render(sf::RenderWindow& window) const noexcept;
                size_t size() const noexcept;
        // Object methods
                void addObject(const std::shared_ptr<Object>& object);
                void addClickableObject(std::shared_ptr<Rectangle> object);
                void retrieveClickedCommand(int x, int y,
                        std::weak_ptr<Command>& command);
                void clear() noexcept;
        private: // Methods
        // Checker
                bool checkClicked(const std::shared_ptr<Rectangle>&
                        object, int x, int y);
        public: // Variables
                std::string name;                                       // Name of the scene (unique)
        private: // Variables
                std::vector<std::shared_ptr<Object>> objects;           // Objects in the scene
                std::vector<std::shared_ptr<Rectangle>>
                        clickableObjects;                               // Clickable objects in the scene
        };
}


#endif // !SCENE_HPP