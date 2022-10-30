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

#include <algorithm>
#include <exception>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include "helpers.h"
#include "improve_containers.h"

namespace base {

class cl_option;

using T_strict_option_type = std::variant<std::nullopt_t, bool, int, float, double, std::string>;
using T_parsed_option_map = std::map<std::string, T_strict_option_type>;

}  // namespace base

namespace base {

// Forward declarations stream output helper
inline std::ostream& operator<<(std::ostream& os, const base::cl_option& opt);

/*
    Parsing result will be returned back to user
*/
class argparse_result {
   public:
    argparse_result() = default;
    ~argparse_result() = default;

    bool success() const { return _success; }

    template <typename T>
    T get(const std::string& index) const {
        T temp{};
        try {
            T_strict_option_type opt = _parsed_options.at(index);
            temp = std::get<T>(opt);
        } catch (const std::out_of_range& ex) {
            throw std::logic_error{"Option " + index + " not found. " + ex.what()};
        } catch (const std::bad_variant_access& ex) {
            throw std::logic_error{"Used wrong type to get option " + index + ". " + ex.what()};
        } catch (const std::exception& ex) {
            throw std::logic_error{"Unknown error while getting option " + index + ". " + ex.what()};
        }

        return temp;
    }

    T_strict_option_type operator[](const std::string& index) const { return _parsed_options.at(index); }
    bool has_option(const std::string& index) const { return _parsed_options.find(index) != _parsed_options.end(); }
    bool is_flag_set(const std::string& index) const {
        if (has_option(index))
            return std::get<bool>(_parsed_options.at(index));
        else
            return false;
    }

    const T_parsed_option_map& get_options() { return _parsed_options; }

    void insert(std::string key, T_strict_option_type value) { _parsed_options.insert_or_assign(key, value); }
    void add_error(std::string error, bool fatal = false) {
        _errors.push_back(error);
        if (fatal) _success = false;
    }

    const std::vector<std::string>& get_errors() const { return _errors; }

   private:
    friend std::ostream& operator<<(std::ostream& os, const argparse_result& parse_result);

    T_parsed_option_map _parsed_options;
    std::vector<std::string> _errors;
    bool _success = true;
};

/*
    Parsing context. Context information for single parse call
*/
struct parse_context {
    parse_context(const std::vector<cl_option>& options, const std::vector<std::string>& args)
        : _parsed(), _options(options), _args(args), _missing_mandatory_options() {}

    bool all_mandatories_found() const { return _missing_mandatory_options.size() == 0; }
    std::vector<std::string> get_missing_mandatories() const { return _missing_mandatory_options; }
    void remove_from_missing_mandatory_options(const std::string& name) {
        auto it = base::find(_missing_mandatory_options, name);
        if (it != _missing_mandatory_options.end()) {
            _missing_mandatory_options.erase(it);
        }
    }

    argparse_result _parsed;
    const std::vector<cl_option>& _options;
    const std::vector<std::string>& _args;
    std::vector<std::string> _missing_mandatory_options;
};

/*
    Single Command line option used for parsing
*/
class cl_option {
   public:
    cl_option(std::string option_name)
        : _short_option(),
          _long_option(),
          _option_name(option_name),
          _option_description(),
          _default_value(std::nullopt),
          _type_indicator(std::nullopt),
          _valid(true),
          _mandatory(false) {}
    ~cl_option() = default;

    enum short_or_long_option { SHORT_OPTION, LONG_OPTION };

    bool operator<(const cl_option& other) {
        if (is_mandatory() == other.is_mandatory())
            return get_name() < other.get_name();
        else if (is_mandatory())
            return true;
        else
            return false;
    }

    std::string get_name() const { return _option_name; }

    cl_option& default_value(T_strict_option_type val) {
        if (val.index() != _type_indicator.index()) {
            _valid = false;
            throw std::logic_error{"Default value type does not match option type for option " + get_name()};
        }
        _default_value = val;
        return *this;
    }

    template <typename T>
    cl_option& set_type() {
        _type_indicator = T{};

        if (std::is_same<bool, T>::value) _default_value.emplace<bool>(false);

        return *this;
    }

    T_strict_option_type get_type() { return _type_indicator; }

    bool has_default_value() const { return std::holds_alternative<std::nullopt_t>(_default_value) == false; }

