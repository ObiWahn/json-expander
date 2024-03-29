// Copyright (c) 2015-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hpp"

#include <list>
#include <unordered_map>

#include <tao/json/pointer.hpp>
#include <tao/json/value.hpp>

namespace tao::json
{
   void unit_test()
   {
      std::cout << "json::value: " << sizeof( value ) << std::endl;
      std::cout << "json::pointer: " << sizeof( pointer ) << std::endl;

      std::cout << "json::internal::value_union< json::value >: " << sizeof( internal::value_union< value > ) << std::endl;

      std::cout << "std::string: " << sizeof( std::string ) << std::endl;

      std::cout << "std::vector< json::value >: " << sizeof( std::vector< value > ) << std::endl;
      std::cout << "std::list< json::value >: " << sizeof( std::list< value > ) << std::endl;

      std::cout << "std::map< std::string, json::value, std::less<> >: " << sizeof( std::map< std::string, value, std::less<> > ) << std::endl;
      std::cout << "std::multimap< std::string, json::value >: " << sizeof( std::multimap< std::string, value > ) << std::endl;
      std::cout << "std::unordered_map< std::string, json::value >: " << sizeof( std::unordered_map< std::string, value > ) << std::endl;
      std::cout << "std::unordered_multimap< std::string, json::value >: " << sizeof( std::unordered_multimap< std::string, value > ) << std::endl;
   }

}  // namespace tao::json

#include "main.hpp"
