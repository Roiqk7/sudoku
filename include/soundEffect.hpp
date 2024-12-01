/*
Date: 24/11/2024

Sound effect class manages the sound effects in the application.
*/

#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

#include <list>
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
                void playSound(const std::string& soundStr);
        private: // Methods
        // Sound effect methods
                bool loadSoundEffect(const std::string& soundStr);
                void removeInactiveSounds();
        private: // Variables
        // Variables
                std::unordered_map<std::string,
                        std::shared_ptr<sf::SoundBuffer>> sounds;               // Sound name to sound mapping
                std::list<std::shared_ptr<sf::Sound>> activeSounds;             // Active sounds
        };
}

#endif // !SOUND_EFFECT_HPP