    T_strict_option_type get_default_value() const { return _default_value; }

    cl_option& short_option(char short_option) {
        if (!std::isalnum(short_option)) {
            _valid = false;
            throw std::invalid_argument("Trying to set short option to non alphanumeric character");
        }
        _short_option = short_option;
        return *this;
    }

    bool has_short_option() const { return _short_option.has_value(); }
    char get_short_option() const { return _short_option.value(); }

    cl_option& long_option(std::string long_option) {
        auto it = base::find_if(long_option, [](char c) { return !std::isalnum(c) && c != '_' && c != '-'; });
        if (it != long_option.end()) {
            _valid = false;
            throw std::invalid_argument("Invalid option name '" + long_option +
                                        "'. Only alphanumerics, '_' and '-' allowed");
        }
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

    cl_option& mandatory(bool val = true) {
        _mandatory = val;
        return *this;
    }

    bool is_mandatory() const { return _mandatory; }

    bool is_valid() const {
        if (_valid) {
            if (!(has_short_option() || has_long_option())) {
                std::cout << get_name() << " Has neither short nor long option.\n";
                return false;
            }

            if (std::holds_alternative<std::nullopt_t>(_type_indicator)) {
                std::cout << get_name() << " Type is not decided.\n";
                return false;
            }

            if (is_mandatory() && std::holds_alternative<bool>(_type_indicator)) {
                std::cout << get_name() << " Boolean option is mandatory\n";
                return false;
            }

            if (!std::holds_alternative<std::nullopt_t>(_default_value) &&
                _default_value.index() != _type_indicator.index()) {
                std::cout << get_name() << " Default value type does not match option type\n";
                return false;
            }

            // return ((has_short_option() || has_long_option()) &&
            //        std::holds_alternative<std::nullopt_t>(_default_value) == false &&
            //        !(is_mandatory() && std::holds_alternative<bool>(_default_value)));

            return true;
        }
        return _valid;
    }

    bool matches_long(std::string option) const {
        if (has_long_option() && (option.find(get_long_option()) == 0))
            return true;
        else
            return false;
    }

    bool matches_short(char option) const {
        if (has_short_option() && (option == get_short_option()))
            return true;
        else
            return false;
    }

    bool consume(parse_context& ctxt, std::vector<std::string>& args, size_t& pos) const {
        auto it = base::find(args[pos], '=');
        std::string value;
        bool holdsPotentialMoreOptions = false;
        if (it != args[pos].end()) {
            std::copy(it + 1, args[pos].end(), std::back_inserter(value));
        }
        if (std::holds_alternative<bool>(_type_indicator)) {
            ctxt._parsed.insert(get_name(), true);
            ctxt.remove_from_missing_mandatory_options(get_name());
            holdsPotentialMoreOptions = true;
        } else {
            if (value.empty() && args.size() <= pos + 1) {
                std::stringstream err;
                err << "Missing option value for option " << *this;
                ctxt._parsed.add_error(err.str(), true);
            } else {
                if (value.empty()) {
                    value = args[++pos];
                }
                if (std::holds_alternative<float>(_type_indicator) || std::holds_alternative<double>(_type_indicator)) {
                    try {
                        ctxt._parsed.insert(get_name(), std::stof(value));
                        ctxt.remove_from_missing_mandatory_options(get_name());
                    } catch (const std::invalid_argument& ex) {
                        std::stringstream err;
                        err << "Could not parse '" << value << "' for option '" << get_name()
                            << "' as expected float. Error: " << ex.what();
                        ctxt._parsed.add_error(err.str(), true);
                    }
                } else if (std::holds_alternative<int>(_type_indicator)) {
                    try {
                        ctxt._parsed.insert(get_name(), std::stoi(value));
                        ctxt.remove_from_missing_mandatory_options(get_name());
                    } catch (const std::invalid_argument& ex) {
                        std::stringstream err;
                        err << "Could not parse '" << value << "' for option '" << get_name()
                            << "' as expected integer type. Error: " << ex.what();
                        ctxt._parsed.add_error(err.str(), true);
                    }
                } else {
                    ctxt._parsed.insert(get_name(), value);
                    ctxt.remove_from_missing_mandatory_options(get_name());
                }
            }
        }
        return holdsPotentialMoreOptions;
    }

   private:
    std::optional<char> _short_option;
    std::optional<std::string> _long_option;
    std::string _option_name;
    std::optional<std::string> _option_description;
    T_strict_option_type _default_value;
    T_strict_option_type _type_indicator;
    bool _valid;
    bool _mandatory;
};

/*
    Command line parser. Tieing it all together.

    Consists ot multiple cl_options. And then can parse
    command line arguments and genereates an argparse_result
    as result
*/
class argparser {
   public:
    argparser(std::string app_name) : _fail_on_unknown(false), _app_name(app_name), _options(){};
    ~argparser() = default;

