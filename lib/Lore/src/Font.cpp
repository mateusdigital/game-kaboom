//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Font.cpp                                  //
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
#include "../include/Font.h"
//Lore
#include "../include/SDLHelpers.h"
//Lore_Private
#include "./private/include/Lore_Private_Utils.h"

//Usings
USING_NS_LORE;


// CTOR //
Font::Font(TTF_Font *font) :
    m_pTTF_Font(font)
{
    //Empty...
}

Font::~Font()
{
    COREGAME_ASSERT(
        m_pTTF_Font != nullptr,
        "Font::~Font - Trying to delete a nullptr font"
    );

    TTF_CloseFont(m_pTTF_Font);
    m_pTTF_Font = nullptr;
}


// Public Methods //
Texture::UPtr Font::prepareTexture(const std::string &str,
                                   const Color &fgColor,
                                   const Color &bgColor)
{

    //COWTODO: We need learn more about TTF_Font and \
    //how to use it correctly
    PVT_LORE_UNUSED(bgColor);

    COREGAME_ASSERT(
        !str.empty(),
        "Font::prepareTexture - Cannot prepare texture for empty strings..."
    );

    auto tmp_surface = TTF_RenderText_Blended(m_pTTF_Font,
                                             str.c_str(),
                                             fgColor);

    //COWTODO: In future add options to set other blend modes.
    SDL_SetSurfaceBlendMode(tmp_surface, SDL_BLENDMODE_BLEND);

    auto sdl_texture = SDLHelpers::make_texture_free(tmp_surface);
    SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);

    return std::unique_ptr<Texture>(new Texture(sdl_texture));
}
