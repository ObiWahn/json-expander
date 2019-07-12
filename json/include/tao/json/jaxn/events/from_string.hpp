// Copyright (c) 2017-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_JAXN_EVENTS_FROM_STRING_HPP
#define TAO_JSON_JAXN_EVENTS_FROM_STRING_HPP

#include <string>
#include <string_view>

#include "from_input.hpp"

namespace tao::json::jaxn::events
{
   // Events producer to parse a JAXN string representation.

   template< typename Consumer >
   void from_string( Consumer& consumer, const char* data, const std::size_t size, const char* source = nullptr, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
   {
      jaxn::events::from_input( consumer, pegtl::memory_input< pegtl::tracking_mode::lazy, pegtl::eol::lf_crlf, const char* >( data, data + size, source ? source : "tao::json::events::jaxn::from_string", byte, line, column ) );
   }

   template< typename Consumer >
   void from_string( Consumer& consumer, const char* data, const std::size_t size, const std::string& source, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
   {
      jaxn::events::from_string( consumer, data, size, source.c_str(), byte, line, column );
   }

   template< typename Consumer, typename... Ts >
   void from_string( Consumer& consumer, const std::string_view data, Ts&&... ts )
   {
      jaxn::events::from_string( consumer, data.data(), data.size(), std::forward< Ts >( ts )... );
   }

}  // namespace tao::json::jaxn::events

#endif
