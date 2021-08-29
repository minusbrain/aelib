/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2021 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <aelib/base/improve_containers.h>

#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "helpers.h"

namespace base {

using T_option_value = std::variant<std::nullopt_t, int, float, std::string, bool>;
using cl_parsed_options = std::map<std::string, T_option_value>;

enum class argparser_option_type { UNDECIDED, INT, FLOAT, STRING, FLAG };

class cl_option {
   public:
    cl_option(std::string option_name)
        : _short_option(),
          _long_option(),
          _option_type(argparser_option_type::UNDECIDED),
          _option_name(option_name),
          _option_description(),
          _default_value(std::nullopt),
          _mandatory(false) {}
    ~cl_option() = default;

    std::string get_name() const { return _option_name; }

    cl_option& default_value(int val) {
        if (_option_type != argparser_option_type::UNDECIDED && _option_type != argparser_option_type::INT) {
            throw std::invalid_argument(
                "Trying to set default value to INT even though its already defined as a different type.");
        }
        _default_value = val;
        _option_type = argparser_option_type::INT;
        return *this;
    }

    cl_option& default_value(float val) {
        if (_option_type != argparser_option_type::UNDECIDED && _option_type != argparser_option_type::FLOAT) {
            throw std::invalid_argument(
                "Trying to set default value to FLOAT even though its already defined as a different type.");
        }
        _default_value = val;
        _option_type = argparser_option_type::FLOAT;
        return *this;
    }

    cl_option& default_value(std::string val) {
        if (_option_type != argparser_option_type::UNDECIDED && _option_type != argparser_option_type::STRING) {
            throw std::invalid_argument(
                "Trying to set default value to STRING even though its already defined as a different type.");
        }
        _default_value = val;
        _option_type = argparser_option_type::STRING;
        return *this;
    }

    bool has_default_value() const { return std::holds_alternative<std::nullopt_t>(_default_value) == false; }
    T_option_value get_default_value() const { return _default_value; }
    bool get_default_value_as_flag() const { return std::get<bool>(_default_value); }
    int get_default_value_as_int() const { return std::get<int>(_default_value); }
    float get_default_value_as_float() const { return std::get<float>(_default_value); }
    std::string get_default_value_as_string() const { return std::get<std::string>(_default_value); }

    cl_option& short_option(char short_option) {
        _short_option = short_option;
        return *this;
    }

    bool has_short_option() const { return _short_option.has_value(); }
    char get_short_option() const { return _short_option.value(); }

    cl_option& long_option(std::string long_option) {
        _long_option = long_option;
        return *this;
    }

    bool has_long_option() const { return _long_option.has_value(); }
    std::string get_long_option() const { return _long_option.value(); }

    cl_option& description(std::string description) {
        _option_description = description;
        return *this;
    }

    bool has_description() const { return _option_description.has_value(); }
    std::string get_description() const { return _option_description.value(); }

    cl_option& type(argparser_option_type type) {
        _option_type = type;
        if (_option_type == argparser_option_type::FLAG && !has_default_value()) {
            _default_value = false;
        }
        return *this;
    }

    cl_option& mandatory() {
        _mandatory = true;
        return *this;
    }

    cl_option& mandatory(bool val) {
        _mandatory = val;
        return *this;
    }

    bool is_mandatory() const { return _mandatory; }

    argparser_option_type get_type() const { return _option_type; }
    bool is_type_decided() const { return _option_type != argparser_option_type::UNDECIDED; }

    bool is_valid() const {
        return (is_type_decided() && (has_short_option() || has_long_option()) &&
                !(is_mandatory() && _option_type != argparser_option_type::FLAG));
    }

   private:
    std::optional<char> _short_option;
    std::optional<std::string> _long_option;
    argparser_option_type _option_type;
    std::string _option_name;
    std::optional<std::string> _option_description;
    T_option_value _default_value;
    bool _mandatory;
};

class argparser {
   public:
    argparser(std::string app_name) : _app_name(app_name), _options(){};
    ~argparser() = default;

    std::string get_app_name() const { return _app_name; }

    cl_option& add_option(std::string option_name) {
        _options.emplace_back(cl_option{option_name});
        return _options.back();
    }

    cl_parsed_options parse(int argc, char** argv) {
        BASE_INTENTIONALLY_UNUSED(argc);
        BASE_INTENTIONALLY_UNUSED(argv);

        return cl_parsed_options{};
    }
    cl_parsed_options parse(std::vector<std::string>& args) {
        BASE_INTENTIONALLY_UNUSED(args);
        return cl_parsed_options{};
    }

    void print_help() {
        assert(all_options_valid());
        std::cout << "Usage:\n" << get_app_name();
        for (auto& opt : _options) {
            std::cout << (opt.is_mandatory() ? " " : " [");
            bool has_both_options = opt.has_short_option() && opt.has_long_option();
            if (opt.has_short_option()) std::cout << "-" << opt.get_short_option();
            if (has_both_options) std::cout << "|";
            if (opt.has_long_option()) std::cout << "--" << opt.get_long_option();
            std::cout << (opt.is_mandatory() ? "" : "]");
        }
    }

    std::vector<cl_option> get_options() const { return _options; }
    bool all_options_valid() const {
        return base::count_if(_options, [](auto& opt) { return opt.is_valid(); }) == (int)_options.size();
    }

    // cl_parser.add_parameters("words", "List of words");

   private:
    std::string _app_name;
    std::vector<cl_option> _options;
};

}  // namespace base

inline std::ostream& operator<<(std::ostream& os, const base::T_option_value& val) {
    std::visit(
        [&os](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                os << arg;
            else if constexpr (std::is_same_v<T, float>)
                os << arg;
            else if constexpr (std::is_same_v<T, std::string>)
                os << std::quoted(arg);
            else if constexpr (std::is_same_v<T, bool>)
                os << (arg ? "true" : "false");
            else
                os << "undefined";
        },
        val);

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const base::cl_option& opt) {
    os << "Command Line Option ('" << opt.get_name() << "'";
    os << ", Status=" << (opt.is_valid() ? "valid" : "invalid");
    if (opt.has_short_option()) {
        os << ", Short='-" << (char)opt.get_short_option() << "'";
    }
    if (opt.has_long_option()) {
        os << ", Long='--" << opt.get_long_option() << "'";
    }
    if (opt.has_description()) {
        os << ", Description='" << opt.get_description() << "'";
    }
    if (opt.has_default_value()) {
        os << ", Default=" << opt.get_default_value();
    }
    if (opt.is_mandatory()) {
        os << ", MANDATORY";
    }
    os << ")";
    return os;
}
