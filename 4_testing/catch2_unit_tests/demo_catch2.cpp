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

TEST_CASE("PushBack", "[LinkList]") {
    SECTION("Add one item and get it back") {
        List l;
        int NewItem = 1;
        l.PushBack(NewItem);
        REQUIRE(l.Size() == 1);
        REQUIRE(l.PopBack() == NewItem);
    }

    SECTION("Add few items and get it back") {
        List l;
        int NewItems[] = { 1,12, -23 };
        for(auto& i : NewItems)
        l.PushBack(i);

        REQUIRE(l.Size() == 3);
        REQUIRE(l.PopBack() == NewItems[2]);
        REQUIRE(l.PopBack() == NewItems[1]);
        REQUIRE(l.PopBack() == NewItems[0]);
    }
}

TEST_CASE("PushFront", "[LinkList]") {
    SECTION("Add one item and get it back") {
        List l;
        int NewItem = 1;
        l.PushFront(NewItem);
        REQUIRE(l.Size() == 1);
        REQUIRE(l.PopFront() == NewItem);
    }

    SECTION("Add few items and get it back") {
        List l;
        int NewItems[] = { 1,12, -23 };
        for (auto i : NewItems)
            l.PushFront(i);

        REQUIRE(l.Size() == 3);
        REQUIRE(l.PopFront() == NewItems[2]);
        REQUIRE(l.PopFront() == NewItems[1]);
        REQUIRE(l.PopFront() == NewItems[0]);
    }
}

TEST_CASE("PopFront", "[LinkList]") {

    SECTION("Get front from empty") {
        List l;
        CHECK_THROWS(l.PopFront());
    }

    SECTION("Add one item to front and get it") {
        List l;
        int NewItem = 1;
        l.PushFront(NewItem);
        REQUIRE(l.Size() == 1);
        REQUIRE(l.PopFront() == NewItem);
    }

    SECTION("Add one item to back and get it") {
        List l;
        int NewItem = 1;
        l.PushBack(NewItem);
        REQUIRE(l.Size() == 1);
        REQUIRE(l.PopFront() == NewItem);
    }

    SECTION("Add few items to Front and get them from Front") {
        List l;
        int NewItems[] = { 1,12, -23 };
        for (auto i : NewItems)
            l.PushFront(i);

        REQUIRE(l.Size() == 3);
        REQUIRE(l.PopFront() == NewItems[2]);
        REQUIRE(l.PopFront() == NewItems[1]);
        REQUIRE(l.PopFront() == NewItems[0]);
        CHECK_THROWS(l.PopFront());
    }

    SECTION("Add few items to Back and get them from Front") {
        List l;
        int NewItems[] = { 1,12, -23 };
        for (auto i : NewItems)
            l.PushBack(i);

        CHECK(l.Size() == 3);
        CHECK(l.PopFront() == NewItems[0]);
        CHECK(l.PopFront() == NewItems[1]);
        CHECK(l.PopFront() == NewItems[2]);
        CHECK_THROWS(l.PopFront());
    }

}

TEST_CASE("PopBack", "[LinkList]") {

    SECTION("Get Back from empty") {
        List l;
        CHECK_THROWS(l.PopBack());
    }

    SECTION("Add one item to back and get it") {
        List l;
        int NewItem = 1;
        l.PushFront(NewItem);
        CHECK(l.Size() == 1);
        CHECK(l.PopBack() == NewItem);
    }

    SECTION("Add one item to back and get it") {
        List l;
        int NewItem = 1;
        l.PushBack(NewItem);
        CHECK(l.Size() == 1);
        CHECK(l.PopBack() == NewItem);
    }

    SECTION("Add few items to Front and get them from back") {
        List l;
        int NewItems[] = { 1,12, -23 };
        for (auto i : NewItems)
            l.PushFront(i);

        CHECK(l.Size() == 3);
        CHECK(l.PopBack() == NewItems[0]);
        CHECK(l.PopBack() == NewItems[1]);
        CHECK(l.PopBack() == NewItems[2]);
        CHECK_THROWS(l.PopBack());
    }

    SECTION("Add few items to Back and get them from Back") {
        List l;
        int NewItems[] = { 1,12, -23 };
        for (auto i : NewItems)
            l.PushBack(i);

        CHECK(l.Size() == 3);
        CHECK(l.PopBack() == NewItems[2]);
        CHECK(l.PopBack() == NewItems[1]);
        CHECK(l.PopBack() == NewItems[0]);
        CHECK_THROWS(l.PopBack());
    }
}


TEST_CASE("Mixed", "[LinkList]") {
    List l;
    int NewItems[] = { 1,12, -23, 1, 0, 111, -2, -6 };
    for (auto i : NewItems) {
        l.PushBack(i);
        l.PushFront(i);
    }

    int list_size = l.Size();
    CHECK(list_size == 2*sizeof(NewItems) / sizeof(int));

    for (int i = list_size/2 - 1 ; i >= 0; --i) {
        CHECK(l.PopBack() == NewItems[i]);
        CHECK(l.PopFront() == NewItems[i]);
    }

    REQUIRE(l.Size() == 0);
}