//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SoundManager.h                            //
//            █ █        █ █        Lore                                      //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016, 2017                  //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __Lore_include_SoundManager_h__
#define __Lore_include_SoundManager_h__

//std
#include <map>
#include <string>
//Lore
#include "Lore_Utils.h"


NS_LORE_BEGIN

class SoundManager
{
    // Inner Types //
private:
    struct EffectInfo
    {
        Mix_Chunk *chunk;
        int        playChannel;
    };


    // Constants / Enums / Typedefs //
public:
    //Loops
    static const int kPlayForever;
    static const int kPlayOneTime;

    //Default Stuff.
    static const int kDefaultFrequency;
    static const int kDefaultFormat;
    static const int kDefaultChannels;
    static const int kDefaultChunkSize;

private:
    typedef std::map<std::string, EffectInfo> EffectMap;
    typedef std::map<std::string, Mix_Music*> MusicMap;


    // Singleton //
public:
    COREGAME_SINGLETON_OF(SoundManager);
    COREGAME_DISALLOW_COPY_MOVE_ASSIGNS(SoundManager);
private:
    SoundManager() =default;


    // Init / Shutdown //
public:
    void initialize(int    frequency = kDefaultFrequency,
                    Uint16 format    = kDefaultFormat,
                    int    channels  = kDefaultChannels,
                    int    chunksize = kDefaultChunkSize);

    void shutdown();


    // Volume Methods //
public:
    //Master
    void setMasterVolume(float vol);
    void toggleMute();
    bool isMuted() const;

    //Effect
    void  setEffectsVolume(float vol);
    float getEffectsVolume() const;

    //Music
    void  setMusicVolume(float vol);
    float getMusicVolume() const;


    // Player Methods //
public:
    //Effect
    void playEffect(const std::string &name, int loopTimes = kPlayOneTime);
    void stopEffect(const std::string &name);
    void stopAllEffects();

    //Music
    void playMusic(const std::string &name, int loopTimes = kPlayForever);
    void stopMusic();


    // Load / Unload Methods //
public:
    //Load
    void loadEffect(const std::string &name);
    void loadMusic(const std::string &name);

    //Unload
    void unloadEffect(const std::string &name);
    void unloadMusic(const std::string &name);

    //Query
    bool isEffectLoaded(const std::string &name);
    bool isMusicLoaded(const std::string &name);


    // Private Methods //
private:
    EffectInfo& getEffectInfo(const std::string &name);


    // iVars //
private:
    std::string m_searchPath;

    EffectMap m_effectsMap;
    MusicMap  m_musicsMap;

    bool m_muted;
};

NS_LORE_END
#endif // __Lore_include_SoundManager_h__ //
