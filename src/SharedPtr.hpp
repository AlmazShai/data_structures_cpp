#pragma once

#include <atomic>

namespace Memory
{

  class CtrlBlockBase
  {
  public:
    CtrlBlockBase() = default;
    virtual ~CtrlBlockBase() = default;
    CtrlBlockBase(const CtrlBlockBase &) = delete;
    CtrlBlockBase &operator=(const CtrlBlockBase &) = delete;

    void add()
    {
      ++m_refCount;
    }

    void decr()
    {
      if (--m_refCount == 0)
      {
        release();
      }
    }

    [[nodiscard]] size_t getCount() const
    {
      return m_refCount;
    }

  protected:
    virtual void release() = 0;

  private:
    std::atomic_uint64_t m_refCount{1};
  };

  template <typename T>
  class CtrlBlock : public CtrlBlockBase
  {
  public:
    explicit CtrlBlock(T *obj)
        : CtrlBlockBase(), m_obj(obj)
    {
    }

    void release() override
    {
      delete m_obj;
      delete this;
    }

  private:
    T *m_obj;
  };

  template <typename T>
  class CtrlBlockWithStorage : public CtrlBlockBase
  {
  public:
    template <typename... Args>
    CtrlBlockWithStorage(Args &&...args)
        : CtrlBlockBase(), m_obj(std::forward<Args>(args)...)
    {
    }

    void release() override
    {
      delete this;
    }

    T *getObj()
    {
      return &m_obj;
    }

  private:
    T m_obj;
  };

  template <typename T>
  class SharedPtr
  {
  private:
    SharedPtr(CtrlBlockWithStorage<T> *cb)
        : m_cb(cb), m_obj(cb->getObj())
    {
    }

    template <typename U, typename... Args>
    friend SharedPtr<U> makeShared(Args &&...args);

  public:
    SharedPtr() : m_cb(nullptr), m_obj(nullptr) {}

    explicit SharedPtr(T *obj)
        : m_cb(new CtrlBlock(obj)), m_obj(obj)
    {
    }

    ~SharedPtr()
    {
      if (m_cb)
      {
        m_cb->decr();
      }
    }

    SharedPtr(const SharedPtr &other)
        : m_cb(other.m_cb), m_obj(other.m_obj)
    {
      if (m_cb)
      {
        m_cb->add();
      }
    }

    SharedPtr(SharedPtr &&other) noexcept
        : m_cb(other.m_cb), m_obj(other.m_obj)
    {
      other.m_obj = nullptr;
      other.m_cb = nullptr;
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
      SharedPtr(other).swap(*this);
      return *this;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept
    {
      SharedPtr(std::move(other)).swap(*this);
      return *this;
    }

    void reset(T *const obj)
    {
      SharedPtr(obj).swap(*this);
    }

    [[nodiscard]] size_t getCount() const
    {
      if (m_cb)
      {
        return m_cb->getCount();
      }
      return 0;
    }

    void swap(SharedPtr &other)
    {
      std::swap(m_cb, other.m_cb);
      std::swap(m_obj, other.m_obj);
    }

    [[nodiscard]] T &operator*() const
    {
      return *m_obj;
    }

    [[nodiscard]] T *operator->() const
    {
      return m_obj;
    }

  private:
    CtrlBlockBase *m_cb;
    T *m_obj;
  };

  template <typename T, typename... Args>
  SharedPtr<T> makeShared(Args &&...args)
  {
    return SharedPtr(new CtrlBlockWithStorage<T>(std::forward<Args>(args)...));
  }

}