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

#include <exception>

#include "gtest/gtest.h"

using base::argparser;
using aot = base::argparser_option_type;

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
    parser.add_option("configfile").short_option('c').type(aot::STRING);

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
    parser.add_option("configfile").long_option("cfg").type(aot::STRING);

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
    parser.add_option("verbose").short_option('v').type(aot::FLAG);

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
    parser.add_option("verbose").long_option("verbose").type(aot::FLAG);

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

TEST(Argparser, ShortInt_SimpleParserGettingCorrectInput_ExpectCorrectParsedArguments) {
    argparser parser{"test"};
    parser.add_option("number").short_option('n').type(aot::INT);

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
    parser.add_option("number").long_option("number").type(aot::INT);

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
    parser.add_option("number").short_option('n').type(aot::FLOAT);

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
    parser.add_option("number").long_option("number").type(aot::FLOAT);

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
    parser.add_option("number").short_option('n').type(aot::FLOAT).mandatory();

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingMandatoryLongOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").long_option("number").type(aot::FLOAT).mandatory();

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingShortOptionValue_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").short_option('n').type(aot::FLOAT);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "-n"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingLongOptionValue_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").long_option("number").type(aot::FLOAT);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "--number"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingShortOptionValueButSecondOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").short_option('n').type(aot::FLOAT);
    parser.add_option("option").short_option('o').type(aot::FLAG);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "-n", "-o"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, MissingLongOptionValueButSecondOption_SimpleParserGettingIncorrectInput_ExpectUnsuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").long_option("number").type(aot::FLOAT);
    parser.add_option("option").long_option("option").type(aot::FLAG);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args2{"test", "--number", "--option"};
    auto parsed2 = parser.parse(args2);

    EXPECT_FALSE(parsed2.success());
    EXPECT_FALSE(parsed2.has_option("number"));
    EXPECT_THROW(std::get<float>(parsed2["number"]), std::exception);
}

TEST(Argparser, PrintHelpOutput_VerifyContent) {
    /* Expected Output
    Usage:
    test -e <email> --pos <position> [-n|--number <number>] [--option]

    Parameters:
    -e <email>             : A mandatory email to be used
    --pos <position>       : Mandatory position
    -n | --number <number> : Provide the floating point number to be used by the tool
    --option               : Wether or not an option should be active
    */

    std::string expected{
        "Usage:\ntest -e <email> --pos <position> [-n|--number <number>] [--option]\n\nParameters:\n-e <email>         "
        "    : A mandatory email to be used\n--pos <position>       : Mandatory position\n-n | --number <number> : "
        "Provide the floating point number to be used by the tool\n--option               : Wether or not an option "
        "should be active\n"};

    argparser parser{"test"};
    parser.add_option("number")
        .short_option('n')
        .long_option("number")
        .type(aot::FLOAT)
        .description("Provide the floating point number to be used by the tool");
    parser.add_option("option").long_option("option").type(aot::FLAG).description(
        "Wether or not an option should be active");
    parser.add_option("position").long_option("pos").type(aot::INT).description("Mandatory position").mandatory();
    parser.add_option("email")
        .short_option('e')
        .type(aot::STRING)
        .mandatory()
        .description("A mandatory email to be used");

    EXPECT_TRUE(parser.all_options_valid());

    std::stringstream strstr;
    parser.print_help(strstr);
    EXPECT_EQ(expected, strstr.str());
}

TEST(Argparser, AlternativeOptionValueFormatShortOption_SimpleParserGettingCorrectInput_ExpectSuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").short_option('n').type(aot::FLOAT);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n=23.45"};
    auto parsed = parser.parse(args);

    EXPECT_TRUE(parsed.success());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_FLOAT_EQ(23.45, std::get<float>(parsed["number"]));
}

TEST(Argparser, AlternativeOptionValueFormatLongOption_SimpleParserGettingCorrectInput_ExpectSuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").long_option("number").type(aot::FLOAT);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "--number=23.45"};
    auto parsed = parser.parse(args);

    EXPECT_TRUE(parsed.success());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_FLOAT_EQ(23.45, std::get<float>(parsed["number"]));
}

TEST(Argparser, InvalidShortOptionName_SimpleParser_ExpectNotValid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option("number").short_option('=').type(aot::FLOAT), std::exception);

    EXPECT_FALSE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n=23.45"};
    EXPECT_THROW(parser.parse(args), std::exception);
}

TEST(Argparser, InvalidLongOptionName_SimpleParser_ExpectNotValid) {
    argparser parser{"test"};
    EXPECT_THROW(parser.add_option("number").long_option("=").type(aot::FLOAT), std::exception);

    EXPECT_FALSE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n=23.45"};
    EXPECT_THROW(parser.parse(args), std::exception);
}

TEST(Argparser,
     AnotherAlternativeOptionValueFormatShortOption_SimpleParserGettingCorrectInput_ExpectSuccessfulParsing) {
    argparser parser{"test"};
    parser.add_option("number").short_option('n').type(aot::INT);

    EXPECT_TRUE(parser.all_options_valid());

    std::vector<std::string> args{"test", "-n8"};
    auto parsed = parser.parse(args);

    EXPECT_TRUE(parsed.success());
    EXPECT_TRUE(parsed.has_option("number"));
    EXPECT_EQ(8, std::get<int>(parsed["number"]));
}

// Test
// add_option("bla").default("Hallo");
// Expect type = String
// Same for float und int

// Test
// add_option("name")
// EXPECT_THROW add_option("name")

// Test
// add_option().long_option("bla")
// EXPECT_THROW add_option().long_option("bla")

// Test
// add_option().short_option('b')
// EXPECT_THROW add_option().short_option('b')