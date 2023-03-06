#include <iostream>
#include "linked_list.h"
#include "catch_test_macros.hpp"

TEST_CASE("Empty", "[LinkList]") {
    List l;
    REQUIRE(l.Empty() == true);
    l.PushBack(1);
    REQUIRE(l.Empty() == false);
    l.PopFront();
    REQUIRE(l.Empty() == true);
}

TEST_CASE("Size", "[LinkList]") {
    List l;
    REQUIRE(l.Size() == 0);
    l.PushFront(1);
    REQUIRE(l.Size() == 1);
    l.PopBack();
    REQUIRE(l.Size() == 0);
}

TEST_CASE("Clear", "[LinkList]") {
    List l;
    l.PushFront(1);
    l.PushBack(1);
    l.Clear();
    REQUIRE(l.Size() == 0);
    l.PushBack(1);
    l.PushFront(-1);
    l.Clear();
    REQUIRE(l.Size() == 0);
    l.Clear();
    REQUIRE(l.Size() == 0);
}