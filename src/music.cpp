/*
Date: 23/11/2024

Music class manages the music in the application.
*/

#include "../include/macros.hpp"
#include "../include/music.hpp"
#include <memory>
#include <SFML/Audio.hpp>
#include <thread>

namespace System
{
// Class methods
        /*
        Constructor for Music class.

        @note Loads the music and starts playing it.
        */
        Music::Music()
        {
                LOG_TRACE("Music::Music() called");

                music = std::make_unique<sf::Music>();

                if (!loadMusic())
                {
                        LOG_ERROR("Failed to load music");
                }
                else
                {
                        music->setLoop(true);
                        music->setVolume(30);
                        playMusic();
                }
        }

        /*
        Destructor for Music class.
        */
        Music::~Music()
        {
                LOG_TRACE("Music::~Music() called");
        }
// Music methods
        /*
        Play the music.
        */
        void Music::playMusic()
        {
                LOG_TRACE("Music::playMusic() called");

                playMusicInThread();
        }

        /*
        Stop the music.
        */
        void Music::stopMusic()
        {
                LOG_TRACE("Music::stopMusic() called");

                music->stop();
        }

        /*
        Load the music.

        @return True if the music was loaded successfully, false otherwise.
        */
        bool Music::loadMusic()
        {
                LOG_TRACE("Music::loadMusic() called");

                return music->openFromFile("assets/music.mp3");
        }

        /*
        Play the music in a separate thread.
        */
        void Music::playMusicInThread()
        {
                LOG_TRACE("Music::playMusicInThread() called");

                // Create a thread to play music
                std::thread musicThread([this]()
                {
                        music->play();
                });

                // Detach the thread to allow it to run independently
                musicThread.detach();
        }
} // namespace System