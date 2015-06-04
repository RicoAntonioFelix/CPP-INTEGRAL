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

#ifndef INTEGRAL_CSP_H__
#define INTEGRAL_CSP_H__

#include <stack>
#include <limits>
#include <bitset>
#include <iosfwd>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <type_traits>

namespace compuSUAVE_Professional {

/**
 * @brief This component is a wrapper to any fundamental integral type.
 *        It consists of all attributes and operations well known for such a
 *        type including extra operations such as conversions to string
 *        representations of various numerical bases and a few others.
 */
template<typename T>
class Integral final {

    /*
     * Assert that instantiation was done with a type parameter that contain
     * integral type traits.
     */
    static_assert(std::is_integral<T>::value,
                  "Error instantiating compuSUAVE_Professional::Integral<T>:\
                   Found non-integral type");

public:

    /**
     * @brief Underlying type of the encapsulated value
     */
    using value_type = T;

    //=========================================================================
    // Constructors
    //=========================================================================

    /**
     * @brief Default constructor
     *
     * Zero initializes the object
     */
    constexpr Integral() noexcept
    : m_value{T{}} {}

    /**
     * @brief Constructor to initialize the object with the specified value
     *
     * @param value Value to initialize the object
     */
    constexpr Integral(const T value) noexcept
    : m_value{value} {}

    /**
     * @brief Copy constructor
     *
     * @param carbon_copy Object to copy value from
     */
    constexpr Integral(const Integral<T>& carbon_copy) noexcept
    : m_value{carbon_copy} {}

    /**
     * @brief Constructor to initialize the object with the specified value
     *
     * @param ct Compatible type to initialize the object
     */
    template<typename CompatibleType>
    constexpr Integral(const CompatibleType ct) noexcept
    : m_value{static_cast<T>(ct)} {}

    /**
     * @brief Move constructor to transfer the value from the specified object
     *
     * @param carbon_copy Object to transfer the value from
     */
    constexpr Integral(Integral<T>&& carbon_copy) noexcept
    : m_value{carbon_copy} {}

    /**
     * @brief Constructor to initialize the object with a C-String
     *
     * C-String must be able to be parsed into an integral value else the
     * object is initialized to zero. Parsable representations include
     * binary, octal, hexadecimal and decimal representations
     *
     * @param value C-String to parse
     */
    constexpr Integral(const char* value) noexcept
    : Integral{std::string{value}} {}

    /**
     * @brief Constructor to initialize the object with a std::string object
     *
     * std::string object must be able to be parsed into an integral value
     * else the object is initialized to zero. Parsable representations
     * include binary, octal, hexadecimal and decimal representations
     *
     * @param value std::string object to parse
     */
    Integral(const std::string& value) noexcept
    : m_value{T{}} {

        // Check for binary sequence
        if ((value.find("0b") == 0) || (value.find("0B") == 0)) {
            try {
                std::bitset<std::numeric_limits<T>::digits> bits{value, 2};
                m_value = static_cast<T>(bits.to_ullong());
            } catch(const std::invalid_argument& ia) {}
            return;
        }

        std::stringstream converter{value};

        // Check for hexidecimal sequence
        if (value.find("0x") == 0) {
            converter << std::hex;
            converter >> m_value;
            return;
        }

        // Check for octal sequence
        if (value.find("0") == 0) {
            converter << std::oct;
            converter >> m_value;
            return;
        }

        converter >> m_value;       
    }

    //=========================================================================
    // Assignment Operations
    //=========================================================================

    /**
     * @brief Assigns the value from the specified object
     *
     * @param carbon_copy Object to get the value from
     *
     * @return Transformed object containing a new value
     */
    constexpr Integral<T>&
    operator =(const Integral<T>& carbon_copy) noexcept {
        return checkAndAssign(carbon_copy);
    }

    /**
     * @brief Assigns the value from the specified temporary object
     *
     * @param carbon_copy Object to get the value from
     *
     * @return Transformed object containing a new value
     */
    constexpr Integral<T>&
    operator =(Integral<T>&& carbon_copy) noexcept {
        return checkAndAssign(carbon_copy);
    }

    /**
     * @brief Assigns the value from the specified compatible type
     *
     * @tparam ct Object to get the value from
     *
     * @return Transformed object containing a new value
     */
    template<typename CompatibleType>
    constexpr Integral<T>&
    operator =(const CompatibleType ct) noexcept {
        return checkAndAssign(Integral<T>{ct});
    }

