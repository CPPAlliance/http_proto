//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

#ifndef BOOST_HTTP_PROTO_BNF_IMPL_TOKEN_LIST_IPP
#define BOOST_HTTP_PROTO_BNF_IMPL_TOKEN_LIST_IPP

#include <boost/http_proto/bnf/token_list.hpp>
#include <boost/http_proto/error.hpp>
#include <boost/http_proto/detail/rfc7230.hpp>

namespace boost {
namespace http_proto {

/*
    legacy list rules:
    1#element => *( "," OWS ) element *( OWS "," [ OWS element ] )
*/

// *( "," OWS ) element *( OWS "," )
char const*
token_list_bnf::
begin(
    char const* const start,
    char const* const end,
    error_code& ec)
{
    // *( "," OWS )
    auto const first =
        detail::skip_opt_comma_ows(
            start, end);
    // token
    auto it = detail::skip_token(
        first, end);
    if(it == first)
    {
        // missing token
        ec = error::bad_value;
        return start;
    }
    value = { first, static_cast<
        std::size_t>(it - first) };
    // *( OWS "," )
    return detail::skip_opt_ows_comma(
        comma_, it, end);
}

// [ OWS element *( OWS "," ) ]
char const*
token_list_bnf::
increment(
    char const* const start,
    char const* const end,
    error_code& ec)
{
    // [ ... ]
    if(start == end)
        return nullptr;
    if(! comma_)
    {
        // missing comma
        ec = error::bad_value;
        return start;
    }
    // OWS
    auto const first =
        detail::skip_ows(start, end);
    // token
    auto it = detail::skip_token(
        first, end);
    if(it == first)
    {
        // missing token
        ec = error::bad_value;
        return start;
    }
    value = { first, static_cast<
        std::size_t>(it - first) };
    // *( OWS "," )
    return detail::skip_opt_ows_comma(
        comma_, it, end);
}

} // http_proto
} // boost

#endif