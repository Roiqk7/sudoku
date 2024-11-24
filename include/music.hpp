/*
Date: 23/11/2024

Music class manages the music in the game.
*/

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <memory>
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
                std::unique_ptr<sf::Music> music;                       // Background music
        };
}


#endif // !MUSIC_HPP