    //=========================================================================
    // Destructor
    //=========================================================================

    /**
     * @brief Default constructor
     */
    ~Integral() = default;

    //=========================================================================
    // Addition Operation
    //=========================================================================

    /**
     * @brief Performs addition on the specified objects
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return Result from the operation
     */
    friend constexpr Integral<T> operator +(const Integral<T>& lhs,
                                            const Integral<T>& rhs)
                                            noexcept {
        return Integral<T>{lhs.m_value + rhs.m_value};
    }

    //=========================================================================
    // Increment Operations
    //=========================================================================

    /**
     * @brief Increments the value by one and returns the incremented value
     *
     * - value and object is synonymous in this context
     *
     * @return The incremented value
     */
    constexpr Integral<T>& operator ++() noexcept {
        ++m_value;
        return *this;
    }

    /**
     * @brief Increments the value by one and returns the pre-incremented value
     *
     * - value and object is synonymous in this context
     *
     * @return The pre-incremented value
     */
    constexpr Integral<T> operator ++(int) noexcept {
        return Integral<T>{m_value++};
    }

    //=========================================================================
    // Subtraction Operation
    //=========================================================================

    /**
     * @brief Performs subtraction on the specified objects
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return Result from the operation
     */
    friend constexpr Integral<T> operator -(const Integral<T>& lhs,
                                            const Integral<T>& rhs)
                                            noexcept {
        return Integral<T>{lhs.m_value - rhs.m_value};
    }

    //=========================================================================
    // Decrement Operations
    //=========================================================================

    /**
     * @brief Decrements the value by one and returns the decremented value
     *
     * - value and object is synonymous in this context
     *
     * @return The decremented value
     */
    constexpr Integral<T>& operator --() noexcept {
        --m_value;
        return *this;
    }

    /**
     * @brief Decrements the value by one and returns the pre-decremented value
     *
     * - value and object is synonymous in this context
     *
     * @return The pre-decremented value
     */
    constexpr Integral<T> operator --(int) noexcept {
        return Integral<T>{m_value--};
    }

    //=========================================================================
    // Negate Operation
    //=========================================================================

    /**
     * @brief Provides a value with an opposite sign
     *
     * - value and object is synonymous in this context
     *
     * @return Value with opposite sign
     */
    constexpr Integral<T> operator -() const noexcept {
        return -m_value;
    }

    //=========================================================================
    // Multiplication Operation
    //=========================================================================

    /**
     * @brief Performs multiplication on the specified objects
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return Result from the operation
     */
    friend constexpr Integral<T> operator *(const Integral<T>& lhs,
                                            const Integral<T>& rhs)
                                            noexcept {
        return Integral<T>{lhs.m_value * rhs.m_value};
    }

    //=========================================================================
    // Division Operation
    //=========================================================================

    /**
     * @brief Performs division on the specified objects
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return Result from the operation
     */
    friend constexpr Integral<T> operator /(const Integral<T>& lhs,
                                            const Integral<T>& rhs)
                                            noexcept {
        return Integral<T>{lhs.m_value / rhs.m_value};
    }

    //=========================================================================
    // Modulus Operation
    //=========================================================================

    /**
     * @brief Performs modulo on the specified objects
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return Result from the operation
     */
    friend constexpr Integral<T> operator %(const Integral<T>& lhs,
                                            const Integral<T>& rhs)
                                            noexcept {
        return Integral<T>{lhs.m_value % rhs.m_value};
    }

    //=========================================================================
    // Comparison Operations
    //=========================================================================

    /**
     * @brief Determines if the objects are of equal value
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return True if equal, false otherwise
     */
    friend constexpr bool operator ==(const Integral<T>& lhs,
                                      const Integral<T>& rhs)
                                      noexcept {
        return lhs.m_value == rhs.m_value;
    }

    /**
     * @brief Determines if the objects are not of equal value
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return True if not equal, false otherwise
     */
    friend constexpr bool operator !=(const Integral<T>& lhs,
                                      const Integral<T>& rhs)
                                      noexcept {
        return !(lhs == rhs);
    }

    /**
     * @brief Determines if one value is less than the other
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return True if lhs is less than rhs, false otherwise
     */
    friend constexpr bool operator <(const Integral<T>& lhs,
                                     const Integral<T>& rhs)
                                     noexcept {
        return lhs.m_value < rhs.m_value;
    }

