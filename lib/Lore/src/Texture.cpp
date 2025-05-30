//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Texture.cpp                               //
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
#include "../include/Texture.h"
//Lore
#include "../include/SDLHelpers.h"
#include "../include/WindowManager.h"
#include "../include/AssetsManager.h"

//Usings
USING_NS_LORE

// Operators for Texture::Flip //
NS_LORE_BEGIN
Texture::Flip operator | (Texture::Flip lhs, Texture::Flip rhs)
{
    return static_cast<Texture::Flip>(
            static_cast<int>(lhs) | static_cast<int>(rhs)
           );
}

Texture::Flip operator & (Texture::Flip lhs, Texture::Flip rhs)
{
    return static_cast<Texture::Flip>(
            static_cast<int>(lhs) & static_cast<int>(rhs)
           );
}

Texture::Flip operator ^ (Texture::Flip lhs, Texture::Flip rhs)
{
    return static_cast<Texture::Flip>(
            static_cast<int>(lhs) ^ static_cast<int>(rhs)
           );
}


Texture::Flip& operator |=(Texture::Flip &lhs, Texture::Flip rhs)
{
    lhs = static_cast<Texture::Flip>(
            static_cast<int>(lhs) | static_cast<int>(rhs)
          );

    return lhs;
}

Texture::Flip& operator &=(Texture::Flip &lhs, Texture::Flip rhs)
{
    lhs = static_cast<Texture::Flip>(
            static_cast<int>(lhs) & static_cast<int>(rhs)
          );

    return lhs;
}

Texture::Flip& operator ^=(Texture::Flip &lhs, Texture::Flip rhs)
{
    lhs = static_cast<Texture::Flip>(
            static_cast<int>(lhs) ^ static_cast<int>(rhs)
          );

    return lhs;
}
NS_LORE_END


// CTOR / DTOR //
Texture::Texture(SDL_Texture *texture) :
    m_pSDL_Texture(texture),
    m_size        (Vector2::Zero())
{
    //Initialized with nullptr texture
    //There is no need to get the size...
    if(!m_pSDL_Texture)
        return;

    int w, h;
    SDL_QueryTexture(m_pSDL_Texture, nullptr, nullptr, &w, &h);

    m_size.x = w;
    m_size.y = h;
}

Texture::~Texture()
{
    COREGAME_ASSERT(
        m_pSDL_Texture != nullptr,
        "Texture::~Texture - Trying to delete a nullptr texture"
    );

    SDL_DestroyTexture(m_pSDL_Texture);
    m_pSDL_Texture = nullptr;
}

// Public Methods //
void Texture::draw(Rectangle srcRect,
                   Rectangle dstRect,
                   float angle,
                   const Vector2 &origin,
                   Flip  flip,
                   const Color &color)
{
    //Turn the Lore types to SDL types...
    //Origin is in range of [0, 1].
	SDL_Point sdl_origin;
	sdl_origin.x = static_cast<int>(origin.getX() * srcRect.w);
	sdl_origin.y = static_cast<int>(origin.getY() * srcRect.h);


    COREGAME_ASSERT_ARGS(
        ((flip == Texture::Flip::None) ||
         (flip == Texture::Flip::X   ) ||
         (flip == Texture::Flip::Y   ) ||
         (flip == Texture::Flip::Both)),
        "Texture::draw - Texture::Flip is invalid %d",
        static_cast<int>(flip)
    );

    auto sdl_flip = static_cast<SDL_RendererFlip>(flip);

    //Offset the position.a
    dstRect.x -= sdl_origin.x;
    dstRect.y -= sdl_origin.y;

    //Set the tint color.
    SDL_SetTextureColorMod(m_pSDL_Texture, color.r, color.g, color.b);

    auto renderer = WindowManager::instance()->getRenderer();
    SDL_RenderCopyEx(
        renderer,
        m_pSDL_Texture,
        &srcRect,
        &dstRect,
        angle,
        &sdl_origin,
        sdl_flip
    );
}

const Vector2& Texture::getTextureSize() const
{
    return m_size;
}
