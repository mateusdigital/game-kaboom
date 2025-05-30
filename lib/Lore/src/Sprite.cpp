//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Sprite.cpp                                //
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
#include "../include/Sprite.h"
//Lore
#include "../include/AssetsManager.h"

//Usings
USING_NS_LORE

// CTOR //
Sprite::Sprite() :
    m_pTexture   (nullptr),
    m_flip       (Texture::Flip::None)
{
    //Empty...
}

Sprite::Sprite(const std::string &filename,
               const Rectangle &srcRect /* = Rectangle::Empty() */) :
    Sprite()
{
    loadTexture(filename, srcRect);
}


// Public Methods //
void Sprite::draw()
{
    if(!getIsVisible())
        return;

    m_pTexture->draw(m_textureRect,
                     getBounds  (),
                     getRotation(),
                     getOrigin  (),
                     m_flip,
                     m_color);
}

//Flip
void Sprite::setFlip(Texture::Flip flip)
{
    m_flip = flip;
}

void Sprite::setFlipX(bool flip)
{
    if(flip) m_flip |= Texture::Flip::X;
    else     m_flip &= Texture::Flip::Y;
}

void Sprite::setFlipY(bool flip)
{
    if(flip) m_flip |= Texture::Flip::Y;
    else     m_flip &= Texture::Flip::X;
}

Texture::Flip Sprite::getFlip() const
{
    return m_flip;
}

bool Sprite::getFlipX() const
{
    return (m_flip & Texture::Flip::X) == Texture::Flip::X;
}

bool Sprite::getFlipY() const
{
    return (m_flip & Texture::Flip::Y) == Texture::Flip::Y;
}


//Color
void Sprite::setColor(const Color &color)
{
    m_color = color;
}

const Color& Sprite::getColor() const
{
    return m_color;
}


//Texture
Texture::SPtr Sprite::getTexture() const
{
    return m_pTexture;
}

void Sprite::setTexture(Texture::SPtr texture,
                        const Rectangle &srcRect /* = Rectangle::Empty() */)
{
    m_pTexture = texture;
    setSourceRectangle(srcRect);
}

void Sprite::loadTexture(const std::string &filename,
                         const Rectangle &srcRect /* = Rectangle::Empty() */)
{
    setTexture(AssetsManager::instance()->getTexture(filename),
               srcRect);
}

void Sprite::setSourceRectangle(const Rectangle &srcRect /* = Rectangle::Empty() */)
{
    m_textureRect = srcRect;

    //Set to whole texture.
    if (m_textureRect.w == 0 && m_textureRect.h == 0) {
        auto size = m_pTexture->getTextureSize();
        m_textureRect.w = size.getX();
        m_textureRect.h = size.getY();
    }
}

const Rectangle& Sprite::getSourceRectangle() const
{
    return m_textureRect;
}

//Bounds
Rectangle Sprite::getBounds() const
{
    Rectangle r;
    auto p = getPosition();
    auto s = m_textureRect;
	
    r.x = p.x;
    r.y = p.y;
    r.w = s.w;
    r.h = s.h;

    return r;
}
