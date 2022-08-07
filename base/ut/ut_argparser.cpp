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
#include <base/argparser.h>

#include <cassert>
#include <stdexcept>
#include <variant>

#include "gtest/gtest.h"

using base::argparser;

TEST(Argparser, ConstructWithName_ExpectCorrectName) {
    argparser parser{"bla"};
    EXPECT_EQ(std::string("bla"), parser.get_app_name());
}

TEST(Argparser, Construct_ExpectValid) {
    argparser parser{"bla"};
    EXPECT_TRUE(parser.all_options_valid());
}

TEST(Argparser, ShortStringParameter_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<std::string>("configfile").short_option('c');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "-c", "config.cfg"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("configfile"));
    EXPECT_EQ(std::get<std::string>(parsed1["configfile"]), std::string("config.cfg"));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("configfile"));
    EXPECT_THROW(std::get<std::string>(parsed2["configfile"]), std::exception);
}

TEST(Argparser, LongStringParameter_ParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<std::string>("configfile").long_option("cfg");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "--cfg", "config.cfg"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("configfile"));
    EXPECT_EQ(std::get<std::string>(parsed1["configfile"]), std::string("config.cfg"));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("configfile"));
    EXPECT_THROW(std::get<std::string>(parsed2["configfile"]), std::exception);
}

TEST(Argparser, ShortFlag_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<bool>("verbose").short_option('v');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "-v"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("verbose"));
    EXPECT_TRUE(std::get<bool>(parsed1["verbose"]));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_TRUE(parsed2.has_option("verbose"));
    EXPECT_FALSE(std::get<bool>(parsed2["verbose"]));
}

TEST(Argparser, LongFlag_ParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<bool>("verbose").long_option("verbose");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "--verbose"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("verbose"));
    EXPECT_TRUE(std::get<bool>(parsed1["verbose"]));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_TRUE(parsed2.has_option("verbose"));
    EXPECT_FALSE(std::get<bool>(parsed2["verbose"]));
}

TEST(Argparser, ShortFlagConvenienceOption_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_flag("verbose").short_option('v');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "-v"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("verbose"));
    EXPECT_TRUE(parsed1.is_flag_set("verbose"));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_TRUE(parsed2.has_option("verbose"));
    EXPECT_FALSE(parsed2.is_flag_set("verbose"));
}

TEST(Argparser, LongFlagConvenienceOption_ParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_flag("verbose").long_option("verbose");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "--verbose"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("verbose"));
    EXPECT_TRUE(parsed1.is_flag_set("verbose"));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_TRUE(parsed2.has_option("verbose"));
    EXPECT_FALSE(parsed2.is_flag_set("verbose"));
}

TEST(Argparser, ShortInt_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<int>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "-n", "42"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("number"));
    EXPECT_EQ(42, std::get<int>(parsed1["number"]));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<int>(parsed2["number"]), std::exception);
}

TEST(Argparser, LongInt_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<int>("number").long_option("number");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "--number", "42"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("number"));
    EXPECT_EQ(42, std::get<int>(parsed1["number"]));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<int>(parsed2["number"]), std::exception);
}

