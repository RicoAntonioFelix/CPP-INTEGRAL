/*  Copyright(c) 2015, Rico Antonio Felix. All rights reserved.
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *      1. The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software
 *      in a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *
 *      2. Altered source versions must be plainly marked as such, and must not
 *      be misrepresented as being the original software.
 *
 *      3. This notice may not be removed or altered from any source
 *      distribution.
 */

 /**
  * @author Rico Antonio Felix <ricoantoniofelix@yahoo.com>
  */

#include "Integral.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstring>

namespace csp = compuSUAVE_Professional;

TEST_CASE( "Default constructor must create an object with a value of zero", "[Integral<T>]" )
{
    csp::Integral<int> value;

    REQUIRE( 0 == int(value) );
}

TEST_CASE( "Constructor must create an object with the specified value", "[Integral<T>]" )
{
    csp::Integral<int> value{7};

    REQUIRE( 7 == int(value) );
}

TEST_CASE( "Copy constructor must create a copy of the specified object with the same value", "[Integral<T>]" )
{
    csp::Integral<int> value{7};
    csp::Integral<int> copy{value};

    REQUIRE( 7 == int(copy) );
}

SCENARIO( "Given a value that can be converted to an object of type Integral<T>" )
{
    WHEN( "Object is of type Integral<int> and value is of type double" )
    {
        THEN( "An object should be created with the value truncated" )
        {
            csp::Integral<int> object{7.7};

            REQUIRE( 7 == int(object) );
        }
    }
}

SCENARIO( "Given a C-String that can be parsed into an integral value" )
{
    WHEN( "C-String represents a decimal value" )
    {
        THEN( "An object should be created equal to such value" )
        {
            csp::Integral<int> object{"137"};

            REQUIRE( 137 == int(object) );
        }
    }

    WHEN( "C-String represents an octal value" )
    {
        THEN( "An object should be created equal to such value" )
        {
            csp::Integral<int> object{"017"};

            REQUIRE( 15 == int(object) );
        }
    }

    WHEN( "C-String represents a hexadecimal value" )
    {
        THEN( "An object should be created equal to such value" )
        {
            csp::Integral<int> object{"0x64"};

            REQUIRE( 100 == int(object) );
        }
    }

    WHEN( "C-String represents a binary value" )
    {
        THEN( "An object should be created equal to such value" )
        {
            csp::Integral<int> object{"0b1111"};

            REQUIRE( 15 == int(object) );
        }
    }

    WHEN( "C-String represents a semi-parsable value" )
    {
        THEN( "An object should be created equal to the parsable part of the C-String" )
        {
            csp::Integral<int> object{"7SEVEN"};

            REQUIRE( 7 == int(object) );
        }
    }

    WHEN( "C-String represents a non-parsable value" )
    {
        THEN( "An object should be created equal to zero" )
        {
            csp::Integral<int> object{"SEVEN"};

            REQUIRE( 0 == int(object) );
        }
    }
}

TEST_CASE( "When one object is assigned to the other both should contain the same value", "[Integral<T>]" )
{
    csp::Integral<int> value1{7};
    csp::Integral<int> value2;

    REQUIRE( 7 == int(value1) );
    REQUIRE( 0 == int(value2) );

    value2 = value1;

    REQUIRE( value2 == value1 );
    REQUIRE( 7 == int(value2) );
}

TEST_CASE( "When an object is assigned to a floating-point value truncation takes place", "[Integral<T>]" )
{
    csp::Integral<int> value;

    REQUIRE( 0 == int(value) );

    value = 7.7;

    REQUIRE( 7 == int(value) );
}

