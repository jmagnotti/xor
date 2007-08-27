#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include "../../include/SDL_mixer.h"

namespace XOR {

/**
 *
 */
class AudioPlayer
{

public:
    
    static AudioPlayer * GetInstance();


    
    static AudioPlayer * GetInstance(const char * track);


    
    void loadTrack(const char * track);


    
    void pause();


    
    void play(const char * track);


    
    void play();


    
    void Shutdown();


    
    virtual ~AudioPlayer();


private:

    AudioPlayer();

	static AudioPlayer * _player;

	Mix_Music * _music;
};

}

#endif			// AUDIOPLAYER_H

