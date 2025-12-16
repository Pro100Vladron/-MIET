#include <iostream>
#include <sstream>
#include <string>

#include "iomanip.hpp"

int main() {
    std::cout << "=== Final Tests According to Requirements ===" << std::endl;
    
    // Test 1: iomanip::simple (из задания)
    std::stringstream s1;
    s1 << "some text" << endm;
    std::cout << "Test 1 - iomanip::simple: '" << s1.str() << "'" << std::endl;
    bool test1_pass = (s1.str() == "some text[eol]\n");
    
    // Test 2: iomanip::one_operand (из задания)
    std::stringstream s2;
    s2 << "some test " << squares << 123 << " and " << squares << "me" << squares << -88.59;
    std::cout << "Test 2 - iomanip::one_operand: '" << s2.str() << "'" << std::endl;
    bool test2_pass = (s2.str() == "some test [123] and [me][-88.59]");
    
    // Test 3: iomanip::two_operands - int (из задания)
    std::stringstream s3;
    s3 << add << 124 << 589 << " == " << 713;
    std::cout << "Test 3 - iomanip::two_operands int: '" << s3.str() << "'" << std::endl;
    bool test3_pass = (s3.str() == "713 == 713");
    
    // Test 4: iomanip::two_operands - string (из задания)
    std::stringstream s4;
    s4 << add << "abc" << "efg" << " text";
    std::cout << "Test 4 - iomanip::two_operands string: '" << s4.str() << "'" << std::endl;
    bool test4_pass = (s4.str() == "abcefg text");
    
    // Test 5: iomanip::two_operands - double (из задания)
    std::stringstream s5;
    s5 << "get => " << add << 45.89 << 32.177 << " <=";
    std::cout << "Test 5 - iomanip::two_operands double: '" << s5.str() << "'" << std::endl;
    bool test5_pass = (s5.str() == "get => 78.067 <=");
    
    // Test 6: variant1::cos - numeric (из варианта)
    std::stringstream s6;
    s6 << cos_manip << 0;
    std::cout << "Test 6 - variant1::cos numeric: '" << s6.str() << "'" << std::endl;
    bool test6_pass = (s6.str() == "1");
    
    // Test 7: variant1::cos - string (из варианта)
    std::stringstream s7;
    s7 << cos_manip << "pi/2";
    std::cout << "Test 7 - variant1::cos string: '" << s7.str() << "'" << std::endl;
    bool test7_pass = (s7.str() == "cos(pi/2)");
    
    // Test 8: variant1::ftp (из варианта)
    std::stringstream s8;
    s8 << ftp << "site.com";
    std::cout << "Test 8 - variant1::ftp: '" << s8.str() << "'" << std::endl;
    bool test8_pass = (s8.str() == "ftp://site.com");
    
    // Results
    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "Test 1 (endm): " << (test1_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 2 (squares): " << (test2_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 3 (add int): " << (test3_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 4 (add string): " << (test4_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 5 (add double): " << (test5_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 6 (cos numeric): " << (test6_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 7 (cos string): " << (test7_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "Test 8 (ftp): " << (test8_pass ? "PASS" : "FAIL") << std::endl;
    
    int passed = test1_pass + test2_pass + test3_pass + test4_pass + test5_pass + test6_pass + test7_pass + test8_pass;
    std::cout << "\nTotal: " << passed << "/8 tests passed" << std::endl;
    
    return (passed == 8) ? 0 : 1;
} 
