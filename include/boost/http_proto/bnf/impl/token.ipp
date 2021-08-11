//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

#ifndef BOOST_HTTP_PROTO_BNF_IMPL_TOKEN_IPP
#define BOOST_HTTP_PROTO_BNF_IMPL_TOKEN_IPP

#include <boost/http_proto/bnf/token.hpp>
#include <boost/http_proto/ctype.hpp>
#include <boost/http_proto/error.hpp>

namespace boost {
namespace http_proto {
namespace bnf {

char const*
token::
parse(
    char const* const start,
    char const* const end,
    error_code& ec)
{
    tchar_set ts;
    auto it = ts.skip(start, end);
    if(it == start)
    {
        // missing or invalid token
        ec = error::bad_element;
        return start;
    }
    value = { start, static_cast<
        std::size_t>(it - start) };
    return it;
}

} // bnf
} // http_proto
} // boost

#endif