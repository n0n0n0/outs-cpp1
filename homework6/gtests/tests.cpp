#include <gtest/gtest.h>

#include "../my_array.h"

using namespace my_containers;

TEST(TestMyArray, correct_size) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_TRUE(a.size() == 3);
}

TEST(TestMyArray, correct_push) {
    MyArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(99);
    ASSERT_TRUE(a[2] == 99);
}

// TEST(TestMyArray, skip_spaces) {
//     ASSERT_TRUE(checkcardnum("4561 2612 1234 5467"));
// }
