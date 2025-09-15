#pragma once

#include <utility>

namespace Memory {
template <typename T>
class UniquePtr
{
public:
    UniquePtr()
        : m_obj(nullptr)
    {
    }

    explicit UniquePtr(T* obj)
        : m_obj(obj)
    {
    }

    ~UniquePtr()
    {
        reset();
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other)
    {
        m_obj = other.m_obj;
        other.m_obj = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other)
    {
        if (this == &other)
        {
            return *this;
        }
        reset();
        m_obj = other.m_obj;
        other.m_obj = nullptr;
        return *this;
    }

    T* release()
    {
        auto tmp = m_obj;
        m_obj = nullptr;
        return tmp;
    }

    void reset()
    {
        delete m_obj;
        m_obj = nullptr;
    }

    void swap(UniquePtr& other)
    {
        std::swap(m_obj, other.m_obj);
    }

    explicit operator bool() const noexcept
    {
        return m_obj != nullptr;
    }

    T& operator*() const
    {
        return *m_obj;
    }

    T* operator->() const
    {
        return m_obj;
    }

private:
    T* m_obj;
};
}