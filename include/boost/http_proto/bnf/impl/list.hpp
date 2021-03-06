//
// Copyright (c) 2021 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_RULE_IMPL_LIST_HPP
#define BOOST_HTTP_PROTO_RULE_IMPL_LIST_HPP

#include <boost/http_proto/bnf/algorithm.hpp>
#include <boost/http_proto/bnf/ctype.hpp>
#include <boost/http_proto/bnf/sequence.hpp>
#include <boost/http_proto/rfc/charsets.hpp>
#include <boost/url/grammar/charset.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace http_proto {
namespace bnf {

template<
    class Element,
    std::size_t N,
    std::size_t M>
char const*
list<Element, N, M>::
begin(
    char const* const start,
    char const* const end,
    error_code& ec)
{
    n_ = 0;
    if(start == end)
    {
        if(n_ < N)
        {
            ec = grammar::error::incomplete;
            return start;
        }
        // empty list
        ec = error::end;
        return start;
    }
    // ( element ) ;most common
    auto it = element_.parse(
        start, end, ec);
    if(! ec)
    {
        ++n_;
        return it;
    }
    ec = {};
    // *( "," OWS ) element
    it = consume<zero_or_more<
        comma_ows>>(it, end, ec);
    //BOOST_ASSERT(! ec);
    it = element_.parse(
        it, end, ec);
    if(! ec)
    {
        ++n_;
        return it;
    }
    // empty
    if(n_ < N)
    {
        // too few
        ec = grammar::error::incomplete;
        return start;
    }
    ec = error::end;
    return start;
}

template<
    class Element,
    std::size_t N,
    std::size_t M>
char const*
list<Element, N, M>::
increment(
    char const* start,
    char const* const end,
    error_code& ec)
{
    if(n_ >= M)
    {
        // got enough
        ec = error::end;
        return start;
    }
    // *( OWS "," )
    auto it = consume<
        zero_or_more<ows_comma>>(
            start, end, ec);
    if(ec.failed())
        return it;
    if(it == start)
    {
        // no comma
        if(n_ < N)
        {
            // too few
            ec = grammar::error::incomplete;
            return start;
        }
        ec = error::end;
        return start;
    }
    if(it == end)
    {
        if(n_ < N)
        {
            // too few
            ec = grammar::error::incomplete;
            return start;
        }
        ec = error::end;
        return it;
    }
    // [ OWS element ]
    start = it;
    it = grammar::find_if_not(
        it, end, ws);
    it = element_.parse(
        it, end, ec);
    if(ec == grammar::error::incomplete)
        return start;
    if(ec.failed())
    {
        if(n_ < N)
        {
            // too few
            ec = error::syntax;
            return start;
        }
        // exclude prev OWS
        ec = error::end;
        return start;
    }
    ++n_;
    return it;
}

//------------------------------------------------

char const*
ows_comma::
parse(
    char const* start,
    char const* end,
    error_code& ec)
{
    if(start == end)
        return start;
    auto it = grammar::find_if_not(
        start, end, ws);
    if(it == end)
    {
        // missing comma
        ec = grammar::error::incomplete;
        return start;
    }
    if(*it != ',')
    {
        // expected comma
        ec = error::syntax;
        return start;
    }
    ++it;
    return it;
}

char const*
comma_ows::
parse(
    char const* start,
    char const* end,
    error_code& ec)
{
    if(start == end)
    {
        // expected comma
        ec = grammar::error::incomplete;
        return start;
    }
    auto it = start;
    if(*it != ',')
    {
        // expected comma
        ec = error::syntax;
        return it;
    }
    ++it;
    it = grammar::find_if_not(
        it, end, ws);
    return it;
}

} // bnf
} // http_proto
} // boost

#endif
