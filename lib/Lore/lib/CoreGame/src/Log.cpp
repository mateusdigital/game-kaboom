//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Log.cpp                                   //
//            █ █        █ █        CoreGame                                  //
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
#include "../include/Log.h"
//std
#include <iostream>
//CoreGame
#include "../include/StringUtils.h"

//Usings
USING_NS_COREGAME;


////////////////////////////////////////////////////////////////////////////////
// Operator Overloads for Log::Type                                           //
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream &os, Log::Type t)
{
    auto s = (t == Log::Type::Fatal)   ?  "Fatal"    :
             (t == Log::Type::Error)   ?  "Error"    :
             (t == Log::Type::Warning) ?  "Warning"  :
             (t == Log::Type::Verbose) ?  "Verbose"  :
             (t == Log::Type::Debug1)  ?  "Debug1"   :
             (t == Log::Type::Debug2)  ?  "Debug2"   :
             (t == Log::Type::Debug3)  ?  "Debug3"   :
             (t == Log::Type::Debug4)  ?  "Debug4"   :
                                          "DUMMY";

    os << s;
    return os;
}



////////////////////////////////////////////////////////////////////////////////
// Static Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
Log& Log::GetDefaultLogger()
{
    static Log s_logger;
    return s_logger;
}


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Log::Log()
{
    addLogType(Type::Fatal);
    addLogType(Type::Error);
    addLogType(Type::Warning);
    addLogType(Type::Verbose);
    addLogType(Type::Debug1);
    addLogType(Type::Debug2);
    addLogType(Type::Debug3);
    addLogType(Type::Debug4);

    addLogOutput(Output::std_out);
}

Log::~Log()
{
    closeFileStream();
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Log::addLogType(Type type)
{
    m_type |= static_cast<int>(type);
}

void Log::removeLogType(Type type)
{
    m_type &= ~static_cast<int>(type);
}

bool Log::isLogTypeActive(Type type) const
{
    return m_type & static_cast<int>(type);
}


void Log::addLogOutput(Output output)
{
    m_output |= static_cast<int>(output);
}

void Log::removeLogOutput(Output output)
{
    m_output &= ~static_cast<int>(output);
}

bool Log::isLogOutputActive(Output output) const
{
    return m_output & static_cast<int>(output);
}


void Log::setLogFileFilename(const std::string &filename, bool append)
{
    closeFileStream();
    auto mode = (append)
                ? std::ios::out | std::ios::app
                : std::ios::out;

    m_filestream.open(filename, mode);
    COREGAME_ASSERT_ARGS(m_filestream.is_open() == true,
                         "Failed to open stream with filename (%s)",
                         filename.c_str());
}

void Log::log(Type type, const std::string &str)
{
    if(!isLogTypeActive(type))
        return;

    //Check for cout.
    if(isLogOutputActive(Output::std_out))
        logAt(type, std::cout, str);

    //Check for cerr.
    if(isLogOutputActive(Output::std_err))
        logAt(type, std::cerr, str);

    //Check for file and if file is open.
    if(isLogOutputActive(Output::file) && m_filestream.is_open())
        logAt(type, m_filestream, str);

}

void Log::log(Type type, const char *fmt, ...)
{
    if(!isLogTypeActive(type))
        return;

    //Build the string.
    va_list args;
    va_start(args, fmt);

    log(type, StringUtils::vformat(fmt, args));

    va_end(args);
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Log::closeFileStream()
{
    if(m_filestream.is_open())
    {
        m_filestream.flush();
        m_filestream.close();
    }
}


void Log::logAt(Type type, std::ostream &os, const std::string &msg)
{
    os << "[" << type << "] " << msg << std::endl << std::flush;
}