TEST(Argparser, ShortFloat_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "-n", "42.69"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("number"));
    EXPECT_FLOAT_EQ(42.69f, std::get<float>(parsed1["number"]));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, LongFloat_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option<float>("number").long_option("number");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args1{"test", "--number", "42.69"};
    auto parsed1 = parser.parse(args1);

    EXPECT_TRUE(parsed1.success());
    EXPECT_TRUE(parsed1.has_option("number"));
    EXPECT_FLOAT_EQ(42.69f, std::get<float>(parsed1["number"]));

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_TRUE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingMandatoryShortOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n').mandatory();

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingMandatoryLongOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").long_option("number").mandatory();

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingShortOptionValue_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "-n"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingLongOptionValue_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").long_option("number");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "--number"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingShortOptionValueButSecondOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n');
    parser.add_option<bool>("option").short_option('o');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "-n", "-o"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingLongOptionValueButSecondOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").long_option("number");
    parser.add_option<bool>("option").long_option("option");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "--number", "--option"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, PrintHelpOutput_VerifyContent) {
    // Expected Output
    // Usage:
    // test -e <email> --pos <position> [-n|--number <number>] [--option]

    // Parameters:
    // -e <email>             : A mandatory email to be used
    // --pos <position>       : Mandatory position
    // -n | --number <number> : Provide the floating point number to be used by the tool
    // --option               : Wether or not an option should be active

    std::string expected{
        "Usage:\ntest -e <email> --pos <position> [-n|--number <number>] [--option]\n\nParameters:\n-e <email>         "
        "    : A mandatory email to be used\n--pos <position>       : Mandatory position\n-n | --number <number> : "
        "Provide the floating point number to be used by the tool\n--option               : Wether or not an option "
        "should be active\n"};

    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n').long_option("number").description(
        "Provide the floating point number to be used by the tool");
    parser.add_option<bool>("option").long_option("option").description("Wether or not an option should be active");
    parser.add_option<int>("position").long_option("pos").description("Mandatory position").mandatory();
    parser.add_option<std::string>("email").short_option('e').mandatory().description("A mandatory email to be used");

    EXPECT_TRUE(parser.all_options_valid());

    std::stringstream strstr;
    parser.print_help(strstr);
    EXPECT_EQ(expected, strstr.str());
}

TEST(Argparser, AlternativeOptionValueFormatShortOption_SimpleParserGettingCorrectInput_ExpectSuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n=23.45"};
    auto parsed = parser.parse(args);

    EXPECT_TRUE(parsed.success());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_FLOAT_EQ(23.45, std::get<float>(parsed["number"]));
}

TEST(Argparser, AlternativeOptionValueFormatLongOption_SimpleParserGettingCorrectInput_ExpectSuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<float>("number").long_option("number");

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "--number=23.45"};
    auto parsed = parser.parse(args);

    EXPECT_TRUE(parsed.success());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_FLOAT_EQ(23.45, std::get<float>(parsed["number"]));
}

TEST(Argparser, InvalidShortOptionName_SimpleParser_ExpectNotValid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<float>("number").short_option('='), std::exception);

    EXPECT_FALSE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n=23.45"};
    EXPECT_THROW(parser.parse(args), std::exception);
}

TEST(Argparser, InvalidLongOptionName_SimpleParser_ExpectNotValid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<float>("number").long_option("="), std::exception);

    EXPECT_FALSE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n=23.45"};
    EXPECT_THROW(parser.parse(args), std::exception);
}

TEST(Argparser,
     AnotherAlternativeOptionValueFormatShortOption_SimpleParserGettingCorrectInput_ExpectSuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option<int>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n8"};
    auto parsed = parser.parse(args);

    EXPECT_TRUE(parsed.success());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_EQ(8, std::get<int>(parsed["number"]));
}

TEST(Argparser, AutoDeriveOptionTypeString) {
    argparser parser{"test"};
    auto& opt = parser.add_option<std::string>("number").short_option('n').default_value(std::string{"Ten"});

    EXPECT_TRUE(std::holds_alternative<std::string>(opt.get_type()));
    EXPECT_TRUE(parser.all_options_valid());
}

TEST(Argparser, AutoDeriveOptionTypeFloat) {
    argparser parser{"test"};
    auto& opt = parser.add_option<float>("number").short_option('n').default_value(12.34f);

    EXPECT_TRUE(std::holds_alternative<float>(opt.get_type()));
    EXPECT_TRUE(parser.all_options_valid());
}

TEST(Argparser, AutoDeriveOptionTypeInt) {
    argparser parser{"test"};
    auto& opt = parser.add_option<int>("number").short_option('n').default_value(42);

    EXPECT_TRUE(std::holds_alternative<int>(opt.get_type()));
    EXPECT_TRUE(parser.all_options_valid());
}

TEST(Argparser, DisallowMultipleOptionsWithSameName) {
    argparser parser{"test"};
    parser.add_option<int>("number").short_option('n').default_value(42);
    EXPECT_THROW(parser.add_option<int>("number").short_option('i').default_value(42), std::exception);

    // As add_option failed/threw error no invalid option has been actually added to parser
    EXPECT_TRUE(parser.all_options_valid());
}

