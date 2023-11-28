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
        _cnt = cnt;
        _ptr = ptr;
        if (ptr != nullptr)
        {
            ++*_cnt;
        }
    }

    void _deref()
    {
        if (_ptr == nullptr || _cnt == nullptr)
            return;

        if (--*_cnt == 0)
        {
            delete _cnt;
            delete _ptr;
        }

        _cnt = nullptr;
        _ptr = nullptr;
    }

public:
    gc_ptr(T *ptr)
    {
        _ref(ptr, ptr != nullptr ? new int(0) : nullptr);
    }

    gc_ptr(T *ptr, int *cnt)
    {
        _ref(ptr, cnt);
    }

    gc_ptr(const gc_ptr<T> &p)
    {
        _deref();
        _ref(p._ptr, p._cnt);
    }

    ~gc_ptr()
    {
        _deref();
    }

    T *ptr() const
    {
        return _ptr;
    }

    operator gc_ptr<const T>() const
    {
        return {_ptr, _cnt};
    }

    gc_ptr<T> &operator=(const gc_ptr<T> &p)
    {
        if (p._ptr != _ptr)
        {
            _deref();
            _ref(p._ptr, p._cnt);
        }
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
        return _ptr == ptr;
    }
    bool operator!=(const T *ptr) const
    {
        return _ptr != ptr;
    }
};