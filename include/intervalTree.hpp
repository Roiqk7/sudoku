/*
Date: 12/11/2024

Interval tree used to determine which object was clicked in the scene. (leafs are objects)
*/

#ifndef INTERVAL_TREE_HPP
#define INTERVAL_TREE_HPP

#include "command.hpp"
#include "object.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace Tool
{
        class IntervalTree
        {
        public: // Methods
                IntervalTree();
                ~IntervalTree();
        // Operations
                void insert(std::weak_ptr<System::Rectangle> object);
                void query(float x, float y,
                        std::weak_ptr<System::Command>& command);
        private: // Variables
                struct Node
                {
                public: // Variables
                        float startX;
                        float endX;
                        float startY;
                        float endY;
                        std::weak_ptr<System::Rectangle> object;        // Object in the scene (assumed to be sf::RectangleShape)
                public: // Methods
                        Node(float startX, float endX,
                                float startY, float endY,
                                std::weak_ptr<System::Rectangle> object);
                };
        };
}

#endif // !INTERVAL_TREE_HPP