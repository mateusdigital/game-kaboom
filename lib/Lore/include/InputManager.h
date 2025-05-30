//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        InputManager.h                            //
//            █ █        █ █        Lore                                      //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016, 2017                  //
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

#ifndef __Lore_include_InputManager_h__
#define __Lore_include_InputManager_h__

//std
#include <map>
#include <set>
//Lore
#include "Lore_Utils.h"


NS_LORE_BEGIN

class InputManager
{
    // Enums //
public:
    typedef Uint8 KeyScanCodeType;
    typedef std::map<std::string, std::set<KeyScanCodeType>> KeybindingsMap;
    typedef std::initializer_list<KeyScanCodeType> KeyScanCodeTypeInitList;

    // Singleton //
public:
    COREGAME_SINGLETON_OF(InputManager);
    COREGAME_DISALLOW_COPY_MOVE_ASSIGNS(InputManager);
private:
    InputManager() = default;


    // Init / Shutdown //
public:
    void initialize();
    void shutdown();


    // Public Methods //
public:
    void update();


    // Key "atomics" methods //
public:
    bool isKeyDown(KeyScanCodeType scanCode);
    bool isKeyUp  (KeyScanCodeType scanCode);

    bool wasKeyDown(KeyScanCodeType scanCode);
    bool wasKeyUp  (KeyScanCodeType scanCode);

    bool isKeyClick(KeyScanCodeType scanCode);


    // Key bindings methods //
public:
    void assignKeyBindings(
        const std::string &keybinding,
        const KeyScanCodeTypeInitList &keys);

    //Empty list means that is to remove all bidings.
    void removeKeyBindings(
        const std::string &keybinding,
        const std::initializer_list<KeyScanCodeType> &keys);


    bool isKeyDown(const std::string &keybinding);
    bool isKeyUp  (const std::string &keybinding);

    bool wasKeyDown(const std::string &keybinding);
    bool wasKeyUp  (const std::string &keybinding);

    bool isKeyClick(const std::string &keybinding);


    // iVars //
private:
    KeyScanCodeType *m_pPrevKeys;
    KeyScanCodeType *m_pCurrKeys;

    int m_numKeys;

    KeybindingsMap m_keybindingsMap;
};

NS_LORE_END
#endif // __Lore_include_InputManager_h__ //
