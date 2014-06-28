#include <iostream>
#include "Assert.cpp"

using namespace std;

class ClassUnderTest{
    public:
        string doSomething(){
            return "actual result";
        }
};

int main(){
    Assert( ClassUnderTest().doSomething() ).toBe( "expected result" );

    printf("Done!\n");
    return 0;
}
