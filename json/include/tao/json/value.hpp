// Copyright (c) 2017-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_VALUE_HPP
#define TAO_JSON_VALUE_HPP

#include "basic_value.hpp"
#include "operators.hpp"
#include "traits.hpp"

namespace tao::json
{
   using value = basic_value< traits >;

}  // namespace tao::json

#endif
