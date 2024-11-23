/*
Date: 15/11/2024

This file contains pre-made scenes for the GUI.

Note: All scenes are expected to be cleared before creating a new one.
*/

#ifndef SCENES_HPP
#define SCENES_HPP

#include "object.hpp"
#include "gui.hpp"
#include "scene.hpp"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace System
{
// System scenes
        void createDefaultScene(Scene& scene, sf::RenderWindow& window);
        void createBackgroundScene(Scene& scene, sf::RenderWindow& window);
// Non-game scenes
        void createWelcomeScene(Scene& scene, GUI& gui);
        void createMainMenuScene(Scene& scene, GUI& gui);
        void createCreditsScene(Scene& scene, GUI& gui);
        void createHelpScene(Scene& scene, GUI& gui);
// Game scenes 
        void createNewGameScene(Scene& scene, GUI& gui);
        void createGameScene(Scene& scene, GUI& gui);
        void createPauseScene(Scene& scene, GUI& gui);
        void createEndScene(Scene& scene, GUI& gui);
// Development scenes
        void createExecutionTimeScene(Scene& scene, GUI& gui,
                const std::chrono::microseconds& time);
}

#endif // !SCENES_HPP