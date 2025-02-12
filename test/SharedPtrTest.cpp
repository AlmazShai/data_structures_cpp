
#include "SharedPtr.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace Memory;

// mock class to track constructor and destructor calls
class MockClass
{
public:
    MOCK_METHOD(void, constructor, ());
    MOCK_METHOD(void, destructor, ());
};

// Foo class to test shared pointer
class Foo
{
public:
    Foo(MockClass &mock)
        : m_mock(mock)
    {
        m_mock.constructor();
    }

    Foo(const Foo &other) = delete;
    Foo(Foo &&other) = delete;

    ~Foo()
    {
        m_mock.destructor();
    }

private:
    MockClass &m_mock;
};

class SharedPtrTest : public ::testing::Test
{
protected:
    MockClass mock;
};

TEST_F(SharedPtrTest, createAndDestroy)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        SharedPtr<Foo> ptr(new Foo(mock));
        EXPECT_EQ(1, ptr.getCount());
    }
}

TEST_F(SharedPtrTest, makeShared)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        auto ptr = makeShared<Foo>(mock);
        EXPECT_EQ(1, ptr.getCount());
    }
}

// copy shared pointer
TEST_F(SharedPtrTest, copy)
{
    EXPECT_CALL(mock, constructor).Times(1);
    EXPECT_CALL(mock, destructor).Times(1);
    {
        SharedPtr ptr(new Foo(mock));
        {
            SharedPtr ptr2(ptr);
            EXPECT_EQ(2, ptr.getCount());
            EXPECT_EQ(2, ptr2.getCount());
        }
        EXPECT_EQ(2, ptr.getCount());
    }
}