SCENARIO( "Given two objects" )
{
    WHEN( "Added together" )
    {
        THEN( "The sum of the objects is produced" )
        {
            csp::Integral<int> value1{1};
            csp::Integral<int> value2{1};

            auto result = ( value1 + value2 );

            REQUIRE( 2 == int(result) );
        }
    }

    WHEN( "Subtracted from each together" )
    {
        THEN( "The difference of the objects is produced" )
        {
            csp::Integral<int> value1{1};
            csp::Integral<int> value2{1};

            auto result = ( value1 - value2 );

            REQUIRE( 0 == int(result) );
        }
    }

    WHEN( "Multipled together" )
    {
        THEN( "The product of the objects is produced" )
        {
            csp::Integral<int> value1{1};
            csp::Integral<int> value2{7};

            auto result = ( value1 * value2 );

            REQUIRE( 7 == int(result) );
        }
    }

    WHEN( "Divided from each together" )
    {
        THEN( "The quotient of the objects is produced" )
        {
            csp::Integral<int> value1{7};
            csp::Integral<int> value2{2};

            auto result = ( value1 / value2 );

            REQUIRE( 3 == int(result) );
        }
    }

    WHEN( "Modulo is applied to them" )
    {
        THEN( "The remainder is produced" )
        {
            csp::Integral<int> value1{7};
            csp::Integral<int> value2{2};

            auto result = ( value1 % value2 );

            REQUIRE( 1 == int(result) );
        }
    }
}

SCENARIO( "Given an object")
{
    WHEN( "Pre-increment operator is applied" )
    {
        THEN( "Object should produce an object with a value increased by one")
        {
            csp::Integral<long> object{1L};

            auto produced = ( ++object );

            REQUIRE( produced == object );
            REQUIRE( 2 == int(produced) );
            REQUIRE( 2 == int(object) );
        }
    }

    WHEN( "Post-increment operator is applied" )
    {
        THEN( "Object should produce an object with pre-incremented value and object should be incremented" )
        {
            csp::Integral<long> object{1L};

            auto produced = ( object++ );

            REQUIRE( produced != object );
            REQUIRE( 1 == int(produced) );
            REQUIRE( 2 == int(object) );
        }
    }

    WHEN( "Pre-decrement operator is applied" )
    {
        THEN( "Object should produce an object with a value decreased by one" )
        {
            csp::Integral<long> object{1L};

            auto produced = ( --object );

            REQUIRE( produced == object );
            REQUIRE( 0 == int(produced) );
            REQUIRE( 0 == int(object) );
        }
    }

    WHEN( "Post-increment operator is applied" )
    {
        THEN( "Object should produce an object with pre-decremented value and object should be decremented" )
        {
            csp::Integral<long> object{1L};

            auto produced = ( object-- );

            REQUIRE( produced != object );
            REQUIRE( 1 == int(produced) );
            REQUIRE( 0 == int(object) );
        }
    }
}

TEST_CASE( "When negation operator is applied on an object the sign of its value should not change", "[Integral<T>]" )
{
    csp::Integral<short> object{7};

    auto result = ( -object );

    REQUIRE( 7 == int(object) );
    REQUIRE(-7 == int(result) );
}

TEST_CASE( "Test inequality operators", "[Integral<T>]" )
{
    SECTION( "Test equals operator" )
    {
        csp::Integral<int> value1{7};
        csp::Integral<int> value2{7};

        REQUIRE( value1 == value2 );
    }

    SECTION( "Test not-equals operator" )
    {
        csp::Integral<int> value1{7};
        csp::Integral<int> value2{1};

        REQUIRE( value1 != value2 );
    }

    SECTION( "Test less-than operator" )
    {
        csp::Integral<int> value1{1};
        csp::Integral<int> value2{7};

        REQUIRE( value1 < value2 );
    }

    SECTION( "Test greater-than operator" )
    {
        csp::Integral<int> value1{7};
        csp::Integral<int> value2{1};

        REQUIRE( value1 > value2 );
    }

    SECTION( "Test less-than or equal-to operator" )
    {
        csp::Integral<int> value1{7};
        csp::Integral<int> value2{7};

        REQUIRE( value1 <= value2 );
    }

    SECTION( "Test greater-than or equal-to operator" )
    {
        csp::Integral<int> value1{10};
        csp::Integral<int> value2{7};

        REQUIRE( value1 >= value2 );
    }
}

