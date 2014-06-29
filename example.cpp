#include <iostream>
#include "Assert.cpp"

using namespace std;

class ClassUnderTest{
    public:
        string doSomething(){
            return "result";
        }
        
        void throwException(){
            throw exception();
        }
};

int main(){
    auto assert = Assert();

    assert
        .that(
            ClassUnderTest().doSomething()
        )
        .equals(
            "result"
        );

    assert
        .thatFn([]{
            ClassUnderTest().throwException();
        })
        .throws();

    printf("Done!\n");
    return 0;
}
