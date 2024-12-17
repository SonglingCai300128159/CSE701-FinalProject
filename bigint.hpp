#include <iostream>
#include <string>
enum sign {POSITIVE, NEGATIVE};

class bigint{
    public:
        bigint();//constrctor with no arguement
        bigint(const std::int64_t &_rawNumber);//constrctor with a signed 64-bit integer
        bigint(const std::string &_rawNumber);//constrctor with a string
        bigint(const std::string &_rawNumber, const std::int64_t &base);

        bigint& operator+=(const bigint& rBigint);
        bigint& operator-=(const bigint& rBigint);
        bigint& operator*=(const bigint& rBigint);
        bigint& operator/=(const bigint& rBigint);
        bigint& operator%=(const bigint& rBigint);

        bigint& operator++();
        bigint operator++(int);
        bigint& operator--();
        bigint operator--(int);

        bigint pow(const bigint& base, const std::uint64_t& exp);

        std::string toString() const;
        std::string toString(const std::int64_t& base) const;
   
        void inverseSign();
        std::string getNumberBody() const;
        sign getSign() const;

    private:
        std::string numberBody = "0";
        sign numberSign = POSITIVE; 

        void changeNumberBody(const std::string &_rawNumberBody);
        void changeNumberSign(const sign &_rawNumberSign);

        std::string pureAdder(const std::string& rawLeft, const std::string& rawRight);
        std::string pureSubtracter(const std::string& rawLeft, const std::string& rawRight);
        std::string pureMulti(const std::string& rawLeft, const std::string& rawRight);
        std::string pureDiv(const std::string& rawLeft, const std::string& rawRight);
        

        std::int64_t lookUpTableCharToInt(const char& _rawBit) const;
        char lookUpTableIntToChar(const std::int64_t& _rawBit) const;

};

std::ostream& operator<<(std::ostream& out, const bigint& _rawNumber);
bool operator==(const bigint& lBigint, const bigint& rBigint);
bool operator!=(const bigint& lBigint, const bigint& rBigint);
bool operator<(const bigint& lBigint, const bigint& rBigint);
bool operator<=(const bigint& lBigint, const bigint& rBigint);
bool operator>(const bigint& lBigint, const bigint& rBigint);
bool operator>=(const bigint& lBigint, const bigint& rBigint);
bigint operator+(const bigint& lBigint, const bigint& rBigint);
bigint operator-(const bigint& lBigint, const bigint& rBigint);
bigint operator*(const bigint& lBigint, const bigint& rBigint);
bigint operator/(const bigint& lBigint, const bigint& rBigint);
bigint operator%(const bigint& lBigint, const bigint& rBigint);

/**
 * @brief Construct a new bigint::bigint object with default arguement
 * 
 */

bigint::bigint(){
    changeNumberBody("0");
    changeNumberSign(POSITIVE);
}

/**
 * @brief Construct a new bigint::bigint object with int arguement
 * 
 * @param _rawNumber target int arguement
 */
bigint::bigint(const std::int64_t &_rawNumber){
    if(_rawNumber >= 0){
        changeNumberBody(std::to_string(_rawNumber));
        changeNumberSign(POSITIVE);
    }else{
        changeNumberBody(std::to_string(-(_rawNumber)));
        changeNumberSign(NEGATIVE);
    }
}

/**
 * @brief Construct a new bigint::bigint object with string arguement
 * 
 * @param _rawNumber target string arguement
 */
bigint::bigint(const std::string &_rawNumber){
    if( !(((std::int64_t)_rawNumber[0]>=48 && (std::int64_t)_rawNumber[0]<=57) || (std::int64_t)_rawNumber[0]==45 || (std::int64_t)_rawNumber[0]==43))
        throw std::invalid_argument("First char of bigint should be +, -, or number omly");

    for(std::uint64_t i = 1; i < _rawNumber.length() ; i++){
        if((std::int64_t)_rawNumber[i]>=48 && (std::int64_t)_rawNumber[i]<=57)
            continue;
        else
            throw std::invalid_argument(std::to_string(i+1)+" char of bigint should be number omly");
    }

    if((std::int64_t)_rawNumber[0]==43){
        std::string temp = "";
        for(std::uint64_t i = 1; i < _rawNumber.length() ; i++){
            temp = temp + _rawNumber[i];
        }
        changeNumberBody(temp);
        changeNumberSign(POSITIVE);
    }
    else if((std::int64_t)_rawNumber[0]==45){
        std::string temp = "";
        for(std::uint64_t i = 1; i < _rawNumber.length() ; i++){
            temp = temp + _rawNumber[i];
        }
        changeNumberBody(temp);
        changeNumberSign(NEGATIVE);
    }
    else{
        std::string temp = "";
        for(std::uint64_t i = 0; i < _rawNumber.length() ; i++){
            temp = temp + _rawNumber[i];
        }
        changeNumberBody(temp);
        changeNumberSign(POSITIVE);
    }
    
}