TEST_CASE( "Test conversion operations", "[Integral<T>]" )
{
    SECTION( "Test conversion to C-String" )
    {
        csp::Integral<int> value{7};

        const char* number = value;

        bool test = ( strcmp(number, "7") == 0 );

        REQUIRE( true == test );
    }

    SECTION( "Test conversion to std::string object" )
    {
        csp::Integral<int> value{7};

        std::string number = value;

        bool test = ( number == "7" );

        REQUIRE( true == test );
    }

    SECTION( "Test conversion to char" )
    {
        csp::Integral<int> value{51};

        char number = value;

        REQUIRE( '3' == number );
    }

    SECTION( "Test conversion to int" )
    {
        csp::Integral<int> value{7};

        int number = value;

        REQUIRE( 7 == number );
    }

    SECTION( "Test conversion to double" )
    {
        csp::Integral<int> value{7};

        double number = value;

        REQUIRE( 7.0 == number );
    }
}

TEST_CASE( "Test base conversion operations", "[Integral<T>]" )
{
    SECTION( "Test toRadix method" )
    {
        csp::Integral<long long> value{12LL};

        auto base4 = value.toRadix(4);

        bool test = ( strcmp(base4, "30") == 0 );

        REQUIRE( true == test );
    }

    SECTION( "Test hex method" )
    {
        csp::Integral<long long> value{12LL};

        auto base16 = value.hex();

        bool test = ( strcmp(base16, "c") == 0 );

        REQUIRE( true == test );
    }

    SECTION( "Test oct method" )
    {
        csp::Integral<long long> value{12LL};

        auto base8 = value.oct();

        bool test  = ( strcmp(base8, "14") == 0 );

        REQUIRE( true == test );
    }

    SECTION( "Test bin method" )
    {
        csp::Integral<long long> value{12LL};

        auto base2 = value.bin();

        bool test = ( strcmp(base2, "1100") == 0 );

        REQUIRE( true == test );
    }
}

TEST_CASE( "Test min and max functions to obtain larger or lesser object", "[Integral<T>]" )
{
    csp::Integral<long long> value1{12LL};
    csp::Integral<long long> value2{24LL};

    SECTION( "Test min function" )
    {
        auto lesser = min(value1, value2);

        REQUIRE( 12 == long(lesser) );
    }

    SECTION( "Test max function" )
    {
        auto lesser = max(value1, value2);

        REQUIRE( 24 == long(lesser) );
    }
}

TEST_CASE( "Test numerical property methods", "[Integral<T>]")
{
    csp::Integral<long long> value{12LL};

    SECTION( "Test odd method" )
    {
        bool test = value.odd();

        REQUIRE( false == test );
    }

    SECTION( "Test even method" )
    {
        bool test = value.even();

        REQUIRE( true == test );
    }
}

TEST_CASE( "Test user defined literals", "[Integral<T>]" )
{
    using namespace compuSUAVE_Professional;

    SECTION( "Test unsigned char type" )
    {
        auto object = 65_cspiuc;

        REQUIRE( 'A' == char(object) );
    }

    SECTION( "Test unsigned short type" )
    {
        auto object = 97_cspius;

        REQUIRE( 'a' == short(object) );
    }

    SECTION( "Test unsigned int type" )
    {
        auto object = 0_cspiui;

        REQUIRE( '\0' == unsigned(object) );
    }

    SECTION( "Test unsigned long type" )
    {
        auto object = 100_cspiul;

        REQUIRE( 100 == long(object) );
    }

    SECTION( "Test unsigned long long type" )
    {
        auto object = 12345_cspiull;

        REQUIRE( 12345 == long(object) );
    }
}
