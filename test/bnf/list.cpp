//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

// Test that header file is self-contained.
#include <boost/http_proto/bnf/list.hpp>
#include <boost/http_proto/error.hpp>
#include <boost/http_proto/string_view.hpp>
#include <boost/http_proto/bnf/algorithm.hpp>
#include <boost/http_proto/bnf/ctype.hpp>

#include "test_suite.hpp"

namespace boost {
namespace http_proto {
namespace bnf {

class list_test
{
public:
    /*
        test-element = 1*DIGIT
    */
    struct test_element
    {
        using value_type = string_view;

        string_view v_;

        string_view value() const noexcept
        {
            return v_;
        }

        char const*
        parse(
            char const* start,
            char const* end,
            error_code& ec)
        {
            digit_set ds;
            auto it = ds.skip(
                start, end);
            if(it == start)
            {
                ec = error::syntax;
                return start;
            }
            return it;
        }
    };

    template<class T>
    void
    valid(string_view s)
    {
        BOOST_TEST_NO_THROW(
            validate<T>(s));
        BOOST_TEST(is_valid<T>(s));
    }

    template<class T>
    void
    invalid(string_view s)
    {
        BOOST_TEST_THROWS(
            validate<T>(s),
            std::exception);
        BOOST_TEST(! is_valid<T>(s));
    }

    void
    run()
    {
        {
            using T = list_of_zero_or_more<
                test_element>;
              valid<T>("");
            invalid<T>(",");
            invalid<T>(", ");
            invalid<T>(", ,");
            invalid<T>(",,,");
              valid<T>("1");
              valid<T>(",1");
              valid<T>("1,");
              valid<T>(", 1");
              valid<T>("1 ,");
            invalid<T>("1, ");
              valid<T>("1,2");
              valid<T>("1,2");
              valid<T>("1,2,3");
              valid<T>(", 1,\t2, 3");
        }
        {
            using T = list_of_one_or_more<
                test_element>;
            invalid<T>("");
            invalid<T>(",");
            invalid<T>(", ");
            invalid<T>(", ,");
            invalid<T>(",,,");
              valid<T>("1");
              valid<T>("1,2");
        }
        {
            using T = list<test_element, 2, 3>;
            invalid<T>("");
            invalid<T>(",");
            invalid<T>(", ");
            invalid<T>(", ,");
            invalid<T>(",,,");
            invalid<T>("1");
            invalid<T>(",1");
            invalid<T>("1,");
            invalid<T>(", 1");
            invalid<T>("1 ,");
            invalid<T>("1, ");
              valid<T>("1,2");
              valid<T>("1,2");
              valid<T>("1,2,3");
              valid<T>(", 1,\t2, 3");
            invalid<T>("1,2,3,4");
        }
    }
};

TEST_SUITE(list_test, "boost.http_proto.list");

} // bnf
} // http_proto
} // boost