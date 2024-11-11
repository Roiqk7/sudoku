/*
Date: 11/11/2024

Object class stores the properties of an object in the scene.
*/

#include "../include/macros.hpp"
#include "../include/object.hpp"
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

namespace System
{
        /*
        Constructor for Object class.

        @param x X position of the object.
        @param y Y position of the object.
        @param width Width of the object.
        @param height Height of the object.
        @param path Path to the resource.
        @param type Type of the object.
        */
        Object::Object(int x, int y, int width, int height,
                std::filesystem::path path, ObjectType type)
                : x(x), y(y), width(width), height(height), path(path), type(type),
                loaded(false)
        {
        }
}