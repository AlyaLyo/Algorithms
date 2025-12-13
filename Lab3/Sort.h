#pragma once

const int THRESHOLD = 16;

bool compare(int a, int b)
{
    return a < b;
}

template<typename T, typename Compare>
T getMedian(T* first, T* last, Compare compare) {
    T* middle = first + (last - first) / 2;

    if (compare(*last, *first))
    {
        std::swap(*last, *first);
    }

    if (compare(*middle, *first))
    {
        std::swap(*middle, *first);
    }

    if (compare(*last, *middle))
    {
        std::swap(*last, *middle);
    }

    return *middle;
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare compare)
{
    T pivot = getMedian(first, last - 1, compare);
    T* i = first;
    T* j = last - 1;

    while (true)
    {
        while (compare(*i, pivot))
        {
            i++;
        }

        while (compare(pivot, *j))
        {
            j--;
        }

        if (i >= j)
        {
            return j;
        }

        std::swap(*i, *j);
        i++;
        j--;
    }
}

template<typename T, typename Compare>
void quickSort(T* first, T* last, Compare compare)
{
    while (first < last)
    {
        T* pivot = partition(first, last, compare);
        if (pivot - first < last - pivot - 1)
        {
            quickSort(first, pivot + 1, compare);
            first = pivot + 1;
        }
        else
        {
            quickSort(pivot + 1, last, compare);
            last = pivot + 1;
        }
    }
}

template<typename T, typename Compare>
void insertionSort(T* first, T* last, Compare compare)
{
    for (T* i = first + 1; i < last; i++)
    {
        T* j = i;
        T current = std::move(*i);
        while (j > first && compare(current, *(j - 1)))
        {
            *j = std::move(*(j - 1));
            j--;
        }
        *j = std::move(current);
    }
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare compare)
{
    if (first >= last) {
        return;
    }
    while (last - first > THRESHOLD)
    {
        T* pivot = partition(first, last, compare);
        if (pivot - first + 1 < last - pivot - 1)
        {
            sort(first, pivot + 1, compare);
            first = pivot + 1;
        }
        else
        {
            sort(pivot + 1, last, compare);
            last = pivot + 1;
        }
    }
    insertionSort(first, last, compare);
}