/**
 * @brief Construct a new bigint::bigint object with string target and a base
 * 
 * @param _rawNumber target string
 * @param _rawbase target base
 */
bigint::bigint(const std::string &_rawNumber, const std::int64_t &_rawbase){
    bigint base(_rawbase);

    changeNumberBody("0");
    changeNumberSign(POSITIVE);

    if( !(((std::int64_t)_rawNumber[0]>=48 && (std::int64_t)_rawNumber[0]<=57) || ((std::int64_t)_rawNumber[0]>=65 && (std::int64_t)_rawNumber[0]<=70) || (std::int64_t)_rawNumber[0]==45 || (std::int64_t)_rawNumber[0]==43))
        throw std::invalid_argument("First char of bigint should be +, -, A-F, or number omly");

    for(std::uint64_t i = 1; i < _rawNumber.length() ; i++){
        if(((std::int64_t)_rawNumber[i]>=48 && (std::int64_t)_rawNumber[i]<=57) || ((std::int64_t)_rawNumber[i]>=65 && (std::int64_t)_rawNumber[i]<=70))
            continue;
        else
            throw std::invalid_argument(std::to_string(i+1)+" char of bigint should be number or A-F omly");
    }
    
    if((std::int64_t)_rawNumber[0]==43){
        for(std::uint64_t i = 1; i < _rawNumber.length(); i++){
            bigint temp(lookUpTableCharToInt(_rawNumber[i]));
            temp *= pow(base, (_rawNumber.length() - i - 1));
            *this += temp;
        }
    }
    else if((std::int64_t)_rawNumber[0]==45){
        for(std::uint64_t i = 1; i < _rawNumber.length(); i++){
            bigint temp(lookUpTableCharToInt(_rawNumber[i]));
            temp *= pow(base, (_rawNumber.length() - i - 1));
            *this += temp;
        }
        inverseSign();
    }
    else{
        for(std::uint64_t i = 0; i < _rawNumber.length(); i++){
            bigint temp(lookUpTableCharToInt(_rawNumber[i]));
            temp *= pow(base, (_rawNumber.length() - i - 1));
            *this += temp;
        }
    }
}

/**
 * @brief private function to change the number itself
 * 
 * @param _rawNumberBody target to change number itself
 */
void bigint::changeNumberBody(const std::string &_rawNumberBody){
    numberBody = _rawNumberBody;
}

/**
 * @brief private function to change the number sign
 * 
 * @param _rawNumberSign target number sign
 */
void bigint::changeNumberSign(const sign &_rawNumberSign){
    numberSign = _rawNumberSign;
}

/**
 * @brief public const function to get the number itself 
 * 
 * @return std::string number itself
 */
std::string bigint::getNumberBody() const{
    return numberBody;
}

/**
 * @brief public function to get the number sign
 * 
 * @return sign number sign
 */
sign bigint::getSign() const{
    return numberSign;
}

/**
 * @brief public function to inverse the number sign
 * 
 */
void bigint::inverseSign(){
    if(numberSign == POSITIVE)
        numberSign = NEGATIVE;
    else
        numberSign = POSITIVE;
}

/**
 * @brief private function to get the result of A + B without considering of sign, assume that both a and b are positive
 * 
 * @param rawLeft left number to add
 * @param rawRight right number to add
 * @return std::string return the sum of numbers in string type
 */
