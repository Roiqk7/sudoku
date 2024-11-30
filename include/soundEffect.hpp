/*
Date: 24/11/2024

Sound effect class manages the sound effects in the application.
*/

#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

#include <memory>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

namespace System
{
        class SoundEffect
        {
        public: // Methods
        // Class methods
                SoundEffect();
                ~SoundEffect();
        // Sound effect methods
                void playSound(const std::string& sound);
        private: // Methods
        // Sound effect methods
                bool loadSoundEffect(const std::string& sound);
                void playSoundEffectInThread();
        private: // Variables
        // Variables
                std::unordered_map<std::string,
                        std::shared_ptr<sf::Music>> sounds;             // Sound name to sound mapping
        };
}

#endif // !SOUND_EFFECT_HPP