    std::string get_app_name() const { return _app_name; }

    template <typename T>
    cl_option& add_option(std::string option_name) {
        if (base::find_if(_options, [&option_name](auto& opt) { return opt.get_name() == option_name; }) !=
            _options.end()) {
            throw std::logic_error("Trying to add multiple options with name " + option_name);
        }
        _options.emplace_back(cl_option{option_name});
        return _options.back().set_type<T>();
    }

    cl_option& add_flag(std::string option_name) { return add_option<bool>(option_name); }

    argparse_result parse(int argc, char** argv) {
        std::vector<std::string> args;
        for (int i = 0; i < argc; ++i) args.push_back(std::string(argv[i]));

        return parse(args);
    }

    argparse_result parse(std::vector<std::string>& args) {
        parse_context ctxt{_options, args};

        if (!all_options_valid()) {
            throw std::logic_error("Trying to parse while not all options added are valid");
        }

        try {
            for (auto& opt : _options) {
                if (opt.is_mandatory()) {
                    ctxt._missing_mandatory_options.push_back(opt.get_name());
                }
                if (opt.has_default_value()) {
                    ctxt._parsed.insert(opt.get_name(), opt.get_default_value());
                }
            }

            for (size_t i = 1; i < args.size(); ++i) {
                if (args[i].rfind("--", 0) == 0) {
                    handle_potential_long_option(ctxt, args, i);
                } else if (args[i].rfind("-", 0) == 0) {
                    handle_potential_short_option(ctxt, args, i);
                } else {
                    std::stringstream err;
                    err << "Ignored non-option " << args[i];
                    ctxt._parsed.add_error(err.str());
                }
            }

            if (ctxt.all_mandatories_found() == false) {
                std::stringstream err;
                err << "The following mandatory parameters are missing " << ctxt.get_missing_mandatories();
                ctxt._parsed.add_error(err.str(), true);
            }
        } catch (const std::exception& ex) {
            std::stringstream err;
            err << "Caught exception during parsing " << ex.what();
            ctxt._parsed.add_error(err.str(), true);
        }

        return ctxt._parsed;
    }

    void print_help(std::ostream& os, const std::vector<std::string>* errors = nullptr) {
        if (!all_options_valid()) {
            throw std::logic_error("Trying to print help while not all options added are valid");
        }
        base::sort(_options);
        if (errors != nullptr && !errors->empty()) {
            os << "Errors while parsing commandline: \n";
            for (auto& error : *errors) {
                os << "* " << error << "\n";
            }
            os << "\n";
        }
        os << "Usage:\n" << get_app_name();
        for (auto& opt : _options) {
            os << (opt.is_mandatory() ? " " : " [");
            bool has_both_options = opt.has_short_option() && opt.has_long_option();
            if (opt.has_short_option()) os << "-" << opt.get_short_option();
            if (has_both_options) os << "|";
            if (opt.has_long_option()) os << "--" << opt.get_long_option();
            if (!std::holds_alternative<bool>(opt.get_type())) os << " <" << opt.get_name() << ">";
            os << (opt.is_mandatory() ? "" : "]");
        }
        os << "\n\nParameters:\n";
        std::vector<std::stringstream> params;
        for (auto& opt : _options) {
            params.push_back(std::stringstream{});
            bool has_both_options = opt.has_short_option() && opt.has_long_option();
            if (opt.has_short_option()) params.back() << "-" << opt.get_short_option();
            if (has_both_options) params.back() << " | ";
            if (opt.has_long_option()) params.back() << "--" << opt.get_long_option();
            if (!std::holds_alternative<bool>(opt.get_type())) params.back() << " <" << opt.get_name() << ">";
        }
        size_t max = 0;
        for (auto& paramstr : params) {
            if (paramstr.str().size() > max) max = paramstr.str().size();
        }

        int i = -1;
        for (auto& opt : _options) {
            ++i;
            if (opt.has_description()) {
                size_t gap = max - params[i].str().size();
                std::string gapstr(gap, ' ');
                params[i] << gapstr << " : " << opt.get_description();
            }
            os << params[i].str() << "\n";
        }
    }

