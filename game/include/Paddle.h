//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Paddle.h                                  //
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

#ifndef __Game_Kaboom_include_Paddle_h__
#define __Game_Kaboom_include_Paddle_h__

//Game_Kaboom
#include "GameKaboom_Utils.h"

NS_GAMEKABOOM_BEGIN

class Paddle : public Lore::IDrawable, public Lore::IUpdatable
{
    // Inner Types //
private:
    struct AnimationInfo
    {
        Lore::Sprite                 sprite;
        std::vector<Rectangle> frames;
        int                          frameIndex;
        CoreClock::Clock             timer;

        void start();

        void update(float dt);
        void draw(const Lore::Vector2 &pos, int yOffset);

        void resetFrame();
        void increaseFrame();
        void changeFrame(int index);
    };

    // Enums / Constants / Typdefs //
public:

    // CTOR / DTOR //
public:
    Paddle();
    virtual ~Paddle();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Setters //
public:
    void setInitialPosition(int x, int y);
    void setMovementBounds (int min, int max);


    // Getters //
public:
    const Lore::Vector2& getPosition() const;
    int getLives() const;


    // Actions //
public:
    void kill();
    bool checkCollision(const Rectangle &rect);


    // Private Methods //
private:
    //Init
    void initSprites();

    //Input
    void handleInput();


    // iVars //
private:
    //HouseKeeping
    Lore::Vector2   m_basePosition;
    Lore::Vector2   m_speed;
    Rectangle m_hitBox;

    int m_lives;

    //Movement
    int m_maxX;
    int m_minX;

    //Sprite
    std::vector<AnimationInfo> m_spritesInfoVec;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Paddle_h__ //
