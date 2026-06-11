#include <gtest/gtest.h>
#include "mymath.hpp"
#include "log.hpp"
using namespace myMath;  // to avoid repeating myMath::

namespace GUnitTestMyApp
{
    TEST(LibFunctionTests, DetectsOperatingSystemOutput)
    {
        LogTargetOperatingSystem(); // log to console
        // Capture console output
        testing::internal::CaptureStdout();

        LogTargetOperatingSystem();

        std::string output = testing::internal::GetCapturedStdout();

#if defined(_WIN32) && defined(_WIN64)
        EXPECT_NE(output.find("Windows 64-bit"), std::string::npos);
#elif defined(_WIN32)
        EXPECT_NE(output.find("Windows 32-bit"), std::string::npos);
#elif defined(__APPLE__) || defined(__MACH__)
        EXPECT_NE(output.find("macOS"), std::string::npos);
#elif defined(__linux__)
        EXPECT_NE(output.find("Linux"), std::string::npos);
#elif defined(__unix__)
        EXPECT_NE(output.find("Unix"), std::string::npos);
#elif defined(_POSIX_VERSION)
        EXPECT_NE(output.find("POSIX-compliant OS"), std::string::npos);
#else
        EXPECT_NE(output.find("Unknown OS"), std::string::npos);
#endif
    }

    TEST(LibFunctionTests, DetectsCompilerOutput)
    {
        LogTargetCompiler(); // log to console
        // Capture stdout before calling the function
        testing::internal::CaptureStdout();

        LogTargetCompiler();

        std::string output = testing::internal::GetCapturedStdout();

#if defined(__clang__)
        EXPECT_NE(output.find("Clang version"), std::string::npos)
            << "Expected Clang output, got: " << output;

#elif defined(__GNUC__) || defined(__GNUG__)
        EXPECT_NE(output.find("GCC version"), std::string::npos)
            << "Expected GCC output, got: " << output;

#elif defined(_MSC_FULL_VER)
        EXPECT_NE(output.find("MSVC version"), std::string::npos)
            << "Expected MSVC output, got: " << output;

#else
        EXPECT_NE(output.find("Unknown compiler"), std::string::npos)
            << "Expected 'Unknown compiler' output, got: " << output;
#endif
    }

    TEST(LibFunctionTests, DetectsCxxVersionOutput)
    {
        LogTargetCxxStandard(); // log to console
        testing::internal::CaptureStdout();

        LogTargetCxxStandard();

        std::string output = testing::internal::GetCapturedStdout();

        // The test dynamically checks which branch should be active
        // based on the compile-time value of __cplusplus
#if __cplusplus >= 202400L
        EXPECT_NE(output.find("post C++23"), std::string::npos)
            << "Expected 'post C++23', got: " << output;

#elif __cplusplus == 202302L
        EXPECT_NE(output.find("C++23"), std::string::npos)
            << "Expected 'C++23', got: " << output;

#elif __cplusplus == 202002L
        EXPECT_NE(output.find("C++20"), std::string::npos)
            << "Expected 'C++20', got: " << output;

#elif __cplusplus == 201703L
        EXPECT_NE(output.find("C++17"), std::string::npos)
            << "Expected 'C++17', got: " << output;

#elif __cplusplus == 201402L
        EXPECT_NE(output.find("C++14"), std::string::npos)
            << "Expected 'C++14', got: " << output;

#elif __cplusplus == 201103L
        EXPECT_NE(output.find("C++11"), std::string::npos)
            << "Expected 'C++11', got: " << output;

#else
        EXPECT_NE(output.find("pre C++11"), std::string::npos)
            << "Expected 'pre C++11', got: " << output;
#endif

        // Optional: ensure the numeric value of __cplusplus is printed too
        EXPECT_NE(output.find(std::to_string(__cplusplus)), std::string::npos)
            << "Expected numeric C++ version (" << __cplusplus << ") to appear in output.";
    }


