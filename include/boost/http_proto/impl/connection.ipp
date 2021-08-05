//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

#ifndef BOOST_HTTP_PROTO_IMPL_CONNECTION_IPP
#define BOOST_HTTP_PROTO_IMPL_CONNECTION_IPP

#include <boost/http_proto/connection.hpp>

namespace boost {
namespace http_proto {

// https://datatracker.ietf.org/doc/html/rfc7230#section-7
// https://datatracker.ietf.org/doc/html/rfc7230#section-6.1
/*
    Connection        = 1#connection-option
    connection-option = token
    token             = 1*tchar
    tchar             = "!" / "#" / "$" / "%" / "&" /
                        "'" / "*" / "+" / "-" / "." /
                        "^" / "_" / "`" / "|" / "~" /
                        DIGIT / ALPHA
*/


} // http_proto
} // boost

#endif
