#ifndef _X_LOCALE_H_
#define _X_LOCALE_H_

#include "xglobal.h"
#include <boost/locale.hpp>

namespace xws
{
namespace xlocale = boost::locale;
typedef xlocale::basic_format<xchar> xchar_format;

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *msg)
{
    return xlocale::translate(msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *context, CharType const *msg)
{
    return xlocale::translate(context, msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *single, CharType const *plural, int n)
{
    return xlocale::translate(single, plural, n);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(CharType const *context, CharType const *single, CharType const *plural, int n)
{
    return xlocale::translate(context, single, plural, n);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &msg)
{
    return xlocale::translate(msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &context, std::basic_string<CharType> const &msg)
{
    return xlocale::translate(context, msg);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &context, std::basic_string<CharType> const &single, std::basic_string<CharType> const &plural, int n)
{
    return xlocale::translate(context, single, plural, n);
}

template<typename CharType>
xlocale::basic_message<CharType> xtr(std::basic_string<CharType> const &single, std::basic_string<CharType> const &plural, int n)
{
    return xlocale::translate(single, plural, n);
}

} // namespace xws

#endif
