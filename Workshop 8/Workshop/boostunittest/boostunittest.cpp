
#define BOOST_TEST_MODULE BoostTestMyApp

#include <boost/test/included/unit_test.hpp>
#include "mymath.hpp"
#include "log.hpp"

#include <sstream>
#include <string>
#include <stdexcept>

using namespace myMath;

// Boost Test Framework does not show the output of std::cout by default when running tests.
// if you want to see the output when running the tests, add the following command line 
// argument to the test runner:
// Refer to: https://www.boost.org/doc/libs/latest/libs/test/doc/html/boost_test/utf_reference/rt_param_reference/log_level.html
//
// Visual studio specific:
// Project -> Properties -> Debugging -> Command Arguments -> --log_level=all 
// 
// Linux specific:
// ./boostunittest --log_level=all

namespace BoostTestMyApp
{
    //
    // ---------- Operating System ----------
    //

    BOOST_AUTO_TEST_CASE(DetectsOperatingSystemOutput)
    {
        LogTargetOperatingSystem();

        // Capture std::cout
        std::ostringstream capturedOutput;
        std::streambuf* oldBuffer = std::cout.rdbuf(capturedOutput.rdbuf());

        LogTargetOperatingSystem();

        std::cout.rdbuf(oldBuffer);

        std::string output = capturedOutput.str();

#if defined(_WIN32) && defined(_WIN64)
        BOOST_CHECK_NE(output.find("Windows"), std::string::npos);

#elif defined(_WIN32)
        BOOST_CHECK_NE(output.find("Windows 32-bit"), std::string::npos);

#elif defined(__APPLE__) || defined(__MACH__)
        BOOST_CHECK_NE(output.find("macOS"), std::string::npos);

#elif defined(__linux__)
        BOOST_CHECK_NE(output.find("Linux"), std::string::npos);

#elif defined(__unix__)
        BOOST_CHECK_NE(output.find("Unix"), std::string::npos);

#elif defined(_POSIX_VERSION)
        BOOST_CHECK_NE(
            output.find("POSIX-compliant OS"),
            std::string::npos
        );

#else
        BOOST_CHECK_NE(
            output.find("Unknown OS"),
            std::string::npos
        );
#endif
    }


    //
    // ---------- Compiler ----------
    //

    BOOST_AUTO_TEST_CASE(DetectsCompilerOutput)
    {
        LogTargetCompiler();

        std::ostringstream capturedOutput;
        std::streambuf* oldBuffer = std::cout.rdbuf(capturedOutput.rdbuf());

        LogTargetCompiler();

        std::cout.rdbuf(oldBuffer);

        std::string output = capturedOutput.str();

#if defined(__clang__)

        BOOST_CHECK_NE(output.find("Clang version"), std::string::npos);

#elif defined(__GNUC__) || defined(__GNUG__)

        BOOST_CHECK_NE(output.find("GCC version"), std::string::npos);

#elif defined(_MSC_FULL_VER)

        BOOST_CHECK_NE(output.find("MSVC version"), std::string::npos);

#else

        BOOST_CHECK_NE(output.find("Unknown compiler"), std::string::npos);

#endif
    }


    //
    // ---------- C++ Standard ----------
    //

    BOOST_AUTO_TEST_CASE(DetectsCxxVersionOutput)
    {
        LogTargetCxxStandard();

        std::ostringstream capturedOutput;
        std::streambuf* oldBuffer = std::cout.rdbuf(capturedOutput.rdbuf());

        LogTargetCxxStandard();

        std::cout.rdbuf(oldBuffer);

        std::string output = capturedOutput.str();

#if __cplusplus >= 202400L

        BOOST_CHECK_NE(
            output.find("C++26 or later"),
            std::string::npos
        );

#elif __cplusplus == 202302L

        BOOST_CHECK_NE(
            output.find("C++23"),
            std::string::npos
        );

#elif __cplusplus == 202002L

        BOOST_CHECK_NE(
            output.find("C++20"),
            std::string::npos
        );

#elif __cplusplus == 201703L

        BOOST_CHECK_NE(
            output.find("C++17"),
            std::string::npos
        );

#elif __cplusplus == 201402L

        BOOST_CHECK_NE(
            output.find("C++14"),
            std::string::npos
        );

#elif __cplusplus == 201103L

        BOOST_CHECK_NE(
            output.find("C++11"),
            std::string::npos
        );

#else

        BOOST_CHECK_NE(
            output.find("pre C++11"),
            std::string::npos
        );

#endif

        BOOST_CHECK_NE(
            output.find(std::to_string(__cplusplus)),
            std::string::npos
        );
    }


