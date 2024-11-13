/*
Date: 11/11/2024

Object class stores the properties of an object in the scene.
*/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "command.hpp"
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>

namespace System
{
        enum class ObjectType
        {
                NONE = 0,
                SPRITE,
                TEXT,
                RECTANGLE
        };
// Object class
        class Object
        {
        public: // Methods
        // Class methods
                Object(const std::string& name, int x, int y,
                        ObjectType type);
                virtual ~Object() = default;
        // Object methods
                virtual void load() = 0;
                virtual void render(sf::RenderWindow& window) = 0;
        public: // Variables
        // Resource specific
                ObjectType type;                                       // Type of the object
        protected: // Variables
        // General
                std::string name;                                      // Name of the object
                bool loaded = false;                                   // If the object is loaded
        // Rendering
                int x;                                                  // X position of the object
                int y;                                                  // Y position of the object
                int width;                                              // Width of the object
                int height;                                             // Height of the object
        };
// Sprite class
        class Sprite : public Object
        {
        public: // Methods
        // Class methods
                Sprite(const std::string& name, int x, int y,
                        std::filesystem::path path, sf::Texture texture,
                        float xScale, float yScale);
                ~Sprite() override;
        // Object methods
                void load() override;
                void render(sf::RenderWindow& window) override;
        private: // Variables
                std::filesystem::path path;                             // Path to the resource
                sf::Texture texture;                                    // Texture of the sprite
                sf::Sprite sprite;                                      // Sprite to render
                float xScale;                                           // X scale of the sprite
                float yScale;                                           // Y scale of the sprite
        };
// Font class
        class Text : public Object
        {
        public: // Methods
        // Class methods
                Text(const std::string& name, int x, int y,
                        std::filesystem::path path, sf::Font font,
                        sf::Text text, int fontSize);
                ~Text() override;
        // Object methods
                void load() override;
                void render(sf::RenderWindow& window) override;
        private: // Variables
                std::filesystem::path path;                             // Path to the resource
                sf::Text text;                                          // Text to render
                sf::Font font;                                          // Font of the text
                int fontSize;                                           // Size of the font
        };
// Rectangle class
        class Rectangle : public Object
        {
        public: // Methods
        // Class methods
                Rectangle(const std::string& name, int x, int y,
                        int width, int height, sf::RectangleShape rectangle,
                        sf::Color color, std::shared_ptr<Command> command = nullptr);
                ~Rectangle() override;
        // Object methods
                void load() override;
                void render(sf::RenderWindow& window) override;
        private: // Variables
                int width;                                              // Width of the object
                int height;                                             // Height of the object
                sf::RectangleShape rectangle;                           // Rectangle to render
                sf::Color color;                                        // Color of the rectangle
                std::shared_ptr<Command> command;                       // Command to execute
        };
}

#endif // !OBJECT_HPP