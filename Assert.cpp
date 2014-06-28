#include <exception>

using namespace std;

class ExpectationMismatch : public exception{
    private:
        string why;

    public:
        ExpectationMismatch(string why){
            this->why = why;
        }

        virtual const char* what() const throw(){
            return this->why.c_str();
        }
};

class Assert{
    private:
        enum Type {BOOL, STRING, INT};

        Type t;
        bool actualBool;
        string actualString;
        int actualInt;

        void AssertInitString(string s){
            this->t = STRING;
            this->actualString = s;
        }

        void mismatch(string actual, string expected){
            throw ExpectationMismatch("Expected (" + actual + ") to be (" + expected + ")");
        }
        void checkT(Type actual){
            if (this->t != actual)
                throw ExpectationMismatch("Expected to be a " + str(actual) + "!");
        }
        string str(bool value){
            return value == true? "true" : "false";
        }
        string str(int value){
            return to_string(value);
        }
        string str(Type t){
            switch(t){
                case BOOL:
                    return "bool";
                case STRING:
                    return "string";
                case INT:
                    return "int";
                default:
                    throw exception();
            }
        }

    public:
        Assert(bool actual){
            this->t = BOOL;
            this->actualBool = actual;
        }
        Assert(string actual){
            this->AssertInitString(actual);
        }
        Assert(const char * actual){
            this->AssertInitString(string(actual));
        }
        Assert(int actual){
            this->t = INT;
            this->actualInt = actual;
        }

        void toBe(bool expected){
            this->checkT(BOOL);
            if (this->actualBool != expected)
                this->mismatch(str(this->actualBool), str(expected));
        }
        void toBe(string expected){
            this->checkT(STRING);
            if (this->actualString.compare(expected) != 0){
                this->mismatch(this->actualString, expected);
            }
        }
        void toBe(const char * expected){
            this->toBe(string(expected));
        }
        void toBe(int expected){
            this->checkT(INT);
            if (this->actualInt != expected)
                this->mismatch(str(this->actualInt), str(expected));
        }
};

