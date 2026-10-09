//
//  Sound helpers for iGraphics, built on miniaudio (miniaudio.h).
//  Works on Windows and Linux. Several sounds can play at the same time.
//
//  Usage:
//      int music = iLoadSound("music/bg.wav", true);   // true = loop
//      iResumeSound(music);    // start, or continue from where it was paused
//      iPauseSound(music);
//      iPlaySound(effect);     // play from the beginning
//

#include "miniaudio.h"

#define I_MAX_SOUNDS 16

ma_engine iSoundEngine;
ma_sound iSounds[I_MAX_SOUNDS];
int iSoundCount = 0;
int iSoundEngineReady = 0;

// Loads a sound file and returns its id, or -1 if it couldn't be loaded.
// Looping sounds are streamed from disk, so long music files load instantly.
int iLoadSound(const char *filename, bool loop = false)
{
    if(!iSoundEngineReady){
        if(ma_engine_init(NULL, &iSoundEngine) != MA_SUCCESS){
            printf("Error: could not start the audio device.\n");
            return -1;
        }
        iSoundEngineReady = 1;
    }

    if(iSoundCount >= I_MAX_SOUNDS){printf("Error: Maximum number of sounds already loaded.\n");return -1;}

    ma_uint32 flags = loop ? MA_SOUND_FLAG_STREAM : MA_SOUND_FLAG_DECODE;
    if(ma_sound_init_from_file(&iSoundEngine, filename, flags, NULL, NULL, &iSounds[iSoundCount]) != MA_SUCCESS){
        printf("Error: could not load sound \"%s\".\n", filename);
        return -1;
    }
    ma_sound_set_looping(&iSounds[iSoundCount], loop);

    return iSoundCount++;
}

// Plays a sound from the beginning, restarting it if it is already playing.
void iPlaySound(int id)
{
    if(id < 0 || id >= iSoundCount) return;
    ma_sound_seek_to_pcm_frame(&iSounds[id], 0);
    ma_sound_start(&iSounds[id]);
}

// Starts a sound if it isn't already playing, continuing from where it was paused.
void iResumeSound(int id)
{
    if(id < 0 || id >= iSoundCount) return;
    if(!ma_sound_is_playing(&iSounds[id])) ma_sound_start(&iSounds[id]);
}

void iPauseSound(int id)
{
    if(id < 0 || id >= iSoundCount) return;
    if(ma_sound_is_playing(&iSounds[id])) ma_sound_stop(&iSounds[id]);
}
