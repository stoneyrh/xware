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

#ifndef _XNET_CLASS_INIT_H_
#define _XNET_CLASS_INIT_H_

/*
 * Why we need this?
 * 
 * Because net message and handler will be created by a string, and 
 * the point is, the definition of those messages and handlers are in
 * xnetwork library, in that case, if we never use those symbols,
 * they won't be imported by linker, then the message and handler
 * registration mechanism won't work. So in order to import those
 * symbols, we need to at lease use those symbols once.
 *
 * NOTE: Only those messages not built in this binary are necessary
 * to be listed here. If the message and handler are part of this
 * binary, no need to list them, but it is not harmful even they are
 * listed.
 */

#define BEGIN_XNET_CLASS_INIT(name)                                             \
namespace __##name##_hidden__                                                   \
{                                                                               \
    class __xnet_class_initializer__                                            \
    {                                                                           \
        public:                                                                 \
            __xnet_class_initializer__()                                        \
            {

#define END_XNET_CLASS_INIT()                                                   \
            }                                                                   \
    };                                                                          \
static __xnet_class_initializer__ __xci__;                                      \
} // namespace

#define INIT_XNET_CLASS(name) name()

#endif
