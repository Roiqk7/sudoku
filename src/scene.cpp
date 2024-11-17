/*
Date: 14/11/2024

Scene class stores one scene of the application and all the objects in it.
*/

#include "../include/macros.hpp"
#include "../include/object.hpp"
#include "../include/scene.hpp"
#include <memory>
#include <string>
#include <vector>

namespace System
{
// Class methods
        /*
        Construct the Scene object.

        @param name Name of the scene.
        */
        Scene::Scene(const std::string& name)
                : name(name)
        {
                LOG_TRACE("Scene::Scene() called.");
        }

        /*
        Destruct the Scene object.
        */
        Scene::~Scene()
        {
                LOG_TRACE("Scene::~Scene() called.");
        }

        /*
        Move construct the Scene object.

        @param other Scene to move.
        */
        Scene::Scene(Scene&& other) noexcept
                : name(std::move(other.name)),
                objects(std::move(other.objects)),
                clickableObjects(std::move(other.clickableObjects)),
                updateFunction(std::move(other.updateFunction))
        {
                LOG_TRACE("Scene::Scene() called.");
        }

        /*
        Move assign the Scene object.

        @param other Scene to move.
        */
        Scene& Scene::operator=(Scene&& other) noexcept
        {
                LOG_TRACE("Scene::operator=() called.");

                if (this != &other)
                {
                        name = std::move(other.name);
                        objects = std::move(other.objects);
                        clickableObjects = std::move(other.clickableObjects);
                        updateFunction = std::move(other.updateFunction);
                }

                return *this;
        }
// Scene methods
        /*
        Render the scene.

        @param window Window to render to.
        */
        void Scene::render(sf::RenderWindow& window) const noexcept
        {
                LOG_TRACE("Scene::render() called.");

                for (const auto& object : objects)
                {
                        if (object)
                        {
                                object->render(window);
                        }
                }
        }

        /*
        Update the scene.
        */
        void Scene::update() noexcept
        {
                LOG_TRACE("Scene::update() called.");

                if (updateFunction)
                {
                        updateFunction(*this);
                }
        }

        /*
        Retrieve the size of the scene.

        @return Size of the scene.
        */
        size_t Scene::size() const noexcept
        {
                LOG_TRACE("Scene::size() called.");

                return objects.size();
        }

        /*
        Set the update function of the scene.

        @param function Function to set.
        */
        void Scene::setUpdateFunction(std::function<void(Scene&)> function)
        {
                LOG_TRACE("Scene::setUpdateFunction() called.");

                updateFunction = function;
        }
// Object methods
        /*
        Add an object to the scene.

        @param object Object to add.

        @note Add clickable objects first.
        */
        void Scene::addObject(const std::shared_ptr<Object>& object)
        {
                LOG_TRACE("Scene::addObject() called.");

                if (!object)
                {
                        return;
                }

                objects.push_back(object);
        }

        /*
        Add a clickable object to the scene.

        @param object Clickable object to add.
        */
        void Scene::addClickableObject(std::unique_ptr<Rectangle> object)
        {
                LOG_TRACE("Scene::addClickableObject() called.");

                if (!object)
                {
                        return;
                }

                objects.push_back(std::move(object));
                clickableObjects.push_back(std::move(object));
        }

        /*
        Retrieve the command of the object that was clicked.

        @param x X position of the click.
        @param y Y position of the click.
        @param command Command to retrieve.

        @note If no object was clicked, command is nullptr.
        */
        void Scene::retrieveClickedCommand(int x, int y,
                std::weak_ptr<Command>& command)
        {
                LOG_TRACE("Scene::retrieveClickedCommand() called.");

                // Note: This approach is greedy, returns the first suitable object
                for (const auto& object : clickableObjects)
                {
                        if (checkClicked(object, x, y))
                        {
                                command = object->command;
                                return;
                        }
                }

                // No object was clicked
                command.reset();
        }

        /*
        Clear the scene.
        */
        void Scene::clear() noexcept
        {
                LOG_TRACE("Scene::clear() called.");

                name.clear();
                objects.clear();
                clickableObjects.clear();
        }

        /*
        Check if the object was clicked.

        @param object Object to check.
        @param x X position of the click.
        @param y Y position of the click.

        @return True if the object was clicked, false otherwise.
        */
        bool Scene::checkClicked(const std::unique_ptr<Rectangle>& object,
                int x, int y)
        {
                LOG_TRACE("Scene::checkClicked() called.");

                return object->x <= x && x <= (object->x + object->width)
                        && object->y <= y && y <= (object->y + object->height);
        }

} // namespace System