/*******************************************************************************************[Vec.h]
Copyright (c) 2003-2007, Niklas Een, Niklas Sorensson
Copyright (c) 2007-2010, Niklas Sorensson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/


#ifndef GLUCOSAMINE_MTL_VEC_H_
#define GLUCOSAMINE_MTL_VEC_H_


namespace Glucose {


template<typename T>
class vec
{
public:
    vec()
        : data(nullptr)
        , size_(0)
        , cap_(0)
    {}

    explicit
    vec(size_t size)
        : data(nullptr)
        , size_(0)
        , cap_(0)
    {
        growTo(size);
    }

    vec(size_t size, T const & pad)
        : data(nullptr)
        , size_(0)
        , cap_(0)
    {
        growTo(size, pad);
    }

    ~vec()
    {
        clear(true);
    }

    // Disallow copy/move
    vec<T> & operator = (vec<T> & other) = delete;
    vec(vec<T> & other) = delete;
    vec(vec<T> && other) = delete;

    // Pointer to first element:
    operator T* ()
    {
        return data;
    }

    size_t
    size() const
    {
        return size_;
    }

    void
    shrink(size_t n)
    {
        assert(n <= size_);
        for (size_t i = 0; i < n; ++i) {
            --size_;
            data[size_].~T();
        }
    }

    void
    shrink_(size_t n)
    {
        assert(n <= size_);
        size_ -= n;
    }

    size_t
    capacity() const
    {
        return cap_;
    }

    void capacity(size_t new_cap);

    void
    growTo(size_t size)
    {
        if (size_ >= size) {
            return;
        }
        capacity(size);
        for (size_t i = size_; i < size; ++i) {
            new (&data[i]) T();
        }
        size_ = size;
    }

    void
    growTo(size_t size, T const & pad)
    {
        if (size_ >= size) {
            return;
        }
        capacity(size);
        for (size_t i = size_; i < size; ++i) {
            data[i] = pad;
        }
        size_ = size;
    }

    void
    clear(bool dealloc = false)
    {
        if (data != nullptr) {
            for (size_t i = 0; i < size_; ++i) {
                data[i].~T();
            }
            size_ = 0;
            if (dealloc) {
                free(data);
                data = nullptr;
                cap_ = 0;
            }
        }
    }

    void
    push()
    {
        if (size_ == cap_) {
            capacity(size_ + 1);
        }
        new (&data[size_]) T();
        ++size_;
    }

    void
    push(T const & elem)
    {
        if (size_ == cap_) {
            capacity(size_ + 1);
        }
        data[size_++] = elem;
    }

    void
    push_(T const & elem)
    {
        assert(size_ < cap_);
        data[size_++] = elem;
    }

    void
    pop()
    {
        assert(size_ > 0);
        --size_;
        data[size_].~T();
    }

    // NOTE: it seems possible that overflow can happen in the 'size_+1' expression of 'push()', but
    // in fact it can not since it requires that 'cap_' is equal to INT_MAX. This in turn can not
    // happen given the way capacities are calculated (below). Essentially, all capacities are
    // even, but INT_MAX is odd.

    T const &
    last() const
    {
        return data[size_-1];
    }

    T &
    last()
    {
        return data[size_-1];
    }

    T const &
    operator [] (size_t pos) const
    {
        return data[pos];
    }

    T &
    operator [] (size_t pos)
    {
        return data[pos];
    }

    void
    copyTo(vec<T> & copy) const
    {
        copy.clear();
        copy.growTo(size_);
        for (size_t i = 0; i < size_; ++i) {
            copy[i] = data[i];
        }
    }

    void
    moveTo(vec<T> & dest) {
        dest.clear(true);
        dest.data = data;
        dest.size_ = size_;
        dest.cap_ = cap_;
        data = nullptr;
        size_ = 0;
        cap_ = 0;
    }

    void
    memCopyTo(vec<T> & copy) const
    {
        copy.capacity(cap_);
        copy.size_ = size_;
        memcpy(copy.data, data, sizeof(T) * cap_);
    }

private:
    T * data;

    size_t size_;
    size_t cap_;
};


template<typename T>
void
vec<T>::capacity(size_t new_cap)
{
    static auto mask = ~ std::size_t { 1 };

    // If we already have enough space, do nothing
    if (cap_ >= new_cap) {
        return;
    }

    // Figure out how much memory to add
    size_t x = (new_cap - cap_ + 1u) & mask;
    size_t y = ((cap_ >> 1) + 2u) & mask;
    size_t add = (x > y) ? x : y;

    // Don't allow overflow of size_t
    if (add > (SIZE_MAX - cap_)) {
        throw std::bad_alloc();
    }

    new_cap = cap_ + add;

    data = (T*) std::realloc(data, new_cap * sizeof(T));

    if (data == nullptr && errno == ENOMEM) {
        throw std::bad_alloc();
    }

    cap_ = new_cap;
}


}  // namespace Glucose


#endif  // GLUCOSAMINE_MTL_VEC_H_
