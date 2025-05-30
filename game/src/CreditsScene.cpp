//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        CreditsScene.cpp                          //
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

//Header
#include "CreditsScene.h"
//Game
#include "MenuScene.h"
#include "Game_Constants.h"


//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
CreditsScene::CreditsScene()
{
    Color c;
    c.r = 255;
    c.g = 255;
    c.b = 255;
    c.a = 255;

    Lore::WindowManager::instance()->setClearColor(c);
    initStuff();
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void CreditsScene::update(float /* dt */)
{
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_RETURN) ||
       inputMgr->isKeyClick(SDL_SCANCODE_SPACE ) ||
       inputMgr->isKeyClick(SDL_SCANCODE_ESCAPE))
    {
        auto gameMgr = Lore::GameManager::instance();
        gameMgr->changeScene(std::unique_ptr<Lore::Scene>(new MenuScene()));
    }
}

void CreditsScene::draw()
{
    m_logo.draw();

    for(auto &text : m_textsVec)
        text.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void CreditsScene::initStuff()
{
    auto win_rect = Lore::WindowManager::instance()->getWindowRect();
    auto gm = Lore::GameManager::instance();

    //Sprite
    m_logo.loadTexture("AmazingCow_Logo_Small.png");
    m_logo.setPosition(win_rect.w * 0.5, 20);
    m_logo.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());

    Color c = {};
    c.r = gm->getRandomNumber(0, 255);
    c.g = gm->getRandomNumber(0, 255);
    c.b = gm->getRandomNumber(0, 255);
    c.a = 255;
    m_logo.setColor(c);


    //Message
    std::vector<std::string> msg {
        "This remake was made with <3 by Amazing Cow Labs.",
        "We hope that you enjoy this little game (!)"
        "",
        "We have other projects at:",
        "www.amazingcow.com",
        "Take a look :)",
        "",
        "This game is entirely FREE SOFTWARE",
        "This means that you're welcome to",
        "SHARE and HACK IT (!!!)",
        "",
        "You can find the sources at:",
        "opensource.amazingcow.com",
        "",
        "Dev / Graphics / Sound by N2OMatt",
        "","",
        "THANKS FOR PLAYING..."
        "", "",
        "Instituto Ayrton Senna helps poor children in Brazil",
        "get better life opportunities by improving their education.",
        "Why you don't look and help their work? <3",
        "www.InstitutoAyrtonSenna.org.br"
    };

    float startOffset = 140;
    float lineOffset  =  20;

    for(int i = 0; i < (int)msg.size(); ++i)
    {
        m_textsVec.push_back(
            Lore::Text(kFontName_Credits, kFontSize_CreditsMsg)
        );

        auto &text = m_textsVec.back();

        text.setString(msg[i]);
        text.setPosition(win_rect.w * 0.5, startOffset + (i * lineOffset));
        text.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
        Color c;
        c.r = 0;
        c.g = 0;
        c.b = 0;
        c.a = 255;
        text.setForegroundColor(c);
    }
}
