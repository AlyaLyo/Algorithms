#include <cstdlib>
#include <iostream>
#include <utility>
#include <string>
#include "Array.h"
#include <gtest/gtest.h>


TEST(ArrayTest, DefaultConstructor)
{
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GT(arr.capacity(), 0);
}

TEST(ArrayTest, ConstructorWithCapacity)
{
    Array<int> arr(10);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 10);

    Array<int> arr_neg(-5);
    EXPECT_EQ(arr_neg.size(), 0);
    EXPECT_EQ(arr_neg.capacity(), 8);
}

TEST(ArrayTest, Destructor)
{
    {
        Array<int> arr(2);
        arr.insert(10);
        arr.insert(20);
    }
    SUCCEED();
}

TEST(ArrayTest, InsertAtEnd)
{
    Array<int> arr;
    int index = arr.insert(10);
    EXPECT_EQ(index, 0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);

    index = arr.insert(20);
    EXPECT_EQ(index, 1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, InsertAtIndexNoResize)
{
    Array<int> arr(5);
    arr.insert(0, 100);
    arr.insert(0, 200);
    arr.insert(1, 99);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 200);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 100);
}

TEST(ArrayTest, InsertAtIndexWithResize)
{
    Array<int> arr(2);
    arr.insert(0, 100);
    arr.insert(1, 200);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.capacity(), 2);

    arr.insert(1, 150);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_GT(arr.capacity(), 2);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 150);
    EXPECT_EQ(arr[2], 200);
}

TEST(ArrayTest, InsertAtEndWithResize)
{
    Array<int> arr(1);
    arr.insert(10); // [10]
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.capacity(), 1);

    arr.insert(20);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_GT(arr.capacity(), 1);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, Remove)
{
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    arr.remove(1);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, IndexOperator)
{
    Array<int> arr(5);
    arr.insert(10);
    arr.insert(20);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    arr[0] = 100;
    EXPECT_EQ(arr[0], 100);
}

TEST(ArrayTest, CopyConstructor)
{
    Array<int> original;
    original.insert(1);
    original.insert(2);

    Array<int> copy = original;

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.capacity(), original.capacity());
    EXPECT_EQ(copy[0], original[0]);
    EXPECT_EQ(copy[1], original[1]);

    copy[0] = 999;
    EXPECT_EQ(original[0], 1);
    EXPECT_EQ(copy[0], 999);
}

TEST(ArrayTest, CopyAssignment)
{
    Array<int> original;
    original.insert(100);
    original.insert(200);

    Array<int> target(1);
    target.insert(5);

    target = original;

    EXPECT_EQ(target.size(), original.size());
    EXPECT_EQ(target.capacity(), original.capacity());
    EXPECT_EQ(target[0], original[0]);
    EXPECT_EQ(target[1], original[1]);

    target[0] = 999;
    EXPECT_EQ(original[0], 100);
    EXPECT_EQ(target[0], 999);
}

TEST(ArrayTest, CopyAssignmentSelf)
{
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    arr = arr;

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, MoveConstructor)
{
    Array<int> original;
    original.insert(100);
    original.insert(200);
    int original_size = original.size();
    int original_capacity = original.capacity();
    int* original_data_ptr = original.buf();

    Array<int> moved_to = std::move(original);

    EXPECT_EQ(moved_to.size(), original_size);
    EXPECT_EQ(moved_to.capacity(), original_capacity);
    EXPECT_EQ(moved_to[0], 100);
    EXPECT_EQ(moved_to[1], 200);

    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.capacity(), 0);
    EXPECT_EQ(original.buf(), nullptr);
}


TEST(ArrayTest, MoveAssignment)
{
    Array<int> original;
    original.insert(300);
    original.insert(400);
    int original_size = original.size();
    int* original_data_ptr = original.buf();

    Array<int> target(1);
    target.insert(5);

    target = std::move(original);

    EXPECT_EQ(target.size(), original_size);
    EXPECT_EQ(target[0], 300);
    EXPECT_EQ(target[1], 400);

    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.buf(), nullptr);
}