    /**
     * @brief Determines if one value is greater than the other
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return True if lhs is greater than rhs, false otherwise
     */
    friend constexpr bool operator >(const Integral<T>& lhs,
                                     const Integral<T>& rhs)
                                     noexcept {
        return !(lhs < rhs);
    }

    /**
     * @brief Determines if one value is less than or equal to the other
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return True if lhs is less than or equal to rhs, false otherwise
     */
    friend constexpr bool operator <=(const Integral<T>& lhs,
                                      const Integral<T>& rhs)
                                      noexcept {
        return (lhs < rhs) || (lhs == rhs);
    }

    /**
     * @brief Determines if one value is greater than or equal to the other
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     *
     * @return True if lhs is greater than or equal to rhs, false otherwise
     */
    friend constexpr bool operator >=(const Integral<T>& lhs,
                                      const Integral<T>& rhs)
                                      noexcept {
        return !(lhs <= rhs);
    }

    //=========================================================================
    // Conversions
    //=========================================================================
    
    /**
     * @brief Converts the object to a C-String
     *
     * @return A C-String representation of the object
     */
    constexpr operator const char*() const noexcept {
        return std::to_string(m_value).c_str();
    }

    /**
     * @brief Converts the object to a std::string object
     *
     * @return A std::string object representation of the object
     */
    constexpr operator std::string() const noexcept {
        return std::to_string(m_value);
    }

    /**
     * @brief Converts the object to instantiated type which can be coerced to
     *        any of the following:
     *
     * - signed char, unsigned char
     * - signed short int, unsigned short int
     * - signed int, unsigned int
     * - signed long int, unsigned long int
     * - signed long long int, unsigned long long int
     * - float, double, long double
     *
     * @return Value using the raw underlying type
     */
    constexpr operator T() const noexcept {
        return m_value;
    }

    //=========================================================================
    // Conversion to Specified Radix
    //=========================================================================

    /**
     * @brief Performs a conversion of the underlying value to the specified
     *        representation
     *
     * Special Cases:
     * - If the supplied radix is zero(0) then default base 10 representation is
     *   returned.
     * - If the supplied radix is greater than sixteen(16) then default base 10
     *   representation is returned as conversions to those are not commonly
     *   used.
     *
     * @param radix Base to convert the underlying value to
     * 
     * @return A C-String representation of the converted underlying value
     */
    constexpr const char* toRadix(std::size_t radix) const noexcept {

        // Enforce pre-conditions
        if (!radix || (radix > 16)) {
            return std::to_string(m_value).c_str();
        }

        std::string       result;
        std::stringstream result_buffer;

        // Use library to produce hexadecimal representation
        if (radix == 16) {
            result_buffer << std::hex;
            result_buffer << m_value;
            result_buffer >> result;
        }

        // Use library to produce octal representation
        else if (radix == 8) {
            result_buffer << std::oct;
            result_buffer << m_value;
            result_buffer >> result;
        }

        // Use mathematical formula for base transformation
        else {
            T value = m_value;
            std::stack<int> result_stack;

            while (value != 0) {
                result_stack.push(value % radix);
                value /= radix;
            }

            while (!result_stack.empty()) {
                result_buffer << result_stack.top();
                result_stack.pop();
            }

            result_buffer >> result;
        }

        return (result).c_str();
    }

    /**
     * @brief Performs a conversion of the underlying value to base 16
     *        representation
     *
     * @return A C-String representation of the converted underlying value
     */
    constexpr const char* hex() const noexcept {
        return toRadix(16);
    }

    /**
     * @brief Performs a conversion of the underlying value to base 10
     *        representation
     *
     * @return A C-String representation of the converted underlying value
     */
    constexpr const char* dec() const noexcept {
        return toRadix(10);
    }

    /**
     * @brief Performs a conversion of the underlying value to base 8
     *        representation
     *
     * @return A C-String representation of the converted underlying value
     */
    constexpr const char* oct() const noexcept {
        return toRadix(8);
    }

    /**
     * @brief Performs a conversion of the underlying value to base 2
     *        representation
     *
     * @return A C-String representation of the converted underlying value
     */
    constexpr const char* bin() const noexcept {
        return toRadix(2);
    }

    //=========================================================================
    // Min and Max Utility Methods
    //=========================================================================

