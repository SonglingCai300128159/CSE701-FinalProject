#include <iostream>
#include <string>
#include <random>
#include "bigint.hpp"

/**
 * @brief self-define exception. Throw when result is wrong
 * 
 */
class wrong_result : public std::exception {
private:
    std::string message;
public:
    wrong_result(const std::string& msg) : message("Error: " + msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

std::int64_t testWithOperator(const std::int64_t left, const std::int64_t right, const char operate);
std::int64_t testComparsion(const std::int64_t left, const std::int64_t right);
std::int64_t testLongInt(const std::int64_t left, const std::int64_t right);

int main(){   
    std::int64_t total = 0;
    std::int64_t countCorrect = 0;

    std::random_device randomSeed;
    std::mt19937 mt32Random(randomSeed());

    std::int64_t left = mt32Random() % 100000000, right = mt32Random() % 100000000, third = mt32Random() % 100000000, randomBase = mt32Random() % 15 + 2;

    //Test constrcutor with invaild char pass
    try{
        total++;
        bigint bLeft(std::to_string(left)+"*$"+std::to_string(right));
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        countCorrect++;
        std::cout<<"Test constrcutor with invaild char pass. ";
        std::cout<<e.what()<<"\n";
    }

    //Test comparsion
    try{
        total += 6;
        countCorrect += testComparsion(left, right);
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test add
    try{
        total++;
        testWithOperator(left, right, '+');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(left, -right, '+');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, right, '+');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, -right, '+');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test sub
    try{
        total++;
        testWithOperator(left, right, '-');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(left, -right, '-');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, right, '-');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, -right, '-');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test nulti
    try{
        total++;
        testWithOperator(left, right, '*');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(left, -right, '*');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, right, '*');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, -right, '*');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test div
    try{
        total++;
        testWithOperator(left, right, '/');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(left, -right, '/');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, right, '/');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, -right, '/');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test mod
    try{
        total++;
        testWithOperator(left, right, '%');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(left, -right, '%');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, right, '%');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }
    try{
        total++;
        testWithOperator(-left, -right, '%');
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test divisor = 0
    try{
        total++;
        bigint bLeft(left);
        bigint bRight(0);
        bLeft / bRight;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        countCorrect++;
        std::cout<<"Test divisor = 0 pass. ";
        std::cout<<e.what()<<"\n";
    }

    //Test Integration
    try{
        total++;
        bigint bLeft(left);
        bigint bRight(right);
        bigint bThird(third);
        bigint bStander(left + right - third);
        if((bLeft + bRight - bThird) != bStander)
            throw wrong_result("Integration Test : ("+ bLeft.toString() + ") + (" + bRight.toString() +") - (" + bThird.toString()+ ") has wrong result.");
        std::cout<<"Integration Test : ("+ bLeft.toString() + ") + (" + bRight.toString() +") - (" + bThird.toString()+ ") = " + bStander.toString() + " pass.\n";
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test Consistency
    try{
        total++;
        bigint bLeft(left);
        bigint bRight(right);
        bigint bThird(third);
        if((bLeft + bRight - bThird) != (bLeft - bThird + bRight))
            throw wrong_result("Consistency Test : ("+ bLeft.toString() + ") + (" + bRight.toString() +") - (" + bThird.toString()+ ") has wrong result.");

        std::cout<<"Consistency Test : ("+ bLeft.toString() + ") + (" + bRight.toString() +") - (" + bThird.toString() + ") pass.\n";
        countCorrect++;

        total++;
        if(((bLeft + bRight) * bThird) != (bLeft * bThird + bRight * bThird))
            throw wrong_result("Consistency Test : (("+ bLeft.toString() + ") + (" + bRight.toString() +")) * (" + bThird.toString()+ ") has wrong result.");

        std::cout<<"Consistency Test : (("+ bLeft.toString() + ") + (" + bRight.toString() +")) * (" + bThird.toString() + ") pass.\n";
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    //Test number system with different base
    try{
        total++;
        bigint bLeft(left);
        bigint bRight(bLeft.toString(randomBase), randomBase);
        if(bLeft != bRight)
            throw wrong_result("Number system Test has wrong result.");
        std::cout<<"Number system Test pass."<<"Base "+ std::to_string(randomBase)<<"\n";
        countCorrect++;
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    try{
        total+=2;
        countCorrect += testLongInt(left, right);
    }catch(const wrong_result &e){
        std::cout<<e.what()<<"\n";
    }catch(const std::exception &e){
        std::cout<<e.what()<<"\n";
    }

    std::cout<<"Test " + std::to_string(total) + ". Pass " + std::to_string(countCorrect) + ". Correctness " + std::to_string(countCorrect / total * 100) + "%.\n"; 
} 

/**
 * @brief Test with operator +, -, *, /, and check result
 * 
 * @param left left int number
 * @param right right int number
 * @param operate indicate the operator
 * @return std::int64_t return 1 when result is right
 */
std::int64_t testWithOperator(const std::int64_t left, const std::int64_t right, const char operate){
    bigint bLeft(left);
    bigint bRight(right);

    if(operate == '+'){
        bigint bStander(left + right);
        if((bLeft + bRight) != bStander)
            throw wrong_result("Adder Test : ("+ bLeft.toString() + ") + (" + bRight.toString() + ") has wrong result.");
        
        std::cout<<"Adder Test : ("+ bLeft.toString() + ") + (" + bRight.toString() + ") = " + bStander.toString() + " Pass.\n";
        return 1;
    }
    
    if(operate == '-'){
        bigint bStander(left - right);
        if((bLeft - bRight) != bStander)
            throw wrong_result("Subtraction Test : ("+ bLeft.toString() + ") - (" + bRight.toString() + ") has wrong result.");
        
        std::cout<<"Subtraction Test : ("+ bLeft.toString() + ") - (" + bRight.toString() + ") = " + bStander.toString() + " Pass.\n";
        return 1;
    }

    if(operate == '*'){
        bigint bStander(left * right);
        if((bLeft * bRight) != bStander)
            throw wrong_result("Multiplication Test : ("+ bLeft.toString() + ") * (" + bRight.toString() + ") has wrong result.");
        
        std::cout<<"Multiplication Test : ("+ bLeft.toString() + ") * (" + bRight.toString() + ") = " + bStander.toString() + " Pass.\n";
        return 1;
    }

    if(operate == '/'){
        bigint bStander(left / right);
        if((bLeft / bRight) != bStander)
            throw wrong_result("Division Test : ("+ bLeft.toString() + ") / (" + bRight.toString() + ") has wrong result.");
        
        std::cout<<"Division Test : ("+ bLeft.toString() + ") / (" + bRight.toString() + ") = " + bStander.toString() + " Pass.\n";
        return 1;
    }
    
    if(operate == '%'){
        bigint bStander(left % right);
        if((bLeft % bRight) != bStander)
            throw wrong_result("Moduls Test : ("+ bLeft.toString() + ") % (" + bRight.toString() + ") has wrong result.");
        
        std::cout<<"Moduls Test : ("+ bLeft.toString() + ") % (" + bRight.toString() + ") = " + bStander.toString() + " Pass.\n";
        return 1;
    }

    return 0;
}

/**
 * @brief test comparsion ==, !=, >, <, >=, <=
 * 
 * @param left left int number to compare
 * @param right right int number to compare
 * @return std::int64_t return the correct test number
 */
std::int64_t testComparsion(const std::int64_t left, const std::int64_t right){
    bigint bLeft(left);
    bigint bRight(right);
    bigint samebLeft(left);
    std::int64_t count = 0;

    if(!(bLeft == samebLeft))
        throw wrong_result("Comparsion Test == : ("+ bLeft.toString() + ") == (" + bRight.toString() + ") has wrong result.");
    
    std::cout<<"Comparsion Test == : ("+ bLeft.toString() + ") == (" + bRight.toString() + ") is " + std::to_string(true) + " pass.\n";
    count++;

    if(bLeft != samebLeft)
        throw wrong_result("Comparsion Test != : ("+ bLeft.toString() + ") != (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Comparsion Test != : ("+ bLeft.toString() + ") != (" + bRight.toString() + ") is " +std::to_string(false) + " pass.\n";
    count++;

    if((bLeft > right) != (left > right))
        throw wrong_result("Comparsion Test > : ("+ bLeft.toString() + ") > (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Comparsion Test > : ("+ bLeft.toString() + ") > (" + bRight.toString() + ") is " +std::to_string(left > right) + " pass.\n";
    count++;

    if((bLeft >= right) != (left >= right))
        throw wrong_result("Comparsion Test >= : ("+ bLeft.toString() + ") >= (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Comparsion Test >= : ("+ bLeft.toString() + ") >= (" + bRight.toString() + ") is " +std::to_string(left >= right) + " pass.\n";
    count++;

    if((bLeft < right) != (left < right))
        throw wrong_result("Comparsion Test < : ("+ bLeft.toString() + ") < (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Comparsion Test < : ("+ bLeft.toString() + ") < (" + bRight.toString() + ") is " +std::to_string(left < right) + " pass.\n";
    count++;

    if((bLeft <= right) != (left <= right))
        throw wrong_result("Comparsion Test >= : ("+ bLeft.toString() + ") >= (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Comparsion Test <= : ("+ bLeft.toString() + ") <= (" + bRight.toString() + ") is " +std::to_string(left <= right) + " pass.\n";
    count++;

    return count;
}

/**
 * @brief Test with big int(number > 10^20)
 * 
 * @param left first number used for building big int
 * @param right second number used for building big int
 * @return std::int64_t return the number of correct test
 */
std::int64_t testLongInt(const std::int64_t left, const std::int64_t right){
    bigint bLeft(std::to_string(left) + std::to_string(left) + std::to_string(right) + std::to_string(right));
    bigint bRight(std::to_string(left) + std::to_string(right) + std::to_string(left) + std::to_string(right));
    std::int64_t count = 0;

    bigint temp(0);

    temp = bLeft + bRight;
    if((temp - bRight) != bLeft)
        throw wrong_result("Big Int Test : ("+ bLeft.toString() + ") + & - (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Big Int Test : ("+ bLeft.toString() + ") + & - (" + bRight.toString() + ") pass.\n";
    count++;

    temp = bLeft * bRight;
    if((temp / bRight) != bLeft)
        throw wrong_result("Big Int Test : ("+ bLeft.toString() + ") * & / (" + bRight.toString() + ") has wrong result.");

    std::cout<<"Big Int Test : ("+ bLeft.toString() + ") * & / (" + bRight.toString() + ") pass.\n";
    count++;

    return count;
}