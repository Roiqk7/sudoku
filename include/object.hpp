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
                SPRITE,
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

        class Sprite : public Object
        {
        public: // Methods
        // Class methods
                Sprite(int x, int y, int width, int height,
                        std::filesystem::path path, sf::Texture texture,
                        int xScale, int yScale);
                ~Sprite() override;
        // Object methods
                void load() override;
                void render(sf::RenderWindow& window) override;
        private: // Variables
                sf::Texture texture;                                    // Texture of the sprite
                sf::Sprite sprite;                                      // Sprite to render
                int xScale;                                             // X scale of the sprite
                int yScale;                                             // Y scale of the sprite
        };

        class Font : public Object
        {
        public: // Methods
        // Class methods
                Font(int x, int y, int width, int height,
                        std::filesystem::path path, sf::Font font,
                        sf::Text text, int fontSize);
                ~Font() override;
        // Object methods
                void load() override;
                void render(sf::RenderWindow& window) override;
        private: // Variables
                sf::Font font;                                          // Font of the text
                sf::Text text;                                          // Text to render
                int fontSize;                                           // Size of the font
        };

        class Rectangle : public Object
        {
        public: // Methods
        // Class methods
                Rectangle(int x, int y, int width, int height,
                        std::filesystem::path path, sf::RectangleShape rectangle,
                        sf::Color color);
                ~Rectangle() override;
        // Object methods
                void load() override;
                void render(sf::RenderWindow& window) override;
        private: // Variables
                sf::RectangleShape rectangle;                           // Rectangle to render
                sf::Color color;                                        // Color of the rectangle
        };
}

#endif // !OBJECT_HPP