#include <iostream>
#include "Assert.cpp"

using namespace std;

int main(){
    auto assert = Assert();

    assert.thatFn([]{
        Assert().that(1).equals(1);
    }).notThrows();

    assert.thatFn([]{
        Assert().that(1).equals(2);
    }).throws();

    assert.thatFn([]{
        Assert().that(true).equals(true);
    }).notThrows();

    assert.thatFn([]{
        Assert().that(false).equals(false);
    }).notThrows();

    assert.thatFn([]{
        Assert().that(false).equals(true);
    }).throws();

    assert.thatFn([]{
        Assert().that(true).equals(false);
    }).throws();

    assert.thatFn([]{
        Assert().that("foo").equals("foo");
    }).notThrows();

    assert.thatFn([]{
        Assert().that("foo").equals("bar");
    }).throws();

    assert.thatFn([]{
        string foo1 = "foo";
        string foo2 = "foo";
        Assert().that(foo1).equals(foo2);
    }).notThrows();

    assert.thatFn([]{
        string foo = "foo";
        string bar = "bar";
        Assert().that(foo).equals(bar);
    }).throws();

    assert.thatFn([]{
        string foo = "foo";
        Assert().that(foo).equals("foo");
    }).notThrows();

    assert.thatFn([]{
        string foo = "foo";
        const char * bar = "bar";
        Assert().that(foo).equals(bar);
    }).throws();

    assert.thatFn([]{
        string foo_string = "foo";
        const char * foo_charpointer = "foo";
        Assert().that(foo_string).equals(foo_charpointer);
    }).notThrows();

    assert.thatFn([]{
        string bar = "bar";
        Assert().that("foo").equals(bar);
    }).throws();

    assert.thatFn([]{
        Assert().that(1).equals(true);
    }).throws();

    assert.thatFn([]{
        Assert().that(true).equals(1);
    }).throws();

    assert.thatFn([]{
        Assert().that(0).equals(false);
    }).throws();

    assert.thatFn([]{
        Assert().that(false).equals(0);
    }).throws();

    printf("OK!\n");
}
