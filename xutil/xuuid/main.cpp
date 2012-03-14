/*
* ****************************************************************************
* *                                                                          *
* * Copyright 2008, xWorkshop Inc.                                           *
* * All rights reserved.                                                     *
* * Redistribution and use in source and binary forms, with or without       *
* * modification, are permitted provided that the following conditions are   *
* * met:                                                                     *
* *    * Redistributions of source code must retain the above copyright      *
* * notice, this list of conditions and the following disclaimer.            *
* *    * Redistributions in binary form must reproduce the above             *
* * copyright notice, this list of conditions and the following disclaimer   *
* * in the documentation and/or other materials provided with the            *
* * distribution.                                                            *
* *    * Neither the name of xWorkshop Inc. nor the names of its             *
* * contributors may be used to endorse or promote products derived from     *
* * this software without specific prior written permission.                 *
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      *
* * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        *
* * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    *
* * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     *
* * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    *
* * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
* * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    *
* * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
* * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
* * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    *
* * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     *
* *                                                                          *
* * Author: stoneyrh@163.com                                                 *
* *                                                                          *
* ****************************************************************************
*/

#include "xglobal.h"
#include "xuuid.h"
#include "xuuid_application.h"
#include "xcommand_line_args.h"
#include "xstring_algorithm.h"
#include "xexception.h"

using namespace xws;

int main(int argc, char* argv[])
{
    try
    {
        xprogram_options::options_description options_description(_A("xuuid <options>"));
        options_description.add_options()
            (_A("help,h"),    _A("produce this message"))
            (_A("version,v"), _A("print out program version"))
            (_A("lower,l"),   _A("output UUID in lower case"))
            (_A("number,n"),  xprogram_options::value<int>()->default_value(1), _A("number of UUIDs will be created"))
            ;
        //
        xuuid_application app(argc, xargs<xchar>(argc, argv), options_description);
        if (app.has_option(_A("help")))
        {
            xcout << app.version_str() << std::endl << std::endl;
            acout << _A("Usage:") << std::endl;
            acout << options_description << std::endl;
            xcout << app.legal_statement() << std::endl;
            xcout << app.bug_statement() << std::endl;
        }
        else if (app.has_option(_A("version")))
        {
            xcout << app.version_str() << std::endl;
            xcout << app.legal_statement() << std::endl;
            xcout << app.bug_statement() << std::endl;
        }
        else
        {
            int number = app.option_value<int>(_A("number"));
            bool upper = !app.has_option(_A("lower"));
            xuuid_random_generator uuid_random_generator;
            for (int i = 0; i < number; ++ i)
            {
                xuuid uuid(uuid_random_generator());
                xstring uuid_string(xuuid_to_xstring(uuid));
                if (upper)
                {
                    xupper(uuid_string);
                }
                xcout << uuid_string << std::endl;
            }
        }
        return app.exec();
    }
    catch (xexception& e)
    {
        acerr << xexception_str(e) << _A(".") << std::endl;
    }
    catch (...)
    {
        xcerr << _X("Unknown error occurs.") << std::endl;
    }
    return -1;
}
