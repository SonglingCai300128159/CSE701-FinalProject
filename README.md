# CSE 701 Final Project: Bigint
## Cai Songling 400259567

* bigint.hpp: A header file containing the entire code for the class bigint.
* test.cpp: A program that comprehensively and thoroughly tests every single feature of class to make sure it works properly.
* The bigint.hpp implemented the following function: 
    - Addition (+ and +=)
    - Subtraction (- and -=)
    - Multiplication (* and *=)
    - Negation (unary -)
    - Comparison (==, !=, <, >, <=, and >=)
    - Insertion (<<, to print the integer to a stream such as std::cout or a file)
    - Increment (++, both pre-increment and post-increment)
    - Decrement (--, both pre-decrement and post-decrement)
    - Integer division (/ and /=)
    - Modulus (% and %=)
    - A constructor that takes a string and a base, and converts the string to an arbitrary-precision integer in that base.
    - A member function to_string() that converts the arbitrary-precision integer to a string in a given base. 
* The program doesn't need the input file and all the test cases come from random number. 
* The example output log should look like this:
    > Test constrcutor with invaild char pass. 9 char of bigint should be number omly  
    Comparsion Test == : (+50754534) == (+72699655) is 1 pass.  
    Comparsion Test != : (+50754534) != (+72699655) is 0 pass.  
    Comparsion Test > : (+50754534) > (+72699655) is 0 pass.  
    Comparsion Test >= : (+50754534) >= (+72699655) is 0 pass.  
    Comparsion Test < : (+50754534) < (+72699655) is 1 pass.  
    Comparsion Test <= : (+50754534) <= (+72699655) is 1 pass.  
    Adder Test : (+50754534) + (+72699655) = +123454189 Pass.  
    Adder Test : (+50754534) + (-72699655) = -21945121 Pass.  
    Adder Test : (-50754534) + (+72699655) = +21945121 Pass.  
    Adder Test : (-50754534) + (-72699655) = -123454189 Pass.  
    Subtraction Test : (+50754534) - (+72699655) = -21945121 Pass.  
    Subtraction Test : (+50754534) - (-72699655) = +123454189 Pass.  
    Subtraction Test : (-50754534) - (+72699655) = -123454189 Pass.  
    Subtraction Test : (-50754534) - (-72699655) = +21945121 Pass.  
    Multiplication Test : (+50754534) * (+72699655) = +3689837111485770 Pass.  
    Multiplication Test : (+50754534) * (-72699655) = -3689837111485770 Pass.  
    Multiplication Test : (-50754534) * (+72699655) = -3689837111485770 Pass.  
    Multiplication Test : (-50754534) * (-72699655) = +3689837111485770 Pass.  
    Division Test : (+50754534) / (+72699655) = 0 Pass.  
    Division Test : (+50754534) / (-72699655) = 0 Pass.  
    Division Test : (-50754534) / (+72699655) = 0 Pass.  
    Division Test : (-50754534) / (-72699655) = 0 Pass.  
    Moduls Test : (+50754534) % (+72699655) = +50754534 Pass.  
    Moduls Test : (+50754534) % (-72699655) = +50754534 Pass.  
    Moduls Test : (-50754534) % (+72699655) = -50754534 Pass.  
    Moduls Test : (-50754534) % (-72699655) = -50754534 Pass.  
    Test divisor = 0 pass. Divisior can't be 0  
    Integration Test : (+50754534) + (+72699655) - (+35793535) = +87660654 pass.  
    Consistency Test : (+50754534) + (+72699655) - (+35793535) pass.  
    Consistency Test : ((+50754534) + (+72699655)) * (+35793535) pass.  
    Number system Test pass.Base 2  
    Big Int Test : (+50754534507545347269965572699655) + & - (+50754534726996555075453472699655) pass.  
    Big Int Test : (+50754534507545347269965572699655) * & / (+50754534726996555075453472699655) pass.  
    Test 34. pass 34. Correctness 100%.