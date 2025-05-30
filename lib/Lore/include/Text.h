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

#ifndef __Lore_include_Text_h__
#define __Lore_include_Text_h__

//std
#include <string>
//Lore
#include "Lore_Utils.h"
#include "Font.h"
#include "IDrawable.h"
#include "ITransformable.h"
#include "Texture.h"


NS_LORE_BEGIN

class Text : public IDrawable, public ITransformable
{
    // CTOR //
public:
    Text();
    Text(const std::string &filename, int size);


    // Public Methods //
public:
    //Draw
    virtual void draw() override;

    //String
    void setString(const std::string &str);
    void setString(const char *fmt, ...);
    const std::string& getString() const;

    //Color
    void setForegroundColor(const Color &color);
    const Color& getForegroundColor() const;

    void setBackgroundColor(const Color &color);
    const Color& getBackgroundColor() const;

    //Font
    void setFont(Font::SPtr font);
    void loadFont(const std::string &filename, int size);

    //Bounds
    Rectangle getBounds() const;

    // Private Methods //
private:
    void calculate();

    // iVars //
private:
    //String
    std::string m_string = {};
    //Font / Texture
    Font::SPtr    m_pFont = nullptr;
    std::unique_ptr<Texture> m_pCurrentTexture = nullptr;
    Rectangle     m_textureRect = {};
    //Flip
    Texture::Flip m_flip = Texture::Flip::None;
    //Colors
    Color m_fgColor = {};
    Color m_bgColor = {};
};

NS_LORE_END
#endif // __Lore_include_Text_h__ //
