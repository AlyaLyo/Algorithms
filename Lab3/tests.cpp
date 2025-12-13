#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include "Sort.h"


TEST(SortTest, EmptyArray) {
    int* arr = nullptr;
    sort(arr, arr, [](int a, int b) { return a < b; });
    SUCCEED();
}


TEST(SortTest, SingleElement) {
    int arr[] = {42};
    sort(arr, arr + 1, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 42);
}

TEST(SortTest, TwoElementsSorted) {
    int arr[] = {1, 2};
    sort(arr, arr + 2, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(SortTest, TwoElementsUnsorted) {
    int arr[] = {2, 1};
    sort(arr, arr + 2, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(SortTest, AlreadySortedArray) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);

    sort(arr, arr + n , [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, ReverseSortedArray) {
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);

    sort(arr, arr + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, ArrayWithDuplicates) {
    int arr[] = {5, 2, 8, 2, 5, 8, 1, 9, 2, 5};
    int expected[] = {1, 2, 2, 2, 5, 5, 5, 8, 8, 9};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);

    sort(arr, arr + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, ArrayWithAllEqualElements) {
    int arr[] = {7, 7, 7, 7, 7, 7, 7, 7};
    int expected[] = {7, 7, 7, 7, 7, 7, 7, 7};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);

    sort(arr, arr + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, NegativeNumbers) {
    int arr[] = {-5, -10, 0, -3, 8, -1, 4};
    int expected[] = {-10, -5, -3, -1, 0, 4, 8};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);

    sort(arr, arr + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, DescendingOrder) {
    int arr[] = {1, 5, 3, 8, 2, 9, 4};
    int expected[] = {9, 8, 5, 4, 3, 2, 1};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);

    sort(arr, arr + n, [](int a, int b) { return a > b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, CustomComparatorAbsoluteValue) {
    int arr[] = {-5, 2, -8, 1, 3, -2, 4};
    sort(arr, arr + 7, [](int a, int b) { return std::abs(a) < std::abs(b); });

    for (int i = 0; i < 6; i++) {
        EXPECT_LE(std::abs(arr[i]), std::abs(arr[i + 1]));
    }
}

struct Person {
    std::string name;
    int age;
    double salary;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age && salary == other.salary;
    }
};

TEST(SortTest, ArrayOfStructsByAge) {
    Person people[] = {
        {"Alice", 30, 50000},
        {"Bob", 25, 45000},
        {"Charlie", 35, 60000},
        {"David", 28, 48000}
    };

    Person expected[] = {
        {"Bob", 25, 45000},
        {"David", 28, 48000},
        {"Alice", 30, 50000},
        {"Charlie", 35, 60000}
    };

    constexpr int n = sizeof(people) / sizeof(people[0]);

    sort(people, people + n, [](const Person& a, const Person& b) {
        return a.age < b.age;
    });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(people[i].name, expected[i].name);
        EXPECT_EQ(people[i].age, expected[i].age);
        EXPECT_DOUBLE_EQ(people[i].salary, expected[i].salary);
    }
}

TEST(SortTest, ArrayOfStructsByName) {
    Person people[] = {
        {"Charlie", 35, 60000},
        {"Alice", 30, 50000},
        {"David", 28, 48000},
        {"Bob", 25, 45000}
    };

    Person expected[] = {
        {"Alice", 30, 50000},
        {"Bob", 25, 45000},
        {"Charlie", 35, 60000},
        {"David", 28, 48000}
    };

    constexpr int n = sizeof(people) / sizeof(people[0]);

    sort(people, people + n, [](const Person& a, const Person& b) {
        return a.name < b.name;
    });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(people[i].name, expected[i].name);
    }
}

TEST(SortTest, ArraySizeOneLessThanThreshold) {
    constexpr int n = 15;
    std::vector<int> arr(n);
    std::vector<int> expected(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
        expected[i] = arr[i];
    }

    std::sort(expected.begin(), expected.end());
    sort(arr.data(), arr.data() + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, ArraySizeEqualToThreshold) {
    constexpr int n = 16;
    std::vector<int> arr(n);
    std::vector<int> expected(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
        expected[i] = arr[i];
    }

    std::sort(expected.begin(), expected.end());
    sort(arr.data(), arr.data() + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortTest, ArraySizeOneMoreThanThreshold) {
    constexpr int n = 17;
    std::vector<int> arr(n);
    std::vector<int> expected(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
        expected[i] = arr[i];
    }

    std::sort(expected.begin(), expected.end());
    sort(arr.data(), arr.data() + n, [](int a, int b) { return a < b; });

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}