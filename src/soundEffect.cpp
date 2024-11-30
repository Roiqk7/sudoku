/*
Date: 24/11/2024

Sound effect class manages the sound effects in the application.
*/

#include "../include/macros.hpp"
#include "../include/soundEffect.hpp"
#include <filesystem>
#include <memory>
#include <SFML/Audio.hpp>
#include <string>
#include <thread>

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
        void SoundEffect::playSound(const std::string& sound)
        {
                LOG_TRACE("SoundEffect::playSound() called");

                if (loadSoundEffect(sound))
                {
                        playSoundEffectInThread(sound);
                }
        }

        /*
        Load a sound effect.

        @param sound The sound effect to load.

        @return True if the sound effect was loaded, false otherwise.
        */
        bool SoundEffect::loadSoundEffect(const std::string& sound)
        {
                LOG_TRACE("SoundEffect::loadSoundEffect() called");

                if (sounds.find(sound) == sounds.end())
                {
                        std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
                        std::string path = "assets/" + sound + ".mp3";
                        if (music->openFromFile(path))
                        {
                                sounds[sound] = music;
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
        Play a sound effect in a separate thread.
        */
        void SoundEffect::playSoundEffectInThread(const std::string& sound)
        {
                LOG_TRACE("SoundEffect::playSoundEffectInThread() called");

                // Create a thread to play the sound effect
                std::thread soundThread([this, sound]()
                {
                        sounds[sound]->play();
                });

                // Detach the thread
                soundThread.detach();
        }
} // namespace System