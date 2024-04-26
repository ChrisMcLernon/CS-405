// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

using namespace std;

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// Verifies there is no overflow or else returns false
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps) or false if overflow was detected</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;          // Result variable to contain the final result and to keep track of addition progress

    for (unsigned long int i = 0; i < steps; ++i){
        
        // Checks if the increment is greater than 0 then checks if the diffrence between the increment and the numeric maximum of the given type is less than the result
        // so when the sum of increment and result is found it is guranteed to be less than the numeric limit as well as insuring it can not underflow on accident with a 
        // negative increment
        if ((increment >= 0) && (result > (numeric_limits<T>::max() - increment))){ 
            return false;
        }
        
        result += increment;   // Increments the running total for each step that passes the overflow check
    }

    return result;             // Returns the result
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// Vrifies there is no underflow or else returns false
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps) or false if underflow was detected</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;          // Result variable to contain the final result and to keep track of addition progress

    for (unsigned long int i = 0; i < steps; ++i){
        
        // Checks if the decrement is greater than 0 then checks if the sum of the decrement and the numeric minimum of the given type is greater than the result
        // so when the difference of the result and decrement is found it is guranteed to be greater than the numeric limit as well as insuring it can not overflow
        // on accident with a positive decrement
        if ((decrement >= 0) && (result < (numeric_limits<T>::min() + decrement))){
            return false;
        }
        
        result -= decrement;   // Increments the running total for each step that passes the overflow check
    }

    return result;             // Returns the result
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps);
    if (result == false){
        cout << "Overflow Detected!" << endl;
    }else{
        cout << +result << endl;
    }

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1);
    if (result == false){
        cout << "Overflow Detected!" << endl;
    }else{
        cout << +result << endl;
    }
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    T result = subtract_numbers<T>(start, decrement, steps);
    if (result == false){
        cout << "Underflow Detected!" << endl;
    }else{
        cout << +result << endl;
    }

    std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << steps + 1 << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1);
    if (result == false){
        cout <<  "Underflow Detected!" << endl;
    }else{
        cout << +result << endl;
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!     " << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu