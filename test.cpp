#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "matrix.h"
#include "list.h"

TEST_CASE("List: new list is empty") {
    List<int> l;
    CHECK(l.is_empty() == 1);
    CHECK(l.at_beg() == 1);
    CHECK(l.at_end() == 1);
}

TEST_CASE("List: insertion") {
    List<int> l;
    Matrix<int> a(2);

    SUBCASE("ins_before") {
        CHECK(l.ins_before(a) == 0);
        CHECK(l.is_empty() == 0);
        CHECK(l.at_beg() == 0);
        CHECK(l.at_end() == 1);
    }

    SUBCASE("ins_after") {
        CHECK(l.ins_after(a) == 0);
        CHECK(l.is_empty() == 0);
        CHECK(l.at_beg() == 1);
        CHECK(l.at_end() == 0);
    }
}

TEST_CASE("List: moving the cursors") {
    List<int> l;
    Matrix<int> a(2);
    for (int i = 0; i < 3; ++i) {
        REQUIRE(l.ins_before(a) == 0);
    }

    l.go_to_beg();
    CHECK(l.at_beg() == 1);
    CHECK(l.at_end() == 0);

    CHECK(l.step_forward() == 0);
    CHECK(l.at_beg() == 0);
    CHECK(l.step_forward() == 0);
    CHECK(l.step_forward() == 0);
    CHECK(l.at_end() == 1);

    SUBCASE("step outside the end") {
        CHECK(l.step_forward() == -1);
    }

    SUBCASE("step backward") {
        CHECK(l.step_backward() == 0);
        CHECK(l.at_end() == 0);
        l.go_to_beg();
        CHECK(l.step_backward() == -1);
    }
}

TEST_CASE("List: get and set") {
    List<int> l;
    Matrix<int> a(2), res(2);
    REQUIRE(l.ins_before(a) == 0);

    SUBCASE("cursor at the end") {
        l.go_to_end();
        CHECK(l.get_before(res) == 0);
        CHECK(l.set_before(a) == 0);
        CHECK(l.get_after(res) == -1);
        CHECK(l.set_after(a) == -1);
    }

    SUBCASE("cursor at the beginning") {
        l.go_to_beg();
        CHECK(l.get_before(res) == -1);
        CHECK(l.set_before(a) == -1);
        CHECK(l.get_after(res) == 0);
        CHECK(l.set_after(a) == 0);
    }
}

TEST_CASE("List: deletion") {
    List<int> l;
    Matrix<int> a(2);
    for (int i = 0; i < 3; ++i) {
        REQUIRE(l.ins_before(a) == 0);
    }

    SUBCASE("delete outside the list") {
        l.go_to_end();
        CHECK(l.del_after() == -1);
        l.go_to_beg();
        CHECK(l.del_before() == -1);
    }

    SUBCASE("delete before the cursor") {
        l.go_to_end();
        CHECK(l.del_before() == 0);
        CHECK(l.del_before() == 0);
        CHECK(l.is_empty() == 0);
        CHECK(l.del_before() == 0);
        CHECK(l.is_empty() == 1);
    }

    SUBCASE("delete after the cursor") {
        l.go_to_beg();
        CHECK(l.del_after() == 0);
        CHECK(l.del_after() == 0);
        CHECK(l.is_empty() == 0);
        CHECK(l.del_after() == 0);
        CHECK(l.is_empty() == 1);
    }
}

TEST_CASE("List: sum and mul") {
    List<int> l;
    Matrix<int> a(2), b(2), res(2);
    REQUIRE(l.ins_before(a) == 0);
    REQUIRE(l.ins_before(b) == 0);

    SUBCASE("cursors between two matrices") {
        l.go_to_beg();
        l.step_forward();
        CHECK(l.sum(res) == 0);
        CHECK(l.mul(res) == 0);
    }

    SUBCASE("cursor at the beginning") {
        l.go_to_beg();
        CHECK(l.sum(res) == -1);
        CHECK(l.mul(res) == -1);
    }

    SUBCASE("cursor at the end") {
        l.go_to_end();
        CHECK(l.sum(res) == -1);
        CHECK(l.mul(res) == -1);
    }
}

TEST_CASE("List: copy constructor and assignment") {
    List<int> original;
    Matrix<int> a(2);
    for (int i = 0; i < 3; ++i) {
        REQUIRE(original.ins_before(a) == 0);
    }
    original.go_to_beg();
    original.step_forward();

    SUBCASE("Copy constructor") {
        List<int> copy(original);
        CHECK(copy.is_empty() == 0);
        CHECK(copy.at_beg() == 0);
        CHECK(copy.at_end() == 0);

        copy.go_to_beg();
        while (!copy.at_end()) {
            copy.del_after();
        }
        CHECK(copy.is_empty() == 1);
        CHECK(original.is_empty() == 0);
    }

    SUBCASE("Assignment and self-assignment") {
        List<int> assigned;
        assigned = original;
        CHECK(assigned.is_empty() == 0);
        CHECK(assigned.at_beg() == 0);
        CHECK(assigned.at_end() == 0);

        assigned = assigned;
        CHECK(assigned.is_empty() == 0);
        CHECK(assigned.at_beg() == 0);
        CHECK(assigned.at_end() == 0);
    }
}

TEST_CASE("List<double>: template works with another type"){
    List<double> l;
    Matrix<double> a(2), b(2), res(2);
    REQUIRE(l.ins_before(a) == 0);
    REQUIRE(l.ins_before(b) == 0);

    l.go_to_beg();
    l.step_forward();
    CHECK(l.sum(res) == 0);
    CHECK(l.mul(res) == 0);
}