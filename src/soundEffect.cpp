/*
Date: 24/11/2024

Sound effect class manages the sound effects in the application.
*/

#include "macros.hpp"
#include "soundEffect.hpp"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <SFML/Audio.hpp>
#include <string>

namespace System
{
        // Class methods
        /*
        Constructor for SoundEffect class.
        */
        SoundEffect::SoundEffect()
        {
                LOG_TRACE("SoundEffect::SoundEffect() called");
        }

        /*
        Destructor for SoundEffect class.
        */
        SoundEffect::~SoundEffect()
        {
                LOG_TRACE("SoundEffect::~SoundEffect() called");
        }
// Sound effect methods
        /*
        Play a sound effect.

        @param sound The sound effect to play.

        @note Expects the sound to be is assets/ and with .mp3 (which should not be included in the parameter).
        */
        void SoundEffect::playSound(const std::string& soundStr)
        {
                LOG_TRACE("SoundEffect::playSound() called");

                if (loadSoundEffect(soundStr))
                {
                        auto sound = std::make_shared<sf::Sound>();
                        sound->setBuffer(*sounds[soundStr]);
                        sound->play();
                        activeSounds.push_back(sound);
                }

                // Once in a while, remove inactive sounds
                if (activeSounds.size() > 10)
                {
                        removeInactiveSounds();
                }
        }

        /*
        Load a sound effect.

        @param sound The sound effect to load.

        @return True if the sound effect was loaded, false otherwise.
        */
        bool SoundEffect::loadSoundEffect(const std::string& soundStr)
        {
                LOG_TRACE("SoundEffect::loadSoundEffect() called");

                if (sounds.find(soundStr) == sounds.end())
                {
                        std::shared_ptr<sf::SoundBuffer> sound
                                = std::make_shared<sf::SoundBuffer>();
                        std::string path = "assets/" + soundStr + ".mp3";
                        if (sound->loadFromFile(path))
                        {
                                sounds[soundStr] = sound;
                                return true;
                        }
                        else
                        {
                                LOG_ERROR("Failed to load sound effect: {}", path);
                                return false;
                        }
                }

                return true;
        }

        /*
        Remove inactive sounds.
        */
        void SoundEffect::removeInactiveSounds()
        {
                LOG_TRACE("SoundEffect::removeInactiveSounds() called");

                activeSounds.remove_if([](const std::shared_ptr<sf::Sound>& sound)
                {
                        return sound->getStatus() == sf::Sound::Stopped;
                });
        }
} // namespace System