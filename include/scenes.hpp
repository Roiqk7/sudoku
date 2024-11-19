/*
Date: 15/11/2024

This file contains pre-made scenes for the GUI.

Note: All scenes are expected to be cleared before creating a new one.
*/

#ifndef SCENES_HPP
#define SCENES_HPP

#include "object.hpp"
#include "scene.hpp"

namespace System
{
// System scenes
        void createDefaultScene(Scene& scene, const sf::RenderWindow& window);
        void createBackgroundScene(Scene& scene, const sf::RenderWindow& window);
// Non-game scenes
        void createWelcomeScene(Scene& scene, const sf::RenderWindow& window);
        void createMainMenuScene(Scene& scene, const sf::RenderWindow& window);
        void createSettingsScene(Scene& scene, const sf::RenderWindow& window);
        void createCreditsScene(Scene& scene, const sf::RenderWindow& window);
// Game scenes
        void createNewGameScene(Scene& scene, const sf::RenderWindow& window);
        void createGameScene(Scene& scene, const sf::RenderWindow& window);
        void createPauseScene(Scene& scene, const sf::RenderWindow& window);
        void createEndScene(Scene& scene, const sf::RenderWindow& window);
// Development scenes
        void createDebugScene(Scene& scene, const sf::RenderWindow& window);
        void createExecutionTimeScene(Scene& scene, const sf::RenderWindow& window);
}

#endif // !SCENES_HPP