std::string bigint::pureAdder(const std::string& rawLeft, const std::string& rawRight){
    std::string left = "", right = "", result = "";
    bool carry = false;

    if(rawLeft.length() > rawRight.length()){
        left = rawLeft;
        for(std::uint64_t i = 0; i < (rawLeft.length()-rawRight.length()); i++){
            right = right + "0";
        }
        right = right + rawRight;
    }
    else if(rawLeft.length() < rawRight.length()){
        left = rawRight;
        for(std::uint64_t i = 0; i < (rawRight.length()-rawLeft.length()); i++){
            right = right + "0";
        }
        right = right + rawLeft;
    }
    else{
        left = rawLeft;
        right = rawRight;
    }

    for(std::uint64_t i = left.length(); i > 0; i--){
        if(carry){
            result = std::to_string((((std::int64_t)left[i-1] - 48) + ((std::int64_t)right[i-1] - 48) + 1) % 10) + result;
            if(((std::int64_t)left[i-1] - 48 + (std::int64_t)right[i-1] - 48) + 1 < 10){
                carry = false;
            }
        }
        else{
            result = std::to_string((((std::int64_t)left[i-1] - 48) + ((std::int64_t)right[i-1] - 48)) % 10) + result;
            if(((std::int64_t)left[i-1] - 48 + (std::int64_t)right[i-1] - 48) >= 10){
                carry = true;
            }
        }
    }

    if(carry)
        result = "1" + result;

    return result;
}

/**
 * @brief private function to calcuate A - B without considering of sign, assume that both A and B are positive and A > B
 * 
 * @param rawLeft left number to sub
 * @param rawRight right number to sub
 * @return std::string the sub of result in string type
 */
std::string bigint::pureSubtracter(const std::string& rawLeft, const std::string& rawRight){
    std::string left = "", right = "", rawResult = "", result = "0";
    bool borrow = false, zeroFlag = false;

    left = rawLeft;
    for(std::uint64_t i = 0; i < (rawLeft.length()-rawRight.length()); i++){
        right = right + "0";
    }
    right = right + rawRight;

    for(std::uint64_t i = left.length(); i > 0; i--){
        if(borrow){
            if(((std::int64_t)left[i-1] - 48 - 1 - ((std::int64_t)right[i-1] - 48)) < 0){
                rawResult = std::to_string(((std::int64_t)left[i-1] - 48 - 1) - ((std::int64_t)right[i-1] - 48) + 10) + rawResult;
            }
            else{
                rawResult = std::to_string(((std::int64_t)left[i-1] - 48 - 1) - ((std::int64_t)right[i-1] - 48)) + rawResult;
                borrow = false;
            }
        }
        else{
            if(((std::int64_t)left[i-1] - 48 - ((std::int64_t)right[i-1] - 48)) < 0){
                rawResult = std::to_string(((std::int64_t)left[i-1] - 48) - ((std::int64_t)right[i-1] - 48) + 10) + rawResult;
                borrow = true;
            }
            else{
                rawResult = std::to_string(((std::int64_t)left[i-1] - 48) - ((std::int64_t)right[i-1] - 48)) + rawResult;
            }
        }
    }

    for(std::uint64_t i = 0; i < rawResult.length(); i++){
        if(rawResult[i] != '0' && (!zeroFlag)){
            zeroFlag = true;
            result = "";
        }
        if(zeroFlag)
            result = result + rawResult[i];
    }

    return result;

}

/**
 * @brief private function to calcuate A * B without considering of sign, assume that both A and B are positive
 * 
 * @param rawLeft left number to multi
 * @param rawRight right number to multi
 * @return std::string the multi of result in string type
 */
std::string bigint::pureMulti(const std::string& rawLeft, const std::string& rawRight){
    std::string result = "0", temp = "0", right = rawRight;
    for(std::uint64_t i = 0; i< right.length(); i++){
        int rightBit = right[i] - 48;
        temp = "0";
        while(rightBit != 0){
            temp = pureAdder(rawLeft, temp);
            rightBit--;
        }
        std::string covering((right.length() - i - 1), '0');
        temp = temp + covering;
        result = pureAdder(result, temp);
    }
    if(result[0] == '0')
        return "0";
    return result;
}

