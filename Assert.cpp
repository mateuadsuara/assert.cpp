#include <exception>
#include <functional>

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

class ThatBool{
    private:
        bool actual;

        void mismatch(string actual, string expected){
            throw ExpectationMismatch("Expected (" + actual + ") to equal (" + expected + ")");
        }
        string str(bool value){
            return value == true? "true" : "false";
        }

    public:
        ThatBool(bool actual){
            this->actual = actual;
        }

        ThatBool equals(bool expected){
            if (actual != expected)
                this->mismatch(str(this->actual), str(expected));

            return *this;
        }
};

class ThatString{
    private:
        string actual;

        void mismatch(string actual, string expected){
            throw ExpectationMismatch("Expected (" + actual + ") to equal (" + expected + ")");
        }

    public:
        ThatString(string actual){
            this->actual = actual;
        }
        ThatString(const char * actual){
            this->actual = string(actual);
        }

        ThatString equals(string expected){
            if (this->actual.compare(expected) != 0){
                this->mismatch(this->actual, expected);
            }
            return *this;
        }
        ThatString equals(const char * expected){
            this->equals(string(expected));
            return *this;
        }
};

class ThatInt{
    private:
        int actual;

        void mismatch(string actual, string expected){
            throw ExpectationMismatch("Expected (" + actual + ") to equal (" + expected +   ")");
        }
        string str(int value){
            return to_string(value);
        }

    public:
        ThatInt(int actual){
            this->actual = actual;
        }

        ThatInt equals(int expected){
            if (this->actual != expected){
                this->mismatch(str(this->actual), str(expected));
            }

            return *this;
        }
};

class ThatVoidFunction{
    private:
        function<void()> fn;
        
        bool doThrows(){
            bool thrown = false;
            try {
                this->fn();
            } catch (...) {
                thrown = true;
            }
            return thrown;
        }

    public:
        ThatVoidFunction(function<void()> fn){
            this->fn = fn;
        }

        void throws(){
            if (!this->doThrows())
                throw ExpectationMismatch("Expected to throw exception");
        }

        void notThrows(){
            if (this->doThrows())
                throw ExpectationMismatch("Expected to not throw exception");
        }
};

class Assert{
    public:
        Assert(){}

        ThatBool that(bool actual){
            return ThatBool(actual);
        }
        ThatString that(string actual){
            return ThatString(actual);
        }
        ThatInt that(int actual){
            return ThatInt(actual);
        }
        ThatVoidFunction thatFn(function<void()> fn){
            return ThatVoidFunction(fn);
        }
};

