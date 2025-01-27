#pragma once

namespace Memory {

class RefCounter {
  public:
    RefCounter(const RefCounter&) = delete;
    RefCounter& operator=(const RefCounter&) = delete;

    RefCounter() : m_count(0) {};

    RefCounter& operator++(int) {
      ++m_count;
      return *this;
    }

    RefCounter& operator--(int) {
      --m_count;
      return *this;
    }

    [[nodiscard]] int getCount() const {
      return m_count;
    }

  private:
    int m_count;
};


template<typename T>
class SharedPtr {
  public:
    SharedPtr() : m_counter(nullptr), m_obj(nullptr) {}

    explicit SharedPtr(T* obj)
        : m_obj(obj), m_counter(new RefCounter) {
      if (m_obj) {
        m_counter = new RefCounter();
        (*m_counter)++;
      }
    }

    ~SharedPtr() {
      decrementCounter();
    }

    SharedPtr(const SharedPtr& other) {
      m_counter = other.m_counter;
      m_obj = other.m_obj;
      (*m_counter)++;
    }

    SharedPtr(SharedPtr&& other) noexcept {
      m_counter = other.m_counter;
      m_obj = other.m_obj;
      other.m_counter = nullptr;
      other.m_obj = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) {
      if (&other != this) {
        decrementCounter();

        m_counter = other.m_counter;
        m_obj = other.m_obj;
        if (m_counter) {
          (*m_counter)++;
        }
      }
      return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
      if (&other != this) {
        decrementCounter();

        m_counter = other.m_counter;
        m_obj = other.m_obj;
        other.m_counter = nullptr;
        other.m_obj = nullptr;
      }
      return *this;
    }

    void reset(T* const obj) {
      decrementCounter();
      m_obj = obj;
      if (m_obj) {
        m_counter = new RefCounter();
        (*m_counter)++;
      }
    }

    [[nodiscard]] int getCount() const {
      if (m_counter) {
        return m_counter->getCount();
      }
      return 0;
    }

  private:
    void decrementCounter() {
      if (m_counter) {
        (*m_counter)--;
        if (m_counter->getCount() == 0) {
          delete m_obj;
          delete m_counter;
          m_obj = nullptr;
          m_counter = nullptr;
        }
      }
    }

  private:
    RefCounter* m_counter;
    T* m_obj;
};

}