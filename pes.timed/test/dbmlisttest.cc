/**
  * Unit tests for DBMList.
  *
  *
  * @author Peter Fontana
  * @author Jeroen Keiren
  * @copyright MIT Licence, see the accompanying LICENCE.txt.
  */

#include <climits>
#include "DBMList.hh"
#include "testdbms.hh"
#include "gtest/gtest.h"

/** Use this function only for testing! */
bool strictly_equal(const DBMList& xs, const DBMList& ys) {
  return std::equal(xs.begin(), xs.end(), ys.begin(), [](const DBM& x, const DBM& y) { return x == y; });
}

// l1b
DBM testDBM3()
{
    DBM testDBM3(0, 1, bound_to_constraint(-1, weak), make_c2());
    return testDBM3;
}

// l3a
DBM testDBM4()
{
    DBM testDBM4(make_c2());
    testDBM4.addConstraint(1,0, bound_to_constraint(3, weak));
    testDBM4.addConstraint(2,0, bound_to_constraint(3, weak));
    return testDBM4;
}

// l3b
DBM testDBM5()
{
    DBM testDBM5(make_c2());
    testDBM5.addConstraint(1,0, bound_to_constraint(4, strict));
    testDBM5.addConstraint(2,0, bound_to_constraint(4, strict));
    testDBM5.addConstraint(0,1, bound_to_constraint(-2, weak));
    testDBM5.addConstraint(0,2, bound_to_constraint(-2, weak));
    return testDBM5;
}

// l3c
DBM testDBM6()
{
    DBM testDBM6(make_c2());
    testDBM6.addConstraint(2, 1, zero_less);
    return testDBM6;
}

// l4a
DBM testDBM7()
{
    DBM testDBM7(make_c2());
    testDBM7.addConstraint(1,0, bound_to_constraint(1, strict));
    testDBM7.addConstraint(0,1, bound_to_constraint(-2, weak));
    return testDBM7;
}

// d2a
DBM testDBM8()
{
    DBM testDBM8(make_c2());
    testDBM8.addConstraint(0,1, bound_to_constraint(-1, weak));
    testDBM8.cf();
    return testDBM8;
}

// d2b
DBM testDBM9()
{
    DBM testDBM9(make_c2());
    testDBM9.addConstraint(1,0, bound_to_constraint(1, strict));
    testDBM9.cf();
    return testDBM9;
}

// tDBM1
DBMList testDBMList1()
{
    DBM test1(testDBM1());
    DBMList testDBMList1(test1);
    return testDBMList1;
}

// list1
DBMList testDBMList3()
{
    DBMList testDBMList3(make_c2());
    DBM test3(testDBM3());
    testDBMList3.addDBM(test3);
    return testDBMList3;
}

// list1b
DBMList testDBMList4()
{
    DBM test3(testDBM3());
    DBMList testDBMList4(test3);
    return testDBMList4;
}

// list3
DBMList testDBMList5()
{
    DBM test4(testDBM4());
    DBM test5(testDBM5());
    DBM test6(testDBM6());
    DBMList testDBMList5(test4);
    testDBMList5.addDBM(test5);
    testDBMList5.addDBM(test6);
    return testDBMList5;
}

// list4
DBMList testDBMList6()
{
    DBM test7(testDBM7());
    DBMList testDBMList6(test7);
    return testDBMList6;
}

// dList2
DBMList testDBMList7()
{
    DBM test8(testDBM8());
    DBM test9(testDBM9());
    DBMList testDBMList7(test8);
    testDBMList7.addDBM(test9);
    return testDBMList7;
}

TEST(DBMListTest, Empty)
{
    DBMList list1cf(testDBMList1());
    DBMList list3cf(testDBMList3());
    DBMList list4cf(testDBMList4());
    DBMList list5cf(testDBMList5());
    list1cf.cf();
    list3cf.cf();
    list4cf.cf();
    list5cf.cf();

    EXPECT_FALSE(list1cf.emptiness());
    EXPECT_FALSE(list3cf.emptiness());
    EXPECT_FALSE(list4cf.emptiness());
    EXPECT_FALSE(list5cf.emptiness());
}

TEST(DBMListTest, CanonicalDBMList1)
{
    DBMList canonical = testDBMList1();
    canonical.cf();

    DBM test1cf(testDBM1cf());
    DBMList expected(test1cf);
    EXPECT_EQ(expected, canonical);
}

TEST(DBMListTest, CanonicalDBMList3)
{
    DBMList canonical = testDBMList3();
    canonical.cf();

    DBMList expected(make_c2());
    EXPECT_EQ(expected, canonical);
}

