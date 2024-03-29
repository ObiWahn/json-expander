// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_UBJSON_PARSE_FILE_HPP
#define TAO_JSON_UBJSON_PARSE_FILE_HPP

#include <string>
#include <utility>

#include "../events/to_value.hpp"
#include "../events/transformer.hpp"

#include "events/parse_file.hpp"

namespace tao::json::ubjson
{
   template< template< typename... > class Traits, template< typename... > class... Transformers >
   [[nodiscard]] basic_value< Traits > basic_parse_file( const std::string& filename )
   {
      json::events::transformer< json::events::to_basic_value< Traits >, Transformers... > consumer;
      events::parse_file( consumer, filename );
      return std::move( consumer.value );
   }

   template< template< typename... > class... Transformers >
   [[nodiscard]] value parse_file( const std::string& filename )
   {
      return basic_parse_file< traits, Transformers... >( filename );
   }

}  // namespace tao::json::ubjson

#endif
