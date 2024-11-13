/*
Date: 11/11/2024

Scene class stores one scene of the application and all the objects in it.
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "intervalTree.hpp"
#include "object.hpp"
#include <memory>
#include <string>
#include <vector>

namespace System
{
        class Scene
        {
        public: // Methods

        public: // Variables
                std::string name;                                       // Name of the scene (unique)
        private: // Variables
                std::vector<std::shared_ptr<Object>> objects;           // Objects in the scene
                Tool::IntervalTree intervalTree;                        // Stored all the objects in the scene
        };
}


#endif // !SCENE_HPP