TEST(DBMListTest, CanonicalDBMList4)
{
    DBMList canonical = testDBMList4();
    canonical.cf();

    DBMList expected = testDBMList4();
    EXPECT_EQ(expected, canonical);
}

TEST(DBMListTest, CanonicalDBMList5)
{
    DBMList canonical = testDBMList5();
    canonical.cf();

    DBM testDBM4cf(make_c2());
    testDBM4cf.addConstraint(0,0, zero_le);
    testDBM4cf.addConstraint(0,1, zero_le);
    testDBM4cf.addConstraint(0,2, zero_le);
    testDBM4cf.addConstraint(1,0, bound_to_constraint(3, weak));
    testDBM4cf.addConstraint(1,1, zero_le);
    testDBM4cf.addConstraint(1,2, bound_to_constraint(3, weak));
    testDBM4cf.addConstraint(2,0, bound_to_constraint(3, weak));
    testDBM4cf.addConstraint(2,1, bound_to_constraint(3, weak));
    testDBM4cf.addConstraint(2,2, zero_le);
    DBM testDBM5cf(make_c2());
    testDBM5cf.addConstraint(0,0, zero_le);
    testDBM5cf.addConstraint(0,1, bound_to_constraint(-2, weak));
    testDBM5cf.addConstraint(0,2, bound_to_constraint(-2, weak));
    testDBM5cf.addConstraint(1,0, bound_to_constraint(4, weak));
    testDBM5cf.addConstraint(1,1, zero_le);
    testDBM5cf.addConstraint(1,2, bound_to_constraint(2, weak));
    testDBM5cf.addConstraint(2,0, bound_to_constraint(4, strict));
    testDBM5cf.addConstraint(2,1, bound_to_constraint(2, strict));
    testDBM5cf.addConstraint(2,2, zero_le);
    DBM testDBM6cf(make_c2());
    testDBM6cf.addConstraint(0,0, zero_le);
    testDBM6cf.addConstraint(0,1, zero_less);
    testDBM6cf.addConstraint(0,2, zero_le);
    testDBM6cf.addConstraint(1,0, infinity);
    testDBM6cf.addConstraint(1,1, zero_le);
    testDBM6cf.addConstraint(1,2, infinity);
    testDBM6cf.addConstraint(2,0, infinity);
    testDBM6cf.addConstraint(2,1, zero_less);
    testDBM6cf.addConstraint(2,2, zero_le);

    DBMList expected(testDBM4cf);
    expected.addDBM(testDBM5cf);
    expected.addDBM(testDBM6cf);
    expected.cf();

    EXPECT_EQ(expected, canonical);
}

TEST(DBMListTest, CanonicalDBMList6)
{
    DBMList canonical = testDBMList6();
    canonical.cf();
    EXPECT_TRUE(canonical.emptiness());

    DBM empty(emptyDBM3());
    DBMList expected(empty);
    EXPECT_EQ(expected, canonical);

}

TEST(DBMListTest, CanonicalDBMList7)
{
    DBMList canonical = testDBMList7();
    canonical.cf();

    DBMList expected = testDBMList7();
    EXPECT_TRUE(strictly_equal(expected, canonical));
}

TEST(DBMListTest, PreDBMList1)
{
    DBMList pre = testDBMList1();
    pre.pre();

    DBM test1pre(testDBM1pre());
    DBMList expected(test1pre);
    EXPECT_EQ(expected, pre);
}

TEST(DBMListTest, PreCfDBMList1)
{
    DBMList precf = testDBMList1();
    precf.pre();
    precf.cf();

    DBM test1precf(testDBM1precf());
    DBMList expected(test1precf);
    EXPECT_EQ(expected, precf);
}

TEST(DBMListTest, Subset)
{
    DBMList list3 = testDBMList3();
    DBMList list4 = testDBMList4();
    list3.cf();
    list4.cf();
    DBM infty(make_c2());
    infty.cf();

    EXPECT_TRUE(list3 <= infty);
    EXPECT_TRUE(list4 <= infty);
    EXPECT_TRUE(list4 <= list3);
    EXPECT_FALSE(list3 <= list4);
}


TEST(DBMListTest, Superset)
{
    DBMList list3 = testDBMList3();
    DBMList list4 = testDBMList4();
    list3.cf();
    list4.cf();
    DBM infty(make_c2());
    infty.cf();

    EXPECT_TRUE(list3 >= infty);
    EXPECT_FALSE(list4 >= infty);
    EXPECT_FALSE(list4 >= list3);
    EXPECT_TRUE(list3 >= list4);
}