std::string bigint::pureDiv(const std::string& rawLeft, const std::string& rawRight){
    std::string result = "", resultCount = "0";
    bigint bLeft(rawLeft), bRight(rawRight), restValue("0"), bTen("10");
    bool startRecord = false;

    for(std::uint64_t i = 0; i< rawLeft.length(); i++){
        std::string temp(1,rawLeft[i]);
        bigint dividendBit(temp);
        dividendBit += restValue;
        while(dividendBit >= bRight ){
            dividendBit -= bRight;
            resultCount = pureAdder(resultCount, "1");
        }
        restValue = dividendBit * bTen;

        if(resultCount != "0")
            startRecord = true;
        if(startRecord)
            result = result + resultCount;
        resultCount = "0";
    }
    if(!startRecord)
        return "0";

    return result;
}

/**
 * @brief default toString function 
 * 
 * @return std::string the format is sign + number
 */
std::string bigint::toString() const{
    if(numberBody == "0")
        return "0";
    if(numberSign == POSITIVE)
        return "+" + numberBody;
    else
        return "-" + numberBody;
}

/**
 * @brief The toString to print a string with a given base
 * 
 * @param rawBase the given base
 * @return std::string result string and the format is sign + number
 */
std::string bigint::toString(const std::int64_t& rawBase) const{
    bigint temp = *this, temp2 = *this, base(rawBase);
    std::string result = "";

    if(numberBody == "0")
        return "0";

    while( temp.getNumberBody() != "0"){
        temp2 %= base;
        result = lookUpTableIntToChar(std::stoi(temp2.getNumberBody())) + result;
        temp /= base;
        temp2 = temp;
    }

    if(numberSign == POSITIVE)
        return "+" + result;
    else
        return "-" + result;
}

/**
 * @brief The overload of printing into a stream 
 * 
 * @param out std::ostream&
 * @param _rawNumber number itself
 * @return std::ostream& result string
 */
std::ostream& operator<<(std::ostream& out, const bigint& _rawNumber){
    out << _rawNumber.toString();
    return out;
}

/**
 * @brief The overload of ==
 * 
 * @param lBigint left bigint 
 * @param rBigint right bigint
 * @return true if left bigint == right bigint
 * @return false if left bigint != right bigint
 */
bool operator==(const bigint& lBigint, const bigint& rBigint){
    std::string left = lBigint.toString();
    std::string right = rBigint.toString();

    if(left[0] != right[0] || left.length() != right.length())
        return false;
    for(std::uint64_t i = 1; i<left.length(); i++){
        if(left[i] != right[i])
            return false;
    }
    return true;
}

/**
 * @brief The overload of ==
 * 
 * @param lBigint left bigint 
 * @param rBigint right bigint
 * @return true true if left bigint != right bigint
 * @return false false if left bigint == right bigint
 */
bool operator!=(const bigint& lBigint, const bigint& rBigint){
    return !(lBigint == rBigint);
}

/**
 * @brief The overload of <
 * 
 * @param lBigint left bigint 
 * @param rBigint right bigint
 * @return true true if left bigint < right bigint
 * @return false false if left bigint >= right bigint
 */
bool operator<(const bigint& lBigint, const bigint& rBigint){
    std::string left = lBigint.toString();
    std::string right = rBigint.toString();

    if(left == "0"){
        if(right[0] == '+')
            return true;
        else
            return false;
    }
    if(right == "0"){
        if(left[0] == '-')
            return true;
        else
            return false;
    }

    if(left[0] != right[0]){
        if(left[0] == '-')
            return true;
        else
            return false;
    }

    if(left[0] == '+'){
        if(left.length() < right.length())
            return true;
        else if(left.length() > right.length())
            return false;
        else{
            for(std::uint64_t i = 1; i < left.length(); i++){
                if(left[i] == right [i])
                    continue;
                else if(left[i] < right [i])
                    return true;
                else
                    return false;
            }
            return false;
        }
    }
    else{
        if(left.length() > right.length())
            return true;
        else if(left.length() < right.length())
            return false;
        else{
            for(std::uint64_t i = 1; i < left.length(); i++){
                if(left[i] == right [i])
                    continue;
                else if(left[i] < right [i])
                    return false;
                else
                    return true;
            }
            return false;
        }
    }
}

