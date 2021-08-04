//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

// Test that header file is self-contained.
#include <boost/http_proto/rfc.hpp>

#include "test_suite.hpp"

namespace boost {
namespace http_proto {

class rfc_test
{
public:
    void
    run()
    {
    }
};

TEST_SUITE(rfc_test, "boost.http_proto.rfc");

} // http_proto
} // boost
