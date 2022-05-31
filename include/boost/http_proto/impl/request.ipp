//
// Copyright (c) 2021 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_IMPL_REQUEST_IPP
#define BOOST_HTTP_PROTO_IMPL_REQUEST_IPP

#include <boost/http_proto/request.hpp>
#include <boost/http_proto/request_view.hpp>
#include <boost/http_proto/detail/copied_strings.hpp>
#include <utility>

namespace boost {
namespace http_proto {

request::
request(
    request const& other)
    : fields_base(other,
        detail::kind::request)
{
}

request::
request(request&& other) noexcept
    : request()
{
    swap(other);
}

request&
request::
operator=(request&& other) noexcept
{
    request temp(
        std::move(other));
    temp.swap(*this);
    return *this;
}

request&
request::
operator=(
    request const& other)
{
    request temp(other);
    swap(temp);
    return *this;
}

request::
request(
    request_view const& rv)
    : fields_base(rv,
        detail::kind::request)
{
}

//------------------------------------------------

request::
operator
request_view() const noexcept
{
    return request_view(h_);
}

//------------------------------------------------

void
request::
clear() noexcept
{
    if(h_.buf == nullptr)
        return;
    this->fields_base::clear();
    set_impl(
        http_proto::method::get,
        "GET",
        "/",
        http_proto::version::http_1_1);
}

void
request::
swap(request& other) noexcept
{
    this->fields_view_base::swap(other);
}

//------------------------------------------------

void
request::
set_impl(
    http_proto::method m,
    string_view ms,
    string_view t,
    http_proto::version v)
{
    detail::copied_strings cs(
        this->string());
    ms = cs.maybe_copy(ms);
    t = cs.maybe_copy(t);

    auto const vs =
        to_string(v);
    auto const n =
        ms.size() + 1 +
        t.size() + 1 +
        vs.size() + 2;
    auto dest =
        set_start_line_impl(n);
    std::memcpy(
        dest,
        ms.data(),
        ms.size());
    dest += ms.size();
    *dest++ = ' ';
    std::memcpy(
        dest,
        t.data(),
        t.size());
    dest += t.size();
    *dest++ = ' ';
    std::memcpy(
        dest,
        vs.data(),
        vs.size());
    dest += vs.size();
    *dest++ = '\r';
    *dest++ = '\n';

    h_.req.method = m;
    h_.req.version = v;
    h_.req.method_len =
        static_cast<off_t>(ms.size());
    h_.req.target_len =
        static_cast<off_t>(t.size());
}

} // http_proto
} // boost

#endif
