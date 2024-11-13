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
        @param type Type of the object.
        */
        Object::Object(const std::string& name, int x, int y,
                ObjectType type)
                : name(name), x(x), y(y), type(type),
                loaded(false)
        {
                LOG_TRACE("Object::Object() called.");
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
                : Object(name, x, y, ObjectType::SPRITE),
                path(path), texture(texture), xScale(xScale),
                yScale(yScale)
        {
                LOG_TRACE("Sprite::Sprite() called.");

                load();
        }

        /*
        Destructor for Sprite class.
        */
        Sprite::~Sprite()
        {
                LOG_TRACE("Sprite destroyed");
        }

        /*
        Load the sprite.

        @throw std::runtime_error if the texture failed to load.
        */
        void Sprite::load()
        {
                LOG_TRACE("Sprite::load() called.");

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
                LOG_TRACE("Sprite::render() called.");

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
                : Object(name, x, y, ObjectType::TEXT),
                path(path), font(font), text(text),
                fontSize(fontSize)
        {
                LOG_TRACE("Text::Text() called.");

                load();
        }

        /*
        Destructor for Font class.
        */
        Text::~Text()
        {
                LOG_TRACE("Text::~Text() called.");
        }

        /*
        Load the font.

        @throw std::runtime_error if the font failed to load.
        */
        void Text::load()
        {
                LOG_TRACE("Text::load() called.");

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
                LOG_TRACE("Text::render() called.");

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
        @param width Width of the object.
        @param height Height of the object.
        @param rectangle Rectangle to render.
        @param color Color of the rectangle.
        @param command Command to execute
        */
        Rectangle::Rectangle(const std::string& name, int x, int y,
                int width, int height, sf::RectangleShape rectangle,
                sf::Color color, std::shared_ptr<Command> command)
                : Object(name, x, y, ObjectType::RECTANGLE),
                width(width), height(height), rectangle(rectangle),
                color(color), command(command)
        {
                LOG_TRACE("Rectangle::Rectangle() called.");

                load();
        }

        /*
        Destructor for Rectangle class.
        */
        Rectangle::~Rectangle()
        {
                LOG_TRACE("Rectangle destroyed");
        }

        /*
        Load the rectangle.
        */
        void Rectangle::load()
        {
                LOG_TRACE("Rectangle::load() called.");

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
                LOG_TRACE("Rectangle::render() called.");

                if (loaded)
                {
                        window.draw(rectangle);
                }
        }
}