//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        ITransformable.h                          //
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

#ifndef __Lore_include_ITransformable_h__
#define __Lore_include_ITransformable_h__

//Lore
#include "Lore_Utils.h"
#include "Vector2.h"


NS_LORE_BEGIN

class ITransformable
{
    // Inner Types //
public:
    struct OriginHelpers
    {
        static const Vector2 TopLeft   (); //0, 0
        static const Vector2 MiddleLeft(); //0, 0.5
        static const Vector2 BottomLeft(); //0, 1

        static const Vector2 TopCenter   (); //0.5, 0
        static const Vector2 Center      (); //0.5, 0.5
        static const Vector2 BottomCenter(); //0.5, 1

        static const Vector2 TopRight   (); //1, 0
        static const Vector2 MiddleRight(); //1, 0.5
        static const Vector2 BottomRight(); //1, 1
    };


    // CTOR / DTOR //
public:
    ITransformable();
    virtual ~ITransformable();


    // Public Methods //
public:
    //Position
    void setPosition (const Vector2 &position);
    void setPosition (float x, float y);
    void setPositionX(float x);
    void setPositionY(float y);

    const Vector2& getPosition () const;
    float          getPositionX() const;
    float          getPositionY() const;


    //Rotation
    void setRotation(float angle);
    float getRotation() const;


    //Scale
    void setScale (const Vector2 &scale);
    void setScale (float x, float y);
    void setScaleX(float x);
    void setScaleY(float y);

    const Vector2& getScale () const;
    float          getScaleX() const;
    float          getScaleY() const;


    //Origin
    void setOrigin (const Vector2 &origin);
    void setOrigin (float x, float y);
    void setOriginX(float x);
    void setOriginY(float y);

    const Vector2& getOrigin()  const;
    float          getOriginX() const;
    float          getOriginY() const;


    // Transforms //
public:
    //Move
    void move(const Vector2 &displacement);
    void moveX(float x);
    void moveY(float y);

    //Rotate
    void rotate(float angle);

    //Scale
    void scale(const Vector2 factor);
    void scale(float scale);
    void scaleX(float x);
    void scaleY(float y);


    // iVars //
private:
    Vector2 m_position;
    float   m_rotation;
    Vector2 m_scale;
    Vector2 m_origin;
};

NS_LORE_END
#endif // __Lore_include_ITransformable_h__ //
