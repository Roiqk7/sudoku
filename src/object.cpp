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
// Object class
        /*
        Constructor for Object class.

        @param name Name of the object.
        @param x X position of the object.
        @param y Y position of the object.
        @param path Path to the resource.
        @param type Type of the object.
        */
        Object::Object(const std::string& name, int x, int y,
                std::filesystem::path path, ObjectType type)
                : name(name), x(x), y(y), path(path), type(type),
                loaded(false)
        {
        }
// Sprite class
        /*
        Constructor for Sprite class.

        @param name Name of the object.
        @param x X position of the object.
        @param y Y position of the object.
        @param path Path to the resource.
        @param texture Texture of the sprite.
        @param xScale X scale of the sprite.
        @param yScale Y scale of the sprite.
        */
        Sprite::Sprite(const std::string& name, int x, int y,
                std::filesystem::path path, sf::Texture texture,
                float xScale, float yScale)
                : Object(name, x, y, path, ObjectType::SPRITE),
                texture(texture), xScale(xScale), yScale(yScale)
        {
                load();
        }

        /*
        Destructor for Sprite class.
        */
        Sprite::~Sprite()
        {
        }

        /*
        Load the sprite.

        @throw std::runtime_error if the texture failed to load.
        */
        void Sprite::load()
        {
                if (!texture.loadFromFile(path))
                {
                        throw std::runtime_error("Failed to load texture: " +
                                path.string());
                }
                sprite.setTexture(texture);
                sprite.setPosition(sf::Vector2f(x, y));
                sprite.setScale(sf::Vector2f(xScale, yScale));
                loaded = true;
        }

        /*
        Render the sprite.

        @param window Window to render to.
        */
        void Sprite::render(sf::RenderWindow& window)
        {
                if (loaded)
                {
                        window.draw(sprite);
                }
        }
// Font class
        /*
        Constructor for Font class.

        @param name Name of the object.
        @param x X position of the object.
        @param y Y position of the object.
        @param path Path to the resource.
        @param font Font of the object.
        */
        Text::Text(const std::string& name, int x, int y,
                std::filesystem::path path, sf::Font font,
                sf::Text text, int fontSize)
                : Object(name, x, y, path, ObjectType::TEXT),
                font(font), text(text), fontSize(fontSize)
        {
                load();
        }

        /*
        Destructor for Font class.
        */
        Text::~Text()
        {
        }

        /*
        Load the font.

        @throw std::runtime_error if the font failed to load.
        */
        void Text::load()
        {
                if (!font.loadFromFile(path))
                {
                        throw std::runtime_error("Failed to load font: " +
                                path.string());
                }
                text.setFont(font);
                text.setCharacterSize(fontSize);
                text.setFillColor(sf::Color::White);
                text.setPosition(sf::Vector2f(x, y));
                loaded = true;
        }

        /*
        Render the font.

        @param window Window to render to.
        */
        void Text::render(sf::RenderWindow& window)
        {
                if (loaded)
                {
                        window.draw(text);
                }
        }
// Rectangle class
        /*
        Constructor for Rectangle class.

        @param name Name of the object.
        @param x X position of the object.
        @param y Y position of the object.
        @param path Path to the resource.
        @param width Width of the object.
        @param height Height of the object.
        @param rectangle Rectangle to render.
        @param color Color of the rectangle.
        */
        Rectangle::Rectangle(const std::string& name, int x, int y,
                std::filesystem::path path, int width, int height,
                sf::RectangleShape rectangle, sf::Color color)
                : Object(name, x, y, path, ObjectType::RECTANGLE),
                width(width), height(height), rectangle(rectangle),
                color(color)
        {
                load();
        }

        /*
        Destructor for Rectangle class.
        */
        Rectangle::~Rectangle()
        {
        }

        /*
        Load the rectangle.
        */
        void Rectangle::load()
        {
                rectangle.setSize(sf::Vector2f(width, height));
                rectangle.setPosition(sf::Vector2f(x, y));
                rectangle.setFillColor(color);
                loaded = true;
        }

        /*
        Render the rectangle.

        @param window Window to render to.
        */
        void Rectangle::render(sf::RenderWindow& window)
        {
                if (loaded)
                {
                        window.draw(rectangle);
                }
        }
}