    //
    // ---------- Free Function Tests ----------
    //

    BOOST_AUTO_TEST_CASE(Add_PositiveNumbers)
    {
        BOOST_CHECK_EQUAL(add(2, 3), 5);
    }

    BOOST_AUTO_TEST_CASE(Add_NegativeNumbers)
    {
        BOOST_CHECK_EQUAL(add(-2, -3), -5);
    }

    BOOST_AUTO_TEST_CASE(Add_WithZero)
    {
        BOOST_CHECK_EQUAL(add(10, 0), 10);
    }


    BOOST_AUTO_TEST_CASE(Subtract_PositiveNumbers)
    {
        BOOST_CHECK_EQUAL(subtract(10, 4), 6);
    }

    BOOST_AUTO_TEST_CASE(Subtract_NegativeNumbers)
    {
        BOOST_CHECK_EQUAL(subtract(-2, -3), 1);
    }

    BOOST_AUTO_TEST_CASE(Subtract_WithZero)
    {
        BOOST_CHECK_EQUAL(subtract(5, 0), 5);
    }


    BOOST_AUTO_TEST_CASE(Multiply_PositiveNumbers)
    {
        BOOST_CHECK_EQUAL(multiply(3, 4), 12);
    }

    BOOST_AUTO_TEST_CASE(Multiply_NegativeNumbers)
    {
        BOOST_CHECK_EQUAL(multiply(-3, 4), -12);
    }

    BOOST_AUTO_TEST_CASE(Multiply_ByZero)
    {
        BOOST_CHECK_EQUAL(multiply(7, 0), 0);
    }


    BOOST_AUTO_TEST_CASE(Divide_ValidNumbers)
    {
        BOOST_CHECK_EQUAL(divide(8, 2), 4);
    }

    BOOST_AUTO_TEST_CASE(Divide_NegativeNumbers)
    {
        BOOST_CHECK_EQUAL(divide(-10, 5), -2);
    }

    BOOST_AUTO_TEST_CASE(Divide_ByZero_Throws)
    {
        BOOST_CHECK_THROW(
            divide(5, 0),
            std::invalid_argument
        );
    }


    BOOST_AUTO_TEST_CASE(Modulus_ValidNumbers)
    {
        BOOST_CHECK_EQUAL(modulus(10, 3), 1);
    }

    BOOST_AUTO_TEST_CASE(Modulus_NegativeNumbers)
    {
        BOOST_CHECK_EQUAL(modulus(-10, 3), -1);
    }

    BOOST_AUTO_TEST_CASE(Modulus_ByZero_Throws)
    {
        BOOST_CHECK_THROW(
            modulus(10, 0),
            std::invalid_argument
        );
    }


    //
    // ---------- Class Method Tests ----------
    //

    struct MathFunctionsFixture
    {
        MathFunctions math;
    };


    BOOST_FIXTURE_TEST_CASE(Add_UsingClass, MathFunctionsFixture)
    {
        BOOST_CHECK_EQUAL(math.add(5, 5), 10);
    }

    BOOST_FIXTURE_TEST_CASE(Subtract_UsingClass, MathFunctionsFixture)
    {
        BOOST_CHECK_EQUAL(math.subtract(10, 8), 2);
    }

    BOOST_FIXTURE_TEST_CASE(Multiply_UsingClass, MathFunctionsFixture)
    {
        BOOST_CHECK_EQUAL(math.multiply(3, 5), 15);
    }

    BOOST_FIXTURE_TEST_CASE(Divide_UsingClass, MathFunctionsFixture)
    {
        BOOST_CHECK_EQUAL(math.divide(9, 3), 3);
    }

    BOOST_FIXTURE_TEST_CASE(Divide_ByZero_UsingClass_Throws, MathFunctionsFixture)
    {
        BOOST_CHECK_THROW(
            math.divide(1, 0),
            std::invalid_argument
        );
    }

    BOOST_FIXTURE_TEST_CASE(Modulus_UsingClass, MathFunctionsFixture)
    {
        BOOST_CHECK_EQUAL(math.modulus(10, 3), 1);
    }

    BOOST_FIXTURE_TEST_CASE(Modulus_ByZero_UsingClass_Throws, MathFunctionsFixture)
    {
        BOOST_CHECK_THROW(
            math.modulus(10, 0),
            std::invalid_argument
        );
    }

} // namespace BoostTestMyApp

