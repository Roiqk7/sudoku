/*
Date: 24/11/2024

Sound effect class manages the sound effects in the application.
*/

#include "../include/macros.hpp"
#include "../include/soundEffect.hpp"
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
                        activeSounds.push_back(sounds[soundStr]);
                        activeSounds.back()->play();
                }

                removeFinishedSounds();
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
                        std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
                        std::string path = "assets/" + soundStr + ".mp3";
                        if (music->openFromFile(path))
                        {
                                sounds[soundStr] = music;
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
        Remove finished sounds.
        */
        void SoundEffect::removeFinishedSounds()
        {
                LOG_TRACE("SoundEffect::removeFinishedSounds() called");

                activeSounds.remove_if([](const std::shared_ptr<sf::Music>& music)
                {
                        return music->getStatus() == sf::Music::Stopped;
                });
        }
} // namespace System