    /**
     * @brief Get minimum between the two objects of this type
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     * 
     * @return Minimum object between lhs and rhs
     */
    friend constexpr Integral<T>& min(const Integral<T>& lhs,
                                      const Integral<T>& rhs)
                                      noexcept {
        return const_cast<Integral<T>&>((lhs < rhs) ? lhs : rhs);
    }

    /**
     * @brief Get maximum between the two objects of this type
     *
     * @param lhs Left hand operand
     * @param rhs Right hand operand
     * 
     * @return Maximum object between lhs and rhs
     */
    friend constexpr Integral<T>& max(const Integral<T>& lhs,
                                      const Integral<T>& rhs)
                                      noexcept {
        return const_cast<Integral<T>&>((lhs > rhs) ? lhs : rhs);
    }

    //=========================================================================
    // Numerical Property Methods
    //=========================================================================

    /**
     * @brief Check if value represents an odd value
     *
     * @return True if value is odd, false otherwise
     */
    constexpr bool odd() const noexcept {
        return m_value & 1;
    }

    /**
     * @brief Check if value represents an even value
     *
     * @return True if value is even, false otherwise
     */
    constexpr bool even() const noexcept {
        return !odd();
    }

    /**
     * @brief Get the minimum representable value of this type
     *
     * @reutrn Minimum value this type can represent
     */
    constexpr static T min() noexcept {
        return std::numeric_limits<T>::min();
    }

    /**
     * @brief Get the maximum representable value of this type
     *
     * @return Maximum value this type can represent
     */
    constexpr static T max() noexcept {
        return std::numeric_limits<T>::max();
    }

    //=========================================================================
    // Streaming Operations
    //=========================================================================

    /**
     * @brief Allow this object to retrieve a value from an input stream
     *
     * Skips initial whitespace from the stream and stops on first non-numerical
     * character
     *
     * @param cin Input stream object
     * @param obj An object of this type
     *
     * @return The specified input stream
     */
    friend std::istream& operator >>(std::istream& cin,
                                     Integral<T>& obj)
                                     noexcept {
        std::string reciever;
        cin >> reciever;
        obj.m_value = Integral<T>{reciever};
        return cin;
    }

    /**
     * @brief Allow this object to be streamed to an output stream
     *
     * @param cout Output stream object
     * @param obj An object of this type
     *
     * @return The specified output stream
     */
    friend constexpr std::ostream& operator <<(std::ostream& cout,
                                               const Integral<T>& obj)
                                               noexcept {
        return cout << obj.m_value;
    }

//=========================================================================
// Implementation Helper Method
//=========================================================================
private:
    /*
     * Assignment Operations Helper Method
     */
    constexpr Integral<T>& checkAndAssign(const Integral<T>& carbon_copy)
                                          noexcept {
        if (this != &carbon_copy)
            m_value = carbon_copy.m_value;
        return *this;
    }

//=========================================================================
// Implementation Details
//=========================================================================
private:
    T m_value; //< Encapsulated Integral Value

}; //< Integral<T>

//=========================================================================
// User Defined Literals
//=========================================================================

/**
 * @brief User defined literal to create an Integral<unsigned char> object
 *
 * @param value Value to be transformed into an Integral<unsigned char> object
 */
inline constexpr auto operator""_cspiuc(unsigned long long value)
{
    return Integral<unsigned char>{value};
}

/**
 * @brief User defined literal to create an Integral<unsigned short> object
 *
 * @param value Value to be transformed into an Integral<unsigned short> object
 */
inline constexpr auto operator""_cspius(unsigned long long value)
{
    return Integral<unsigned short>{value};
}

/**
 * @brief User defined literal to create an Integral<unsigned int> object
 *
 * @param value Value to be transformed into an Integral<unsigned int> object
 */
inline constexpr auto operator""_cspiui(unsigned long long value)
{
    return Integral<unsigned int>{value};
}

/**
 * @brief User defined literal to create an Integral<unsigned long> object
 *
 * @param value Value to be transformed into an Integral<unsigned long> object
 */
inline constexpr auto operator""_cspiul(unsigned long long value)
{
    return Integral<unsigned long>{value};
}

/**
 * @brief User defined literal to create an Integral<unsigned long long> object
 *
 * @param value Value to be transformed into an Integral<unsigned long long>
 *        object
 */
inline constexpr auto operator""_cspiull(unsigned long long value)
{
    return Integral<unsigned long long>{value};
}

} //< namespace compuSUAVE_Professional

#endif //< INTEGRAL_CSP_H__
