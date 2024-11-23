/*
Date: 23/11/2024

Music class manages the music in the application.
*/

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>

namespace System
{
        class Music
        {
        public: // Methods
        // Class methods
                Music();
                ~Music();
        // Music methods
                void playMusic();
                void stopMusic();
        private: // Methods
        // Music methods
                bool loadMusic();
        private: // Variables
        // Variables
                sf::Music music;                                        // Music to play
        };
}


#endif // !MUSIC_HPP