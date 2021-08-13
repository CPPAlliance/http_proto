//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

#ifndef BOOST_HTTP_PROTO_BASIC_PARSER_HPP
#define BOOST_HTTP_PROTO_BASIC_PARSER_HPP

#include <boost/http_proto/detail/config.hpp>
#include <boost/http_proto/error.hpp>
#include <boost/http_proto/string_view.hpp>
#include <boost/http_proto/trivial_optional.hpp>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace boost {
namespace http_proto {

#ifndef BOOST_HTTP_PROTO_DOCS
class context;
#endif

/** A parser for HTTP/1 messages.

    The parser is strict. Any malformed
    inputs according to the documented
    HTTP ABNFs is treated as an
    unrecoverable error.
*/
class basic_parser
{
private:
    // headers have a maximum size of 65536 chars
    using off_t = std::uint16_t;

    enum class api
    {
        header,
        body,
        body_part,
        chunk,
        chunk_part,
    };

    enum class state
    {
        nothing_yet = 0,
        start_line,
        fields,
        body,
        chunk,
        chunk_next,
        complete
    };

    struct config
    {
        constexpr config() noexcept;

        std::size_t header_limit;   // max header size
    };

    struct message
    {
        constexpr message() noexcept;

        std::size_t header_size;   // full header size
        string_view payload;       // payload part
        trivial_optional<
            std::uint64_t
                > payload_size;
        std::uint64_t
            payload_remain;
        char version;               // HTTP-version, 0 or 1

        bool is_chunked : 1;
    };

    context& ctx_;
    char* buffer_;
    std::size_t cap_;           // allocated size
    std::size_t size_;          // committed part
    std::size_t used_;          // parsed part
    state state_;
    api api_;

    config cfg_;
    message m_;

    explicit
    basic_parser(
        context& ctx) noexcept;

public:
    BOOST_HTTP_PROTO_DECL
    ~basic_parser();

    /** Returns `true` if a complete message has been parsed.
    */
    bool
    is_done() const noexcept
    {
        return state_ ==
            state::complete;
    }

    /** Prepare the parser for the next message.

    */
    BOOST_HTTP_PROTO_DECL
    void
    reset();

    BOOST_HTTP_PROTO_DECL
    std::pair<void*, std::size_t>
    prepare();

    BOOST_HTTP_PROTO_DECL
    void
    commit(std::size_t n);

    BOOST_HTTP_PROTO_DECL
    void
    commit_eof();

    BOOST_HTTP_PROTO_DECL
    void
    parse_header(error_code& ec);

    BOOST_HTTP_PROTO_DECL
    void
    parse_body(error_code& ec);

    BOOST_HTTP_PROTO_DECL
    void
    parse_body_part(error_code& ec);

    BOOST_HTTP_PROTO_DECL
    void
    parse_chunk_ext(
        error_code& ec);

    BOOST_HTTP_PROTO_DECL
    void
    parse_chunk_part(
        error_code& ec);

    BOOST_HTTP_PROTO_DECL
    void
    parse_chunk_trailer(
        error_code& ec);

    string_view
    payload() const noexcept
    {
        return m_.payload;
    }

private:
    friend class request_parser;
    friend class response_parser;

    virtual char* parse_start_line(
        char*, char const*, error_code&) = 0;
    virtual void finish_header(error_code&) = 0;

    void do_parse(error_code&);
    char* parse_fields(char*, char const*, error_code&);
    char* parse_field(char*, char const*, error_code&);
    void do_connection(string_view, error_code&);
    void do_content_length(string_view, error_code&);
    void do_transfer_encoding(string_view, error_code&);
    void do_upgrade(string_view, error_code&);
};

} // http_proto
} // boost

#endif
