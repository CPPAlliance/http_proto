//
// Copyright (c) 2021 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_RULE_IMPL_TOKEN_IPP
#define BOOST_HTTP_PROTO_RULE_IMPL_TOKEN_IPP

#include <boost/http_proto/bnf/token.hpp>
#include <boost/http_proto/error.hpp>
#include <boost/http_proto/bnf/ctype.hpp>

#include <boost/http_proto/rfc/charsets.hpp>
#include <boost/url/grammar/token.hpp>

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
    auto it = start;
    grammar::token<tchars_t> t0;
    if(! grammar::parse(
        it, end, ec, t0))
        return start;
    s = *t0;
    return it;
#if 0
    if(start == end)
    {
        ec = grammar::error::incomplete;
        return start;
    }
    tchar_set ts;
    auto it = start;
    if(! ts.contains(*it))
    {
        // invalid tchar
        ec = error::syntax;
        return start;
    }
    it = ts.skip(it + 1, end);
    s_ = string_view(
        start, it - start);
    return it;
#endif
}

} // bnf
} // http_proto
} // boost

#endif
