//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Sprite.h                                  //
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

#ifndef __Lore_include_Sprite_h__
#define __Lore_include_Sprite_h__

//std
#include <string>
//Lore
#include "Lore_Utils.h"
#include "IDrawable.h"
#include "ITransformable.h"
#include "Texture.h"


NS_LORE_BEGIN

class Sprite : public IDrawable, public ITransformable
{
    // Typedef //
public:
    typedef std::shared_ptr<Sprite> SPtr;

    // CTOR //
public:
    Sprite();
    Sprite(const std::string &filename,
        const Rectangle& srcRect = {});


    // Public Methods //
public:
    virtual void draw() override;

    //Flip
    void setFlip (Texture::Flip flip);
    void setFlipX(bool flip);
    void setFlipY(bool flip);

    Texture::Flip getFlip () const;
    bool          getFlipX() const;
    bool          getFlipY() const;

    //Color
    void setColor(const Color &color);
    const Color& getColor() const;

    //Texture
    Texture::SPtr getTexture() const;
    void setTexture(Texture::SPtr texture,
                    const Rectangle &srcRect = {});

    void loadTexture(const std::string &filename,
                     const Rectangle &srcRect = {});

    void setSourceRectangle(const Rectangle &srcRect = {});
    const Rectangle& getSourceRectangle() const;

    //Bounds
    Rectangle getBounds() const;


    // iVars //
private:
    //Texture Stuff.
    Texture::SPtr m_pTexture;
    Rectangle     m_textureRect;
    Texture::Flip m_flip;

    Color m_color;
};

NS_LORE_END
#endif // __Lore_include_Sprite_h__ //
