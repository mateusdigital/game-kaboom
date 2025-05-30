//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Text.cpp                                  //
//            █ █        █ █        Lore                                      //
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
#include "../include/Text.h"
//std
#include <cstdarg>
//Lore
#include "../include/AssetsManager.h"
#include "./private/include/Lore_Private_Utils.h"
#include "./private/include/Log.h"
#include "../include/SDLHelpers.h"

//Usings
USING_NS_LORE


// CTOR //
Text::Text() :
    //String
    // m_string - Default initialized
    //Font / Texture
    m_pFont          (nullptr),
    m_pCurrentTexture(nullptr),
    //Flip
    m_flip(Texture::Flip::None)
{
    //Empty...
    m_fgColor.r = 255;
    m_fgColor.g = 255;
    m_fgColor.b = 255;
    m_fgColor.a = 255;
    m_bgColor.r = 255;
    m_bgColor.g = 255;
    m_bgColor.b = 255;
    m_bgColor.a = 0;
}

Text::Text(const std::string &filename, int size) :
    Text()
{
    loadFont(filename, size);
}


// Public Methods //
//Draw
void Text::draw()
{
    if(!getIsVisible() || !m_pCurrentTexture)
        return;


    m_pCurrentTexture->draw(m_textureRect,
                            getBounds  (),
                            getRotation(),
                            getOrigin  (),
                            m_flip,
                            m_fgColor);
}

//String
void Text::setString(const std::string &str)
{
    m_string = str;
    calculate();
}

void Text::setString(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    //Forward the '...' to vformat
    m_string = CoreGame::StringUtils::vformat(fmt, args);

    va_end(args);

    calculate();
}

const std::string& Text::getString() const
{
    return m_string;
}


//Color
void Text::setForegroundColor(const Color &color)
{
    m_fgColor = color;
    calculate();
}

const Color& Text::getForegroundColor() const
{
    return m_fgColor;
}


void Text::setBackgroundColor(const Color &color)
{
    m_bgColor = color;
    calculate();
}

const Color& Text::getBackgroundColor() const
{
    return m_bgColor;
}


//Font
void Text::setFont(Font::SPtr font)
{
    m_pFont = font;
    calculate();
}

void Text::loadFont(const std::string &filename, int size)
{
    setFont(AssetsManager::instance()->getFont(filename, size));
}

//Bounds
Rectangle Text::getBounds() const
{
    auto p = getPosition();
    auto s = m_textureRect;

    Rectangle r;
    r.x = p.getX();
    r.y = p.getY();
    r.w = s.w;
    r.h = s.h;

    return r;
}

// Private Methods //
void Text::calculate()
{
    //Nothing to draw...
    if(m_string.empty())
    {
        m_pCurrentTexture = nullptr;
        m_textureRect.w = 0;
        m_textureRect.h = 0;
    }
    else
    {
        m_pCurrentTexture = m_pFont->prepareTexture(m_string,
                                                    m_fgColor,
                                                    m_bgColor);

        auto s = m_pCurrentTexture->getTextureSize();
        m_textureRect.w = s.getX();
        m_textureRect.h = s.getY();
    }
}
