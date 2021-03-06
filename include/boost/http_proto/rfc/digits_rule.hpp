//
// Copyright (c) 2021 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_RFC_DIGITS_RULE_HPP
#define BOOST_HTTP_PROTO_RFC_DIGITS_RULE_HPP

#include <boost/http_proto/detail/config.hpp>
#include <boost/http_proto/error.hpp>
#include <boost/http_proto/string_view.hpp>
#include <boost/url/grammar/parse_tag.hpp>
#include <cstdlib>

namespace boost {
namespace http_proto {

/** Rule for decimal numbers of unlimited length

    @par BNF
    @code
    number          = 1*DIGIT
    @endcode

    @par Specification
    @li <a href="https://datatracker.ietf.org/doc/html/rfc5234#section-3.6"
        >3.6. Variable Repetition: *Rule (rfc5234)</a>
*/
struct digits_rule
{
    string_view s;
    std::uint64_t v = 0;
    bool overflow = false;

    friend
    void
    tag_invoke(
        grammar::parse_tag const&,
        char const*& it,
        char const* end,
        error_code& ec,
        digits_rule& t) noexcept
    {
        parse(it, end, ec, t);
    }

private:
    BOOST_HTTP_PROTO_DECL
    static
    void
    parse(
        char const*& it,
        char const* end,
        error_code& ec,
        digits_rule& t) noexcept;
};

} // http_proto
} // boost

#endif
