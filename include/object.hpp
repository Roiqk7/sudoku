/*
Date: 11/11/2024

Object class stores the properties of an object in the scene.
*/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace System
{
        enum class ObjectType
        {
                NONE = 0,
                TEXTURE,
                FONT,
                RECTANGLE
        };

        class Object
        {
        public: // Methods
        // Class methods
                Object(int x, int y, int width, int height,
                        std::filesystem::path path, ObjectType type);
                virtual ~Object() = default;
        // Object methods
                virtual void load() = 0;
                virtual void render(sf::RenderWindow& window) = 0;
        public: // Variables
        // Resource specific
                ObjectType type;                                        // Type of the object
        protected: // Variables
        // General
                bool loaded;                                            // If the object is loaded
                int x;                                                  // X position of the object
                int y;                                                  // Y position of the object
                int width;                                              // Width of the object
                int height;                                             // Height of the object
                std::filesystem::path path;                             // Path to the resource
        };
}

#endif // !OBJECT_HPP