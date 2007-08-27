#include "AudioPlayer.h"
#include <iostream>

using namespace std;

namespace XOR {

AudioPlayer * AudioPlayer::_player = NULL;

AudioPlayer::AudioPlayer()
{
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,512);
}

AudioPlayer * AudioPlayer::GetInstance()
{
	if (_player == NULL)
		_player = new AudioPlayer();

	return _player;
}

AudioPlayer * AudioPlayer::GetInstance(const char * track)
{
	if (_player == NULL)
		_player = new AudioPlayer();

	_player->loadTrack(track);

	return _player;
}

void AudioPlayer::play()
{
	if (! Mix_PlayingMusic())
		Mix_PlayMusic(_music, 1);
	else if (Mix_PausedMusic())
		Mix_ResumeMusic();
}

void AudioPlayer::pause()
{
	Mix_PauseMusic();
}

void AudioPlayer::play(const char * track)
{
	loadTrack(track);
}

void AudioPlayer::loadTrack(const char * track)
{
	_music = Mix_LoadMUS(track);
}

void AudioPlayer::Shutdown()
{
	delete _player;
}

AudioPlayer::~AudioPlayer()
{
	Mix_CloseAudio();
}

}

