//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

#ifndef BOOST_HTTP_PROTO_BNF_CHUNK_EXT_HPP
#define BOOST_HTTP_PROTO_BNF_CHUNK_EXT_HPP

#include <boost/http_proto/detail/config.hpp>
#include <boost/http_proto/error.hpp>
#include <boost/http_proto/string_view.hpp>
#include <boost/http_proto/trivial_optional.hpp>

namespace boost {
namespace http_proto {
namespace bnf {

/** BNF for chunk-ext

    @par BNF
    @code
    chunk-ext      = *( ";" chunk-ext-name [ "=" chunk-ext-val ] )

    chunk-ext-name = token
    chunk-ext-val  = token / quoted-string
    @endcode

    @see
        https://datatracker.ietf.org/doc/html/rfc7230#section-4.1.1
*/
struct chunk_ext
{
    struct value_type
    {
        string_view name;
        trivial_optional<
            string_view> value;
    };

    struct bnf_type
    {
        BOOST_HTTP_PROTO_DECL
        char const*
        parse_element(
            value_type& result,
            char const* const start,
            char const* const end,
            error_code& ec);
    };
};

} // bnf
} // http_proto
} // boost

#endif