#include <iostream>
#include "Assert.cpp"

using namespace std;

int main(){
    auto assert = Assert();

    Assert(true);
    assert.thatFn([]{
        Assert(false);
    }).throws<ExpectationMismatch>();

    Assert().that(1).equals(1);
    assert.thatFn([]{
        Assert().that(1).equals(2);
    }).throws<ExpectationMismatch>();

    Assert().that(true).equals(true);
    Assert().that(false).equals(false);
    assert.thatFn([]{
        Assert().that(false).equals(true);
    }).throws<ExpectationMismatch>();
    assert.thatFn([]{
        Assert().that(true).equals(false);
    }).throws<ExpectationMismatch>();

    Assert().that("foo").equals("foo");
    assert.thatFn([]{
        Assert().that("foo").equals("bar");
    }).throws<ExpectationMismatch>();

    []{
        string foo1 = "foo";
        string foo2 = "foo";
        Assert().that(foo1).equals(foo2);
    }();

    assert.thatFn([]{
        string foo = "foo";
        string bar = "bar";
        Assert().that(foo).equals(bar);
    }).throws<ExpectationMismatch>();

    []{
        string foo = "foo";
        Assert().that(foo).equals("foo");
    }();

    assert.thatFn([]{
        string foo = "foo";
        const char * bar = "bar";
        Assert().that(foo).equals(bar);
    }).throws<ExpectationMismatch>();

    []{
        string foo_string = "foo";
        const char * foo_charpointer = "foo";
        Assert().that(foo_string).equals(foo_charpointer);
    }();

    assert.thatFn([]{
        string bar = "bar";
        Assert().that("foo").equals(bar);
    }).throws<ExpectationMismatch>();

    assert.thatFn([]{
        Assert().that(1).equals(true);
    }).throws<ExpectationMismatch>();

    assert.thatFn([]{
        Assert().that(true).equals(1);
    }).throws<ExpectationMismatch>();

    assert.thatFn([]{
        Assert().that(0).equals(false);
    }).throws<ExpectationMismatch>();

    assert.thatFn([]{
        Assert().that(false).equals(0);
    }).throws<ExpectationMismatch>();

    bool mismatchThrown;

    mismatchThrown = false;
    try {
        Assert().thatFn([]{}).throws();
    } catch (ExpectationMismatch e) {
        mismatchThrown = true;
    }
    assert.that(mismatchThrown).equals(true);

    Assert().thatFn([]{ throw exception(); }).throws();

    mismatchThrown = false;
    try {
        Assert().thatFn([]{}).throws<int>();
    } catch (ExpectationMismatch e) {
        mismatchThrown = true;
    }
    assert.that(mismatchThrown).equals(true);

    Assert().thatFn([]{ throw 5; }).throws<int>();

    printf("OK!\n");
}