TEST(Argparser, DisallowMultipleOptionsWithSameShortOption) {
    argparser parser{"test"};
    parser.add_option<int>("number").short_option('n').default_value(42);
    parser.add_option<int>("another_number_with_same_shortoption").short_option('n').default_value(42);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, DisallowMultipleOptionsWithSameLongOption) {
    argparser parser{"test"};
    parser.add_option<int>("number").long_option("number").default_value(42);
    parser.add_option<int>("another_number_with_same_longoption").long_option("number").default_value(42);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, SetDefaultToIntWhileTypeIsString_ExpectThrowAndInvalid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<std::string>("number").long_option("number").default_value(42), std::logic_error);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, SetDefaultToFloatWhileTypeIsString_ExpectThrowAndInvalid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<std::string>("number").long_option("number").default_value(42.56f),
                 std::logic_error);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, SetDefaultToStringWhileTypeIsInt_ExpectThrowAndInvalid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<int>("number").long_option("number").default_value("Hello"), std::logic_error);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, SetDefaultToFloatWhileTypeIsInt_ExpectThrowAndInvalid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<int>("number").long_option("number").default_value(42.56f), std::logic_error);

    EXPECT_FALSE(parser.all_options_valid());
}
TEST(Argparser, SetDefaultToStringWhileTypeIsFloat_ExpectThrowAndInvalid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<float>("number").long_option("number").default_value("Hello"), std::logic_error);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, SetDefaultToIntWhileTypeIsFloat_ExpectThrowAndInvalid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option<float>("number").long_option("number").default_value(42), std::logic_error);

    EXPECT_FALSE(parser.all_options_valid());
}

TEST(Argparser, TryToParseStringAsFloat_ExpectError) {
    argparser parser{"test"};
    parser.add_option<float>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n", "Test"};
    auto parsed = parser.parse(args);

    EXPECT_FALSE(parsed.success());
    EXPECT_FALSE(parsed.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed["number"]), std::exception);
}

TEST(Argparser, TryToParseStringAsInt_ExpectError) {
    argparser parser{"test"};
    parser.add_option<int>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n", "Test"};
    auto parsed = parser.parse(args);

    EXPECT_FALSE(parsed.success());
    EXPECT_FALSE(parsed.has_option("number"));
    EXPECT_THROW(std::get<int>(parsed["number"]), std::exception);
}

TEST(Argparser, TryToParseArgcArgv_ExpectOk) {
    argparser parser{"test"};
    parser.add_option<int>("number").short_option('n');

    EXPECT_TRUE(parser.all_options_valid());

    int argc = 3;
    char arg1[5] = "test";
    char arg2[3] = "-n";
    char arg3[2] = "5";
    char* argv[3] = {arg1, arg2, arg3};

    auto parsed = parser.parse(argc, argv);

    EXPECT_TRUE(parsed.success());
    EXPECT_EQ(0, parsed.get_errors().size());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_EQ(5, std::get<int>(parsed["number"]));
}

TEST(Argparser, ReadmeExample_ExpectNoErrors) {
    std::vector<std::string> args{"/bin/myapp", "--cfg", "/home/me/.myapp", "-j8"};

    try {
        // Construct a parser for program 'myapp'
        argparser parser{"myapp"};
        // Prepare parser with intended options
        parser.add_option<std::string>("configfile")
            .short_option('c')
            .long_option("cfg")
            .default_value(std::string("/etc/myapp.conf"))
            .description("Location of configuration file to use");
        parser.add_option<bool>("verbose").short_option('v').long_option("verbose").description(
            "Activate more verbose output");
        parser.add_option<int>("threads").short_option('j').mandatory().description(
            "Number of threads that shall be used for processing");

        // Checks for any logical errors in defined options
        assert(parser.all_options_valid());

        // Parse command line input
        auto parsed_args = parser.parse(args);

        if (!parsed_args.success()) {
            parser.print_help(std::cout, &parsed_args.get_errors());
            return;
        }

        // std::cout << "Using configfile: " << parsed_args.get<std::string>("configfile") << std::endl;
        // std::cout << "All parsed parameters: " << parsed_args.get_options() << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Parsing error: " << ex.what() << std::endl;
    }
}
