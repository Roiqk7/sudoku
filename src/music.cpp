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
        Check if the music is playing.

        @note If the music is not playing, start playing it.
        */
        [[deprecated("If needed, place in the main loop. But I believe it is not necessary.")]]
        void Music::checkMusic()
        {
                LOG_TRACE("Music::checkMusic() called");

                if (music->getStatus() != sf::Music::Playing)
                {
                        playMusic();
                }
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