/**
 * @brief The overload of <=
 * 
 * @param lBigint left bigint 
 * @param rBigint right bigint
 * @return true true if left bigint <= right bigint
 * @return false false if left bigint > right bigint
 */
bool operator<=(const bigint& lBigint, const bigint& rBigint){
    if(lBigint == rBigint || lBigint < rBigint)
        return true;
    else
        return false;
}

/**
 * @brief The overload of >
 * 
 * @param lBigint left bigint 
 * @param rBigint right bigint
 * @return true true if left bigint > right bigint
 * @return false false if left bigint <= right bigint
 */
bool operator>(const bigint& lBigint, const bigint& rBigint){
    return !(lBigint <= rBigint);
}

/**
 * @brief The overload of >=
 * 
 * @param lBigint left bigint 
 * @param rBigint right bigint
 * @return true true if left bigint >= right bigint
 * @return false false if left bigint < right bigint
 */
bool operator>=(const bigint& lBigint, const bigint& rBigint){
    return !(lBigint < rBigint);
}

/**
 * @brief The overload of -, negation
 * 
 * @param lBigint the target of negation bigint
 * @return bigint the result of negation bigint
 */
bigint operator-(bigint& lBigint){
    lBigint.inverseSign();
    return lBigint;
}

/**
 * @brief The overload of +=, add another number to itself
 * 
 * @param rBigint the right number to add
 * @return bigint& the reference of result
 */
bigint& bigint::operator+=(const bigint& rBigint){
    if(getSign() == rBigint.getSign()){
        changeNumberBody(pureAdder(getNumberBody(), rBigint.getNumberBody()));
    }
    else{
        if(getSign() == POSITIVE){
            bigint temp = rBigint;
            temp.inverseSign();
            if(*this >= temp){
                changeNumberBody(pureSubtracter(getNumberBody(), rBigint.getNumberBody()));
            }
            else{
                changeNumberBody(pureSubtracter(rBigint.getNumberBody(), getNumberBody()));
                inverseSign();
            }
        }
        else{
            bigint temp = *this;
            temp.inverseSign();
            if(temp > rBigint){
                changeNumberBody(pureSubtracter(getNumberBody(), rBigint.getNumberBody()));
            }
            else{
                changeNumberBody(pureSubtracter(rBigint.getNumberBody(), getNumberBody()));
                inverseSign();
            }
        }
    }

    return *this;
}

/**
 * @brief The overload of +, add two numbers
 * 
 * @param lBigint left number to add
 * @param rBigint right number to add
 * @return bigint result of add
 */
bigint operator+(const bigint& lBigint, const bigint& rBigint){
    bigint temp = lBigint;
    temp += rBigint;
    return temp;
}

/**
 * @brief The overload of -=, sub another number to itself
 * 
 * @param rBigint the right number to sub
 * @return bigint& the reference of result
 */
bigint& bigint::operator-=(const bigint& rBigint){
    if(getSign() != rBigint.getSign()){
        changeNumberBody(pureAdder(getNumberBody(), rBigint.getNumberBody()));
    }
    else{
         if(getSign() == POSITIVE){
            if(*this >= rBigint){
                changeNumberBody(pureSubtracter(getNumberBody(), rBigint.getNumberBody()));
            }
            else{
                changeNumberBody(pureSubtracter(rBigint.getNumberBody(), getNumberBody()));
                inverseSign();
            }
        }
        else{
            if(*this >= rBigint){
                changeNumberBody(pureSubtracter(rBigint.getNumberBody(), getNumberBody()));
                inverseSign();
            }
            else{
                changeNumberBody(pureSubtracter(getNumberBody(), rBigint.getNumberBody()));
            }
        }
    }

    return *this;
}

/**
 * @brief The overload of -, sub two numbers
 * 
 * @param lBigint left number to sub
 * @param rBigint right number to sub
 * @return bigint result of sub
 */
bigint operator-(const bigint& lBigint, const bigint& rBigint){
    bigint temp = lBigint;
    temp -= rBigint;
    return temp;
}

/**
 * @brief The overload of ++, pre-increment
 * 
 * @return bigint& the result of increment
 */
bigint& bigint::operator++(){
    bigint one(1);
    *this += one;
    return *this;
}

/**
 * @brief The overload of ++, post-increment
 * 
 * @return bigint& the result of increment
 */
