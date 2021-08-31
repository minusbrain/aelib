/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
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
    EXPECT_TRUE(parsed1.has_option("verbose"));
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
    EXPECT_TRUE(parsed1.has_option("verbose"));
    EXPECT_FALSE(std::get<bool>(parsed2["verbose"]));
}

// std::cout << parsed.get_errors() << "\n";
