//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Texture.h                                 //
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

#ifndef __Lore_include_Texture_h__
#define __Lore_include_Texture_h__

//std
#include <string>
//Lore
#include "Lore_Utils.h"
#include "Vector2.h"


NS_LORE_BEGIN

class Texture
{
    // Enums / Constants // Typedefs //
public:
    typedef std::shared_ptr<Texture> SPtr;
    typedef std::unique_ptr<Texture> UPtr;

    enum class Flip {
        None = 0,
        X    = 1,
        Y    = 2,
        Both = 3
    };


    // CTOR / DTOR //
public:
    Texture(SDL_Texture *texture);
    ~Texture();

    COREGAME_DISALLOW_COPY_MOVE_ASSIGNS(Texture);


    // Public Methods //
public:
    void draw(Rectangle srcRect,
              Rectangle dstRect,
              float angle,
              const Vector2 &origin,
              Flip  flip,
              const Color &color);

    const Vector2& getTextureSize() const;


    // iVars //
private:
    SDL_Texture *m_pSDL_Texture;
    Vector2      m_size;
};


// Operators for Texture::Flip //
std::ostream& operator <<(std::ostream &os, Texture::Flip flip);

Texture::Flip operator | (Texture::Flip lhs, Texture::Flip rhs);
Texture::Flip operator & (Texture::Flip lhs, Texture::Flip rhs);
Texture::Flip operator ^ (Texture::Flip lhs, Texture::Flip rhs);

Texture::Flip& operator |=(Texture::Flip &lhs, Texture::Flip rhs);
Texture::Flip& operator &=(Texture::Flip &lhs, Texture::Flip rhs);
Texture::Flip& operator ^=(Texture::Flip &lhs, Texture::Flip rhs);

NS_LORE_END
#endif // __Lore_include_Texture_h__ //
