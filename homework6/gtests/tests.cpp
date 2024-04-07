#include <gtest/gtest.h>

#include "../my_array.h"

using namespace my_containers;

TEST(TestMyArray, empty_on_create) {
    MyArray<int> a;
    ASSERT_TRUE(a.size() == 0);
}

TEST(TestMyArray, push_back_ok) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(33);
    ASSERT_TRUE(a.size() == 3);
    ASSERT_TRUE(a[2] == 33);
}

TEST(TestMyArray, insert_first) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(99);
    a.insert(77, 0);
    ASSERT_TRUE(a[0] == 77);
}

TEST(TestMyArray, insert_middle) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(9);
    a.push_back(19);
    a.insert(55, 2);
    ASSERT_TRUE(a[2] == 55);
}

TEST(TestMyArray, insert_last) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(9);
    a.push_back(19);
    a.insert(55, 4);
    ASSERT_TRUE(a[4] == 55);
    ASSERT_TRUE(a.size() == 5);
}

TEST(TestMyArray, erase_first) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(9);
    a.push_back(19);
    a.erase(0, 1);
    ASSERT_TRUE(a[0] == 2);
    ASSERT_TRUE(a.size() == 3);
}

TEST(TestMyArray, erase_last) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(9);
    a.push_back(19);
    a.erase(a.size()-1, 1);
    ASSERT_TRUE(a[2] == 9);
    ASSERT_TRUE(a.size() == 3);
}

TEST(TestMyArray, erase_middle) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(9);
    a.push_back(19);
    a.erase(2, 1);
    ASSERT_TRUE(a[2] == 19);
    ASSERT_TRUE(a.size() == 3);
}

TEST(TestMyArray, all_elements) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(9);
    a.push_back(19);
    ASSERT_TRUE(a[0] == 1);
    ASSERT_TRUE(a[1] == 2);
    ASSERT_TRUE(a[2] == 9);
    ASSERT_TRUE(a[3] == 19);
}