TEST(ArrayTest, MoveAssignmentSelf)
{
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    arr = std::move(arr);

    EXPECT_GE(arr.size(), 0);
    SUCCEED();
}

TEST(ArrayTest, IteratorForward)
{
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    int sum = 0;
    int count = 0;
    auto it = arr.iterator();
    while (it.hasNext())
    {
        sum += it.get();
        count++;
        it.next();
    }
    sum += it.get();
    count++;

    EXPECT_EQ(sum, 6);
    EXPECT_EQ(count, 3);
}

TEST(ArrayTest, ConstIteratorForward)
{
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    Array<int>& const_arr = arr;
    int sum = 0;
    int count = 0;

    auto it = const_arr.iterator();
    while (it.hasNext())
    {
        sum += it.get();
        count++;
        it.next();
    }
    sum += it.get();
    count++;

    EXPECT_EQ(sum, 30);
    EXPECT_EQ(count, 2);
}

TEST(ArrayTest, IteratorReverse)
{
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    int sum = 0;
    int expected_value = 3;
    auto it = arr.reverseIterator();
    while (it.hasNext())
    {
        EXPECT_EQ(it.get(), expected_value);
        sum += it.get();
        expected_value--;
        it.next();
    }
    sum += it.get();
    EXPECT_EQ(sum, 6);
}

TEST(ArrayTest, ConstIteratorReverse)
{
    Array<int> arr;
    arr.insert(100);
    arr.insert(200);

    Array<int>& const_arr = arr;
    int sum = 0;
    int expected_value = 200;
    auto it = const_arr.reverseIterator();
    while (it.hasNext())
    {
        EXPECT_EQ(it.get(), expected_value);
        sum += it.get();
        expected_value -= 100;
        it.next();
    }
    sum += it.get();

    EXPECT_EQ(sum, 300);
}

TEST(ArrayTest, IteratorSet)
{
    Array<int> arr;
    arr.insert(5);
    arr.insert(10);

    for (auto it = arr.iterator(); it.hasNext(); it.next())
    {
        if (it.get() == 5)
        {
            it.set(99);
        }
    }

    auto it = arr.iterator();
    while (it.hasNext())
    {
        if (it.get() == 5)
        {
            it.set(99);
        }
        it.next();
    }

    if (it.get() == 5)
    {
        it.set(99);
    }

    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 10);
}

TEST(ArrayTest, EmptyArrayIterators)
{
    Array<int> arr;

    auto it = arr.iterator();
    EXPECT_FALSE(it.hasNext());

    auto rev_it = arr.reverseIterator();
    EXPECT_FALSE(rev_it.hasNext());

    Array<int>& const_arr = arr;
    auto const_it = const_arr.iterator();
    EXPECT_FALSE(const_it.hasNext());

    auto const_rev_it = const_arr.reverseIterator();
    EXPECT_FALSE(const_rev_it.hasNext());
}

TEST(ArrayTest, WithString)
{
    Array<std::string> str_arr(2);
    str_arr.insert("Hello");
    str_arr.insert("World");

    EXPECT_EQ(str_arr.size(), 2);
    EXPECT_EQ(str_arr[0], "Hello");
    EXPECT_EQ(str_arr[1], "World");

    str_arr[1] = "C++";
    EXPECT_EQ(str_arr[1], "C++");

    Array<std::string> str_copy = str_arr;
    EXPECT_EQ(str_copy[0], "Hello");
    EXPECT_EQ(str_copy[1], "C++");

    Array<std::string> str_move = std::move(str_arr);
    EXPECT_EQ(str_move[0], "Hello");
    EXPECT_GE(str_arr.size(), 0);
}

TEST(IteratorTest, HasNextTest) {
    Array<int> arr(3);
    arr.insert(0);
    arr.insert(1);
    arr.insert(2);

    auto it = arr.iterator();
    it.next();
    it.next();
    EXPECT_FALSE(it.hasNext());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
