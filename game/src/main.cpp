//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        main.cpp                                  //
//            █ █        █ █        Game_Kaboom                               //
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

//C
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#elif defined(__APPLE__) || defined(__linux__) || defined(__ANDROID__)
#include <unistd.h>
#endif
//std
#include <sstream>
#include <vector>
#include <string>
//Lore
#include "Lore.h"
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "SplashScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "CreditsScene.h"
#include "Version.h"

//Usings
USING_NS_GAMEKABOOM;


#define GAME_NAME    "Amazing Cow Labs - Kaboom!"
#define GAME_FULL_NAME GAME_NAME " - " GAME_VERSION

void checkAllAssetsFiles()
{
    std::vector<std::string> requiredFiles {
        //Icon
        "kaboom_icon.png",
        //Images
        "AmazingCow_Logo_Big.png",
        "AmazingCow_Logo_Small.png",
        "amazing_intro.wav",
        "Bomb_Alive.png",
        "Bomber.png",
        "Paddle.png",
        //Sounds
        "bomb_caught.wav",
        "bomb_dropping.wav",
        "bomb_explode1.wav",
        "bomb_explode2.wav",
        "bomb_explode3.wav",
        "bomb_explode4.wav",
        "bomb_explode5.wav",
        "Bomb_Exploded.png",
        "defeat.wav",
        "gameover.wav",
        "level_start.wav",
        "menu_select.wav",
        "victory.wav",
        //Fonts
        "nokiafc22.ttf",
        "SourceCodePro-Regular.ttf"
    };

    auto missingFiles = Lore::AssetsManager::instance()->checkFilesExists(
        requiredFiles
    );

    if(missingFiles.size() != 0)
    {
        std::stringstream msg_sstream;

        msg_sstream << "Sorry, missing assets files!" << std::endl;
        msg_sstream << "Please install the game."     << std::endl;
        msg_sstream << "For help send a email to:"    << std::endl;
        msg_sstream << "help@amazingcow.com with ";
        msg_sstream << "[kaboom] as subject!"         << std::endl;

        Lore::SDLHelpers::MessageBox_Error(
            GAME_FULL_NAME,
            msg_sstream.str()
        );

        exit(1);
    }
}

#if WIN32
int SDL_main(int argc, char* argv[])
#else
int main()
#endif
{
    Lore::ErrorControl::DieMode = Lore::ErrorControl::LORE_ERROR_DIE_ON_ALL_ERRORS;

    auto winMgr    = Lore::WindowManager::instance();
    auto assetsMgr = Lore::AssetsManager::instance();
    auto gameMgr   = Lore::GameManager::instance  ();
    auto inputMgr  = Lore::InputManager::instance ();
    auto soundMgr  = Lore::SoundManager::instance ();

    winMgr->initialize(
        GAME_FULL_NAME,
        800, 600,
        800, 600,
        0, 0
    );


    //Init the AssetsManager and check if all
    //required assets are present.
    char current_path[2048];
    getcwd(current_path, sizeof(current_path));

    auto search_path = std::string(current_path) + "/assets/";

    assetsMgr->initialize(search_path);
    checkAllAssetsFiles();

    //Set the Window Icon.
    winMgr->setIcon("kaboom_icon.png");

    inputMgr->initialize();

    soundMgr->initialize(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        2048
    );

    gameMgr->initialize(
        CoreRandom::Random::kRandomSeed,
        60
    );

    gameMgr->run(std::unique_ptr<Lore::Scene>(new SplashScene()));


    gameMgr->shutdown();
    winMgr->shutdown ();

    return 0;
}