TEST(DBMListTest, Equal)
{
    DBMList list3 = testDBMList3();
    DBMList list4 = testDBMList4();
    DBMList empty = testDBMList3();
    empty.makeEmpty();
    DBM infty(make_c2());
    list3.cf();
    list4.cf();

    EXPECT_TRUE(list3 == infty);
    EXPECT_FALSE(list4 == infty);
    EXPECT_FALSE(list4 == list3);
    EXPECT_FALSE(list3 == list4);
    EXPECT_TRUE(empty == DBMList(emptyDBM3()));
    EXPECT_EQ(DBMList(emptyDBM3()), empty);
}

TEST(DBMListTest, DBMList7Test)
{
    DBMList list7orig = testDBMList7();
    DBMList list7 = testDBMList7();
    DBMList* list7copy = new DBMList(list7);
    list7.cf();
    list7copy->cf();

    EXPECT_EQ(list7, *list7copy);

    list7.cf();
    list7copy->cf();
    EXPECT_FALSE(list7.emptiness());
    EXPECT_FALSE(list7copy->emptiness());
    EXPECT_EQ(list7, (*list7copy));
    EXPECT_TRUE(strictly_equal(list7orig, list7));
    EXPECT_TRUE(strictly_equal(list7orig, *list7copy));

    DBM infty(make_c2());
    infty.cf();
    EXPECT_TRUE(list7 == infty);
    EXPECT_TRUE(strictly_equal(list7, list7orig));
    EXPECT_TRUE(list7 >= infty);
    EXPECT_TRUE(strictly_equal(list7, list7orig));
    EXPECT_TRUE(list7 <= infty);
    EXPECT_TRUE(strictly_equal(list7, list7orig));

    delete list7copy;
}

TEST(DBMListTest, CompareDBMList7Self)
{
    DBMList list7 = testDBMList7();
    list7.cf();
    EXPECT_TRUE(list7 <= list7);
    EXPECT_TRUE(list7 >= list7);
    EXPECT_TRUE(list7 == list7);
}

TEST(DBMListTest, CompareDBMList7DBM8)
{
    DBMList list7 = testDBMList7();
    DBM dbm8(testDBM8());
    list7.cf();

    EXPECT_TRUE(list7 >= dbm8);
    EXPECT_FALSE(list7 <= dbm8);
    EXPECT_FALSE(list7 == dbm8);
}

TEST(DBMListTest, Intersection)
{
    DBMList list7orig = testDBMList7();
    DBMList list7 = testDBMList7();

    list7.intersect(list7orig);
    list7.cf();
    DBMList expected = list7orig;
    DBM test8(testDBM8());
    DBM test9(testDBM9());
    expected.addDBM(test8);
    expected.addDBM(test9);
    expected.cf();

    EXPECT_TRUE(strictly_equal(expected, list7));

    list7.cf();
    EXPECT_TRUE(strictly_equal(list7orig, list7));
}

TEST(DBMListTest, CopyAndIntersectSelf)
{
    DBMList list5 = testDBMList5();
    DBMList list6 = testDBMList6();
    DBMList* list5copy = new DBMList(make_c2());
    *list5copy = list5;

    EXPECT_TRUE(strictly_equal(list5, *list5copy));
    list5.cf();
    list5copy->cf();

    EXPECT_TRUE(list5 <= *list5copy);
    EXPECT_TRUE(list5 >= *list5copy);
    EXPECT_TRUE(list5 == *list5copy);

    list5.intersect(*list5copy);
    DBMList expected = testDBMList5();
    DBM test4(testDBM4());
    DBM test5(testDBM5());
    DBM test6(testDBM6());
    expected.addDBM(test4);
    expected.addDBM(test5);
    expected.addDBM(test6);

    list5.cf();
    EXPECT_EQ(*list5copy, list5);

    EXPECT_FALSE(strictly_equal(list5, *list5copy));
    EXPECT_FALSE(strictly_equal(list6, *list5copy));

    list6.cf();
    EXPECT_TRUE(list5 <= *list5copy);
    EXPECT_TRUE(list5 >= *list5copy);
    EXPECT_TRUE(list5 == *list5copy);
    EXPECT_TRUE(list6 <= *list5copy);
    EXPECT_FALSE(list6 >= *list5copy);
    EXPECT_FALSE(list6 == *list5copy);

    // test copy
    list6 = *list5copy;
    EXPECT_TRUE(list6 <= *list5copy);
    EXPECT_TRUE(list6 >= *list5copy);
    EXPECT_TRUE(list6 == *list5copy);

    list6.cf();
    EXPECT_EQ(list5, list6);

    list6.makeEmpty();
    DBM empty(emptyDBM3());
    DBMList emptylist(empty);
    EXPECT_EQ(emptylist, list6);

    delete list5copy;
    EXPECT_EQ(emptylist, list6);
}
