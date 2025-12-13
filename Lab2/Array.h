
#pragma once

template<typename T>
class Array final
{
public:

    Array();
    Array(int capacity);

    ~Array();

    Array(const Array<T>& other);
    Array(Array<T>&& other);

    Array <T>& operator = (const Array<T>& other);
    Array <T>& operator = (Array<T>&& other);
    Array<T>& operator = (Array<T> rhs);

    int insert(const T& value);
    int insert(int index, const T& value);

    void remove(int index);

    const T& operator[](int index) const;
    T& operator[](int index);

    int size() const;
    int capacity() const;
    T* buf() const;

    class Iterator
    {
    public:

        Iterator(Array<T>& array, T* start_ptr);
        Iterator(Array<T>& array, T* start_ptr, int direction);

        T& get() const;
        void set(const T& value);
        void next();
        bool hasNext() const;

    private:

        Array<T>& array_ref_;
        T* cur_ptr_;
        int dir_;

    };

    class ConstIterator
    {
    public:

        ConstIterator(Array<T>& array, T* start_ptr);
        ConstIterator(Array<T>& array, T* start_ptr, int direction);

        const T& get() const;
        void next();
        bool hasNext() const;

    private:

        Array<T>& array_ref_;
        T* cur_ptr_;
        int dir_;

    };

    Iterator iterator();
    ConstIterator iterator() const;

    Iterator reverseIterator();
    ConstIterator reverseIterator() const;

private:

    int size_;
    int capacity_;
    T* buf_;

    void resize();

};

template<typename T>
Array<T>::Array():
    size_(0),
    capacity_(8)
{
    buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
}

template<typename T>
Array<T>::Array(int capacity):
    size_(0),
    capacity_(capacity > 0 ? capacity : 8)
{
    buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
}

template<typename T>
Array<T>::~Array()
{
    for (int i = 0; i < size_; i++)
    {
        buf_[i].~T();
    }
    std::free(buf_);
}

template<typename T>
Array<T>::Array(const Array<T>& other):
    size_(other.size_),
    capacity_(other.capacity_)
{
    buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
    for (int i = 0; i < size_; i++)
    {
        new(buf_ + i) T(other[i]);
    }
}

template<typename T>
Array<T>::Array(Array<T>&& other):
    buf_(other.buf_),
    size_(other.size_),
    capacity_(other.capacity_)
{
    other.buf_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
Array<T>& Array<T>::operator = (Array<T> rhs)
{
    std::swap(capacity_, rhs.capacity_);
    std::swap(size_, rhs.size_);
    std::swap(buf_, rhs.buf_);
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator = (const Array<T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    for (int i = 0; i < size_; i++)
    {
        buf_[i].~T();
    }
    std::free(buf_);

    size_ = other.size_;
    capacity_ = other.capacity_;
    buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));

    for (int i = 0; i < size_; i++)
    {
        new(buf_ + i) T(other[i]);
    }
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator = (Array<T>&& other)
{
    if (this == &other)
    {
        return *this;
    }

    for (int i = 0; i < size_; i++)
    {
        buf_[i].~T();
    }
    std::free(buf_);

    buf_ = other.buf_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.buf_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

template<typename T>
int Array<T>::insert(const T &value) {
    if (size_ >= capacity_) {
        resize();
    }
    new(buf_ + size_) T(value);
    return size_++;
}

template<typename T>
int Array<T>::insert(int index, const T &value)
{
    if (size_ >= capacity_)
    {
        resize();
    }

    for (int i = size_; i > index; i--)
    {
        new (buf_ + i) T(std::move(buf_[i - 1]));
        buf_[i - 1].~T();
    }

    new(buf_ + index) T(value);
    size_++;
    return index;
}


template<typename T>
void Array<T>::remove(int index)
{
    buf_[index].~T();
    for (int i = index + 1; i < size_; i++)
    {
        new(buf_ + i - 1) T(std::move(buf_[i]));
        buf_[i].~T();
    }
    size_--;
}


template<typename T>
const T& Array<T>::operator[](int index) const
{
    return buf_[index];
}

template<typename T>
T& Array<T>::operator[](int index)
{
    return buf_[index];
}


template<typename T>
int Array<T>::size() const
{
    return size_;
}

template<typename T>
int Array<T>::capacity() const
{
    return capacity_;
}

template<typename T>
T* Array<T>::buf() const
{
    return buf_;
}

template<typename T>
void Array<T>::resize()
{
    capacity_ = capacity_ * 2 + 1;
    T* buf_resized = (T*) std::malloc(capacity_ * sizeof(T));
    for (int i = 0; i <size_; i++)
    {
        new(buf_resized + i) T(std::move(buf_[i]));
        buf_[i].~T();
    }
    std::free(buf_);
    buf_ = buf_resized;
}

template<typename T>
Array<T>::Iterator::Iterator(Array<T>& array,T* start_ptr):
    array_ref_(array),
    cur_ptr_(start_ptr),
    dir_(1)
{}

template<typename T>
Array<T>::Iterator::Iterator(Array<T>& array, T* start_ptr, int direction):
    array_ref_(array),
    cur_ptr_(start_ptr),
    dir_(direction)
{}

template<typename T>
T& Array<T>::Iterator::get() const
{
    return *cur_ptr_;
}

template<typename T>
void Array<T>::Iterator::set(const T &value)
{
    *cur_ptr_ = value;
}

template<typename T>
void Array<T>::Iterator::next()
{
    cur_ptr_ += dir_;
}

template<typename T>
bool Array<T>::Iterator::hasNext() const
{
    if (dir_ > 0)
    {
        return cur_ptr_ < array_ref_.buf_ + array_ref_.size_ - 1;
    }
    else
    {
        return cur_ptr_ > array_ref_.buf_;
    }
}

template<typename T>
Array<T>::ConstIterator::ConstIterator(Array<T> &array, T *start_ptr):
    array_ref_(array),
    cur_ptr_(start_ptr),
    dir_(1)
{}

template<typename T>
Array<T>::ConstIterator::ConstIterator(Array<T>& array, T* start_ptr, int direction):
    array_ref_(array),
    cur_ptr_(start_ptr),
    dir_(direction)
{}

template<typename T>
const T& Array<T>::ConstIterator::get() const
{
    return *cur_ptr_;
}

template<typename T>
void Array<T>::ConstIterator::next()
{
    cur_ptr_ += dir_;
}

template<typename T>
bool Array<T>::ConstIterator::hasNext() const
{
    if (dir_ > 0)
    {
        return cur_ptr_ < array_ref_.buf_ + array_ref_.size_ - 1;
    }
    else
    {
        return cur_ptr_ > array_ref_.buf_;
    }
}

template<typename T>
typename Array<T>::Iterator Array<T>::iterator()
{
    return Array<T>::Iterator(*this, buf_);
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::iterator() const
{
    return Array<T>::ConstIterator(*this, buf_);
}

template<typename T>
typename Array<T>::Iterator Array<T>::reverseIterator()
{
    if (size_ > 0)
    {
        return Array<T>::Iterator(*this, buf_ + size_ - 1, -1);
    }
    return Array<T>::Iterator(*this, buf_ - 1, -1);
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::reverseIterator() const
{
    if (size_ > 0)
    {
        return Array<T>::ConstIterator(*this, buf_ + size_ - 1, -1);
    }
    return Array<T>::ConstIterator(*this, buf_ - 1, -1);
}

