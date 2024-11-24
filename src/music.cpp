/*
Date: 23/11/2024

Music class manages the music in the application.
*/

#include "../include/macros.hpp"
#include "../include/music.hpp"
#include <SFML/Audio.hpp>

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

                music->play();
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
} // namespace System