bigint bigint::operator++(int){
    bigint one(1), temp = *this;
    *this += one;
    return temp;
}

/**
 * @brief The overload of --, pre-decrement
 * 
 * @return bigint& the result of decrement
 */
bigint& bigint::operator--(){
    bigint one(1);
    *this -= one;
    return *this;
}

/**
 * @brief The overload of --, post-decrement
 * 
 * @return bigint& the result of decrement
 */
bigint bigint::operator--(int){
    bigint one(1), temp = *this;
    *this -= one;
    return temp;
}

/**
 * @brief The overload of *=, multi another number to itself
 * 
 * @param rBigint the right number to multi
 * @return bigint& the reference of result
 */
bigint& bigint::operator*=(const bigint& rBigint){
    if(getSign() == rBigint.getSign()){
        changeNumberBody(pureMulti(numberBody, rBigint.getNumberBody()));
        if(getSign() == NEGATIVE)
            inverseSign();
    }
    else{
        changeNumberBody(pureMulti(numberBody, rBigint.getNumberBody()));
        if(getSign() == POSITIVE)
            inverseSign();
    }

    return *this;
}

/**
 * @brief The overload of *, multi two numbers
 * 
 * @param lBigint left number to multi
 * @param rBigint right number to multi
 * @return bigint result of multi
 */
bigint operator*(const bigint& lBigint, const bigint& rBigint){
    bigint temp = lBigint;
    temp *= rBigint;
    return temp;
}

/**
 * @brief The overload of /=, div another number to itself
 * 
 * @param rBigint the right number to div
 * @return bigint& the reference of result
 */
bigint& bigint::operator/=(const bigint& rBigint){
    if(rBigint.getNumberBody() == "0")
        throw std::invalid_argument("Divisior can't be 0");
    if(getSign() == rBigint.getSign()){
        changeNumberBody(pureDiv(numberBody, rBigint.getNumberBody()));
        if(getSign() == NEGATIVE)
            inverseSign();
    }
    else{
        changeNumberBody(pureDiv(numberBody, rBigint.getNumberBody()));
        if(getSign() == POSITIVE)
            inverseSign();
    }

    return *this;
}

/**
 * @brief The overload of /, div two numbers
 * 
 * @param lBigint left number to div
 * @param rBigint right number to div
 * @return bigint result of div
 */
bigint operator/(const bigint& lBigint, const bigint& rBigint){
    bigint temp = lBigint;
    temp /= rBigint;
    return temp;
}

/**
 * @brief The overload of %=, mod another number to itself
 * 
 * @param rBigint the right number to mod
 * @return bigint& the reference of result
 */
bigint& bigint::operator%=(const bigint& rBigint){
    bigint temp(0), temprBigint(rBigint.getNumberBody()), templBigint(getNumberBody());

    temp = (templBigint / temprBigint) * temprBigint - templBigint;
    changeNumberBody(temp.getNumberBody());

    return *this;
}

/**
 * @brief The overload of %, mod two numbers
 * 
 * @param lBigint left number to mod
 * @param rBigint right number to mod
 * @return bigint result of mod
 */
bigint operator%(const bigint& lBigint, const bigint& rBigint){
    bigint temp = lBigint;
    temp %= rBigint;
    return temp;
}

/**
 * @brief private function to calcuate a^b, without considering of sign
 * 
 * @param base base number 
 * @param exp exponent number
 * @return bigint result
 */
bigint bigint::pow(const bigint& base, const std::uint64_t& exp){
    bigint temp(1);
    for(std::uint64_t i = 0; i < exp; i++){
        temp *= base;
    }
    return temp;
}

/**
 * @brief private function to convert char from 0 to F into 0 - 16 number
 * 
 * @param _rawBit target char
 * @return std::int64_t result number
 */
std::int64_t bigint::lookUpTableCharToInt(const char &_rawBit) const{
    switch (_rawBit){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return -1;
    }
}

/**
 * @brief private function to convert int from 0 to 16 into char 0 - F 
 * 
 * @param _rawBit target number
 * @return char target char
 */
char bigint::lookUpTableIntToChar(const std::int64_t& _rawBit) const{
    switch (_rawBit){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return '0';
    }
}





