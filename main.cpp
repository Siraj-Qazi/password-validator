#include <iostream>
#include <string>

class StringValidator {
public:
    virtual ~StringValidator() {};

    virtual bool isValid(std::string input) = 0;
    virtual std::string validationType(void) = 0;
};

class MinLengthValidator {
public:
    MinLengthValidator(int min) {
        if (min > 0)
            min_length = min;
    }

    bool isValid(std::string input) {
        return input.length() >= min_length;
    }

private:
    int min_length;

};

class MaxLengthValidator {
public:
    MaxLengthValidator(int max) {
        if (max > 0)
            max_length = max;
    }

    bool isValid(std::string input) {
        return input.length() <= max_length;
    }

private:
    int max_length;

};

class LengthValidator : public StringValidator {
public:
    LengthValidator(int min, int max);

    bool isValid(std::string input);

    std::string validationType() {
        return "Length Validator: ";
    }

private:
    MinLengthValidator min_validator;
    MaxLengthValidator max_validator;
};

LengthValidator::LengthValidator(int min, int max) : min_validator(min), max_validator(max) {}

bool LengthValidator::isValid(std::string input) {
    return (min_validator.isValid(input) && max_validator.isValid(input));

}

class UpperCaseValidator {
public:
    UpperCaseValidator(std::string input) {
        test_string = input;
    }

    bool isValid(std::string input) {
        for (auto i : test_string)
            if (isupper(i))
                return true;
        return false;
    }

private:
    std::string test_string;
};

class LowerCaseValidator {
public:
    LowerCaseValidator(std::string input) {
        test_string = input;
    }

    bool isValid(std::string input) {
        for (auto i : test_string)
            if (islower(i))
                return true;
        return false;
    }


private:
    std::string test_string;
};

class CaseValidator : public StringValidator {
public:
    CaseValidator(std::string input) : uppercase_validator(input), lowercase_validator(input) {}

    bool isValid(std::string input) {
        return (uppercase_validator.isValid(input) && lowercase_validator.isValid(input));
    }

    std::string validationType() {
        return "Case Validator: ";
    }

private:
    UpperCaseValidator uppercase_validator;
    LowerCaseValidator lowercase_validator;
};

class DigitValidator : public StringValidator {
public:
    DigitValidator(std::string input) {
        test_string = input;
    }

    bool isValid(std::string input) {
        for (auto i : test_string)
            if (isdigit(i))
                return true;

        return false;
    }

    std::string validationType() {
        return "Digit Validator: ";
    }

private:
    std::string test_string;
};


class SpecialCharacterValidator : public StringValidator {
public:
    SpecialCharacterValidator(std::string input) {
        test_string = input;
    }

    bool isValid(std::string input) {
        for (auto i : test_string)
            if (!isalpha(i))
                return true;

        return false;
    }

    std::string validationType() {
        return "Special Character Validator: ";
    }

private:
    std::string test_string;
};

using namespace std;

void printValid(StringValidator *validator, string input) {
    cout << "The string '" << input << "' is "
         << (validator->isValid(input) ? "valid" : "invalid");
}


int main() {

    std::cout <<"\n Enter input string: > ";
    std::string input;
    std::getline(std::cin, input);

    StringValidator* passwordValidator[4];

    LengthValidator lengthValidator(8,32);
    CaseValidator caseValidator(input);
    SpecialCharacterValidator specialCharacterValidator(input);
    DigitValidator digitValidator(input);

    passwordValidator[0] = &lengthValidator;
    passwordValidator[1] = &caseValidator;
    passwordValidator[2] = &specialCharacterValidator;
    passwordValidator[3] = &digitValidator;

    bool isValid = true;
    for(int i = 0; i < 4; ++i) {
        std::cout << "\n "<< passwordValidator[i]->validationType();
        printValid(passwordValidator[i],input);
    }

    std::cout<<"\n --------- \n";

}
