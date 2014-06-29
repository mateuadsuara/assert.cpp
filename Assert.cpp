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
        string str(int value){
            return to_string(value);
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

        void equals(int notEqualType){
            this->mismatch(str(this->actual), str(notEqualType));
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
            if (this->actual != expected){
                this->mismatch(this->actual, expected);
            }
            return *this;
        }
        ThatString equals(const char * expected){
            return this->equals(string(expected));
        }
};

class ThatInt{
    private:
        int actual;

        void mismatch(string actual, string expected){
            throw ExpectationMismatch("Expected (" + actual + ") to equal (" + expected + ")");
        }
        string str(bool value){
            return value == true? "true" : "false";
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
        
        void equals(bool notEqualType){
            this->mismatch(str(this->actual), str(notEqualType));
        }
};

class ThatVoidFunction{
    private:
        function<void()> fn;
        
        bool doThrowsAny(){
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
            if (!this->doThrowsAny())
                throw ExpectationMismatch("Expected to throw something");
        }

        template <typename E>
        void throws(){
            bool thrown = false;
            try {
                this->fn();
            } catch (E e) {
                thrown = true;
            }

            if (!thrown)
                throw ExpectationMismatch("Expected to throw something of the specified type");
        }
};

class Assert{
    public:
        Assert(){}
        Assert(bool expectedTrue){
            ThatBool(expectedTrue).equals(true);
        }

        ThatBool that(bool actual){
            return ThatBool(actual);
        }
        ThatString that(string actual){
            return ThatString(actual);
        }
        ThatString that(const char * actual){
            return ThatString(string(actual));
        }
        ThatInt that(int actual){
            return ThatInt(actual);
        }
        ThatVoidFunction thatFn(function<void()> fn){
            return ThatVoidFunction(fn);
        }
};

