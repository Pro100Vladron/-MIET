/* Json object.
 * @file
 * @date 2018-08-09
 * @author Anonymous
 */

#ifndef __JSON_HPP__
#define __JSON_HPP__

#include <map>
#include <string>
#include <vector>
#include <variant>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

/* Json EBNF specification (https://www.json.org)
 * string := \" (\\ . | [^\"])* \"
 * number := [0-9]+(\.[0-9]*)?
 * boolean := "true" | "false"
 * nullable := "null"
 * value := number | string | boolean | nullable | array | object
 * array := '[' value (',' value)* ']'
 * key_value := string ':' value
 * object := '{' key_value (',' key_value)* '}'
 * json := array | object
 */

namespace x3 = boost::spirit::x3;

namespace json::types
{
    struct array;
    struct object;

    using value = x3::variant<
        std::nullptr_t,
        bool,
        int,
        float,
        std::string,
        x3::forward_ast<array>,
        x3::forward_ast<object>
    >;

    struct array : std::vector<value> {};
    struct object : std::map<std::string, value> {};

    using json = x3::variant<array, object>;
}

namespace json::parser
{
    using x3::int_;
    using x3::bool_;
    using x3::lit;
    using x3::lexeme;

    const auto sfloat_ = x3::real_parser<float, x3::strict_real_policies<float>>();
	
    // Rule Declarations
    x3::rule<class number_tag, std::variant<float, int>> const number = "number";
    x3::rule<class quoted_string_tag, std::string> const quoted_string = "quoted_string";
    x3::rule<class nullable_tag, std::nullptr_t> const nullable = "nullable";
    x3::rule<class value_tag, json::types::value> const value = "value";
    x3::rule<class array_tag, json::types::array> const array = "array";
    x3::rule<class object_tag, json::types::object> const object = "object";
    x3::rule<class json_tag, json::types::json> const json = "json";

    // Rule Definitions
    auto const number_def = sfloat_ | int_;
    auto const quoted_string_def = lexeme['"' >> *((lit('\\') >> x3::char_) | (x3::char_ - '"' - '\\')) >> '"'];
    auto const nullable_def = lit("null") >> x3::attr(nullptr);
    auto const value_def = 
        sfloat_ | 
        int_ | 
        quoted_string | 
        bool_ | 
        nullable | 
        array | 
        object;

    auto const array_def = lit('[') >> -(value % ',') >> lit(']');
    auto const key_value = quoted_string >> ':' >> value;
    auto const object_def = lit('{') >> -(key_value % ',') >> lit('}');
    auto const json_def = array | object;

    BOOST_SPIRIT_DEFINE(number, quoted_string, nullable, value, array, object, json)
}

#endif // __JSON_HPP__