    std::vector<cl_option> get_options() const { return _options; }

    std::string get_invalidity_reason() const {
        std::stringstream err;

        if (base::count_if(_options, [](auto& opt) { return opt.is_valid(); }) != (int)_options.size()) {
            const auto& it = base::find_if(_options, [](auto& opt) { return !opt.is_valid(); });
            err << "There are invalid options. First invalid option found: " << *it;
            return err.str();
        }

        std::vector<char> short_options;
        std::vector<std::string> long_options;

        for (auto& opt : _options) {
            if (opt.has_short_option()) short_options.push_back(opt.get_short_option());
            if (opt.has_long_option()) long_options.push_back(opt.get_long_option());
        }

        base::sort(short_options);
        base::sort(long_options);

        auto same_short = base::adjacent_find(short_options);
        if (same_short != short_options.end()) {
            err << "There are multiple short_options with same name. First instance found: '" << *same_short << "'";
            return err.str();
        }

        auto same_long = base::adjacent_find(long_options);
        if (same_long != long_options.end()) {
            err << "There are multiple long_options with same name. First instance found: '" << *same_long << "'";
            return err.str();
        }

        return err.str();
    }

    void fail_on_unknown(bool fail) { _fail_on_unknown = fail; }

    bool all_options_valid() const { return get_invalidity_reason().empty(); }

    // cl_parser.add_parameters("words", "List of words");

   private:
    void handle_potential_long_option(parse_context& ctxt, std::vector<std::string>& args, size_t& pos) {
        bool found = false;
        std::string param{};
        std::copy(args[pos].begin() + 2, args[pos].end(), std::back_inserter(param));
        for (auto& opt : ctxt._options) {
            if (opt.matches_long(param)) {
                found = true;
                (void)opt.consume(ctxt, args, pos);
                break;
            }
        }
        if (!found && _fail_on_unknown) {
            std::stringstream err;
            err << "Unknown option " << param;
            ctxt._parsed.add_error(err.str());
        }
    }

    void handle_potential_short_option(parse_context& ctxt, std::vector<std::string>& args, size_t& pos) {
        bool found = false;
        bool continueLookingForShortOptions = true;
        std::string param{};
        std::copy(args[pos].begin() + 1, args[pos].end(), std::back_inserter(param));
        size_t i = 0;
        while (continueLookingForShortOptions && param.size() > i) {
            for (auto& opt : ctxt._options) {
                if (opt.matches_short(param[i])) {
                    found = true;
                    continueLookingForShortOptions = opt.consume(ctxt, args, pos);
                    break;
                }
            }
            if (!found && _fail_on_unknown) {
                std::stringstream err;
                err << "Unknown option " << (char)param[i];
                ctxt._parsed.add_error(err.str(), true);
                found = true;
            }
            ++i;
        }
    }

    bool _fail_on_unknown;
    std::string _app_name;
    std::vector<cl_option> _options;
};

}  // namespace base

namespace std {
inline std::ostream& operator<<(std::ostream& os, const base::T_strict_option_type& val) {
    std::visit(
        [&os](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                os << arg;
            else if constexpr (std::is_same_v<T, float>)
                os << arg;
            else if constexpr (std::is_same_v<T, double>)
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
}  // namespace std

namespace base {

std::ostream& operator<<(std::ostream& os, const cl_option& opt) {
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

inline std::ostream& operator<<(std::ostream& os, const argparse_result& parse_result) {
    os << "Parse result: " << (parse_result.success() ? "success" : "failed") << "\n";
    os << "Parsed options: " << parse_result._parsed_options << "\n";
    if (parse_result._errors.size() > 0) os << "Parse errors: " << parse_result._errors << "\n";
    return os;
}

}  // namespace base
