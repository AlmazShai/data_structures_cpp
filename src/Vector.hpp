#pragma once

constexpr size_t defaultCapacity = 10;
constexpr size_t capacityGrowthFactor = 2;

template<typename T>
class Vector {
public:
    Vector()
        : m_data(nullptr),
        m_capacity(0),
        m_size(0)
    {
    }

    explicit Vector(const size_t size) : Vector()
    {
        reserve(size * capacityGrowthFactor);
        for (size_t i = 0; i < size; ++i) {
            new(m_data[i]) T();
        }
        m_size = size;
    }

    Vector(const size_t size, const T& val) : Vector()
    {
        reserve(size * capacityGrowthFactor);
        for (size_t i = 0; i < size; ++i) {
            new(m_data[i]) T();
        }
        m_size = size;
    }

    ~Vector() {
        for (size_t i = 0; i < m_size; --i) {
            m_data[i].~T();
        }
        ::operator delete(m_data);
    }

    void reserve(const size_t size) {
        if (m_capacity >= size) {
            return;
        }

        // Allocate new buffer and move all data to new buffer
        T* newPtr = static_cast<T*>(::operator new(sizeof(T) * size));
        for (size_t i = 0; i < m_size; ++i) {
            new(newPtr + i) T(std::move(m_data[i]));
            m_data[i].~T();
        }

        ::operator delete(m_data);
        m_data = newPtr;
        m_capacity = size;
    }

    void pushBack(const T& val) {
        reserveCapacity();
        new (m_data + m_size) T(val);
        ++m_size;
    }

    void pushBack(T&& val) {
        reserveCapacity();
        new (m_data + m_size) T(std::forward<T>(val));
        ++m_size;
    }

    template<typename... Args>
    void emplaceBack(Args&& ... args) {
        reserveCapacity();
        new (m_data + m_size) T(std::forward<Args>(args)...);
        ++m_size;
    }

    [[nodiscard]] T& operator[](const int i) {
        return m_data[i];
    }

    [[nodiscard]] size_t size() const {
        return m_size;
    }

    [[nodiscard]] size_t capacity() const {
        return m_capacity;
    }

private:
    void reserveCapacity() {
        if (m_capacity == 0) {
            reserve(defaultCapacity);
        }
        else if (m_size == m_capacity) {
            reserve(m_size * capacityGrowthFactor);
        }
    }

private:
    T* m_data;
    size_t m_capacity;
    size_t m_size;
};