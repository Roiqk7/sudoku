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
        void createDefaultScene(Scene& scene);
// Non-game scenes
        void createWelcomeScene(Scene& scene);
        void createMainMenuScene(Scene& scene);
        void createSettingsScene(Scene& scene);
        void createCreditsScene(Scene& scene);
// Game scenes
        void createNewGameScene(Scene& scene);
        void createGameScene(Scene& scene);
        void createPauseScene(Scene& scene);
        void createEndScene(Scene& scene);
// Development scenes
        void createDebugScene(Scene& scene);
        void createExecutionTimeScene(Scene& scene);
}

#endif // !SCENES_HPP