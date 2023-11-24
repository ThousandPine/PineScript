#pragma once

#include <stdio.h>

/**
 * 引用计数方式实现的智能指针
 * NOTE:不要传入在栈上创建的对象的指针
 */

template <class T>
class gc_ptr
{
private:
    int *_cnt = nullptr;
    T *_ptr = nullptr;

    void _ref(T *ptr, int *cnt)
    {
        this->_cnt = cnt;
        this->_ptr = ptr;
        if (ptr != nullptr)
        {
            ++*_cnt;
        }
    }

    void _deref()
    {
        if (this->_ptr == nullptr || this->_cnt == nullptr)
            return;

        if (--*_cnt == 0)
        {
            delete _cnt;
            delete _ptr;
        }

        this->_cnt = nullptr;
        this->_ptr = nullptr;
    }

public:
    gc_ptr(T *ptr)
    {
        this->_ref(ptr, ptr != nullptr ? new int(0) : nullptr);
    }

    gc_ptr(T *ptr, int *cnt)
    {
        this->_ref(ptr, cnt);
    }

    gc_ptr(const gc_ptr<T> &p)
    {
        this->_deref();
        this->_ref(p._ptr, p._cnt);
    }

    ~gc_ptr()
    {
        _deref();
    }

    T *ptr() const
    {
        return this->_ptr;
    }

    operator gc_ptr<const T>() const
    {
        return {this->_ptr, this->_cnt};
    }

    gc_ptr<T> &operator=(const gc_ptr<T> &p)
    {
        this->_deref();
        this->_ref(p._ptr, p._cnt);
        return *this;
    }

    T &operator*() const
    {
        return *_ptr;
    }

    T *operator->() const
    {
        return _ptr;
    }

    bool operator==(const T *ptr) const
    {
        return this->_ptr == ptr;
    }
    bool operator!=(const T *ptr) const
    {
        return this->_ptr != ptr;
    }
};