    //
    // ---------- Free Function Tests ----------
    //
    TEST(MyAppFreeFunctionTests, Add_PositiveNumbers)
    {
        EXPECT_EQ(add(2, 3), 5);
    }

    TEST(MyAppFreeFunctionTests, Add_NegativeNumbers)
    {
        EXPECT_EQ(add(-2, -3), -5);
    }

    TEST(MyAppFreeFunctionTests, Add_WithZero)
    {
        EXPECT_EQ(add(10, 0), 10);
    }

    TEST(MyAppFreeFunctionTests, Subtract_PositiveNumbers)
    {
        EXPECT_EQ(subtract(10, 4), 6);
    }

    TEST(MyAppFreeFunctionTests, Subtract_NegativeNumbers)
    {
        EXPECT_EQ(subtract(-2, -3), 1);
    }

    TEST(MyAppFreeFunctionTests, Subtract_WithZero)
    {
        EXPECT_EQ(subtract(5, 0), 5);
    }

    TEST(MyAppFreeFunctionTests, Multiply_PositiveNumbers)
    {
        EXPECT_EQ(multiply(3, 4), 12);
    }

    TEST(MyAppFreeFunctionTests, Multiply_NegativeNumbers)
    {
        EXPECT_EQ(multiply(-3, 4), -12);
    }

    TEST(MyAppFreeFunctionTests, Multiply_ByZero)
    {
        EXPECT_EQ(multiply(7, 0), 0);
    }

    TEST(MyAppFreeFunctionTests, Divide_ValidNumbers)
    {
        EXPECT_EQ(divide(8, 2), 4);
    }

    TEST(MyAppFreeFunctionTests, Divide_NegativeNumbers)
    {
        EXPECT_EQ(divide(-10, 5), -2);
    }

    TEST(MyAppFreeFunctionTests, Divide_ByZero_Throws)
    {
        EXPECT_THROW(divide(5, 0), std::invalid_argument);
    }

    TEST(MyAppFreeFunctionTests, Modulus_ValidNumbers)
    {
        EXPECT_EQ(modulus(10, 3), 1);
    }

    TEST(MyAppFreeFunctionTests, Modulus_NegativeNumbers)
    {
        EXPECT_EQ(modulus(-10, 3), -1);
    }

    TEST(MyAppFreeFunctionTests, Modulus_ByZero_Throws)
    {
        EXPECT_THROW(modulus(10, 0), std::invalid_argument);
    }

    //
    // ---------- Class Method Tests ----------
    //

    class MyAppClassMethodTests : public ::testing::Test {
    protected:
        MathFunctions math;  // available in all TEST_F cases
    };

    TEST_F(MyAppClassMethodTests, Add_UsingClass)
    {
        EXPECT_EQ(math.add(5, 5), 10);
    }

    TEST_F(MyAppClassMethodTests, Subtract_UsingClass)
    {
        EXPECT_EQ(math.subtract(10, 8), 2);
    }

    TEST_F(MyAppClassMethodTests, Multiply_UsingClass)
    {
        EXPECT_EQ(math.multiply(3, 5), 15);
    }

    TEST_F(MyAppClassMethodTests, Divide_UsingClass)
    {
        EXPECT_EQ(math.divide(9, 3), 3);
    }

    TEST_F(MyAppClassMethodTests, Divide_ByZero_UsingClass_Throws)
    {
        EXPECT_THROW(math.divide(1, 0), std::invalid_argument);
    }

    TEST_F(MyAppClassMethodTests, Modulus_UsingClass)
    {
        EXPECT_EQ(math.modulus(10, 3), 1);
    }

    TEST_F(MyAppClassMethodTests, Modulus_ByZero_UsingClass_Throws)
    {
        EXPECT_THROW(math.modulus(10, 0), std::invalid_argument);
    }
} // namespace GUnitTestMyApp
