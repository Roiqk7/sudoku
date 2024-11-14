/*
Date: 11/11/2024

Scene class stores one scene of the application and all the objects in it.
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "command.hpp"
#include "object.hpp"
#include <memory>
#include <string>
#include <vector>

namespace System
{
        class Scene
        {
        public: // Methods
        // Class methods
                Scene(const std::string& name);
                ~Scene();
        // Scene methods
                void render(sf::RenderWindow& window);
                void addObject(const std::shared_ptr<Object>& object);
                void addClickableObject(std::unique_ptr<Rectangle> object);
                void retrieveClickedCommand(int x, int y,
                        std::weak_ptr<Command>& command);
        private: // Methods
                bool checkClicked(const std::unique_ptr<Rectangle>&
                        object, int x, int y);
        public: // Variables
                std::string name;                                       // Name of the scene (unique)
        private: // Variables
                std::vector<std::shared_ptr<Object>> objects;           // Objects in the scene
                std::vector<std::unique_ptr<Rectangle>>
                        clickableObjects;                               // Clickable objects in the scene
        };
}


#endif // !SCENE_HPP