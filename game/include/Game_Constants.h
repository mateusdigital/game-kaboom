//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Game_Constants.h                          //
//            █ █        █ █        Game_Kaboom                               //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
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

#ifndef __Game_Kaboom_include_Game_Constants_h__
#define __Game_Kaboom_include_Game_Constants_h__

////////////////////////////////////////////////////////////////////////////////
// Texts                                                                      //
////////////////////////////////////////////////////////////////////////////////
// Text //
constexpr auto kFontName         = "nokiafc22.ttf";
constexpr auto kFontName_Credits = "SourceCodePro-Regular.ttf";

//Splash Scene
constexpr int kFontSize_AmazingCowLogoText = 30;
//Menu Scene
constexpr int kFontSize_TitleText        = 60;
constexpr int kFontSize_PlayCreditsText  = 40;
constexpr int kFontSize_AmazingCowText   = 20;
//Game Scene
constexpr int kFontSize_StatusText   = 100;
constexpr int kFontSize_ScoreText    = 20;
constexpr int kFontSize_TurnText     = 20;
constexpr int kGameScene_TextOffset  = 20;
//Credits Scene
constexpr int kFontSize_CreditsMsg = 20;


////////////////////////////////////////////////////////////////////////////////
// Timers                                                                     //
////////////////////////////////////////////////////////////////////////////////
constexpr float kClockInterval_StatusText = 0.5; //Half a second.


////////////////////////////////////////////////////////////////////////////////
// Positions / Sizes                                                          //
////////////////////////////////////////////////////////////////////////////////
constexpr int kSize_SkyHeight = 150;
constexpr int kPos_Bomber     = kSize_SkyHeight;
constexpr int kPos_Player     = 400;


////////////////////////////////////////////////////////////////////////////////
// Score                                                                      //
////////////////////////////////////////////////////////////////////////////////
constexpr int kScoreMutilplier = 50;


////////////////////////////////////////////////////////////////////////////////
// Sounds                                                                     //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kSoundName_AmazingIntro = "amazing_intro.wav";

constexpr auto kSoundName_LevelStart = "level_start.wav";
constexpr auto kSoundName_Victory    = "victory.wav";
constexpr auto kSoundName_Defeat     = "defeat.wav";
constexpr auto kSoundName_GameOver   = "gameover.wav";

constexpr auto kSoundName_Dropping   = "bomb_dropping.wav";
constexpr auto kSoundName_ExplodeFmt = "bomb_explode%d.wav";
constexpr auto kSoundName_Caught     = "bomb_caught.wav";

constexpr int kSoundExplode_Count = 5;
constexpr auto kSoundName_ExplodeLast = "bomb_explode5.wav";

constexpr auto kSoundName_MenuSelect = "menu_select.wav";

////////////////////////////////////////////////////////////////////////////////
// String Formats                                                             //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kStringFormat_Score = "Score %06d";
constexpr auto kStringFormat_Level = "Level %03d";

#endif // __Game_Kaboom_include_Game_Constants_h__ //
