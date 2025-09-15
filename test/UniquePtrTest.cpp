#include <gtest/gtest.h>

#include "UniquePtr.hpp"

#include "TestPrimitives.hpp"

namespace Test {
using namespace Memory;
using namespace ::testing;

class UniquePtrTest : public ::testing::Test
{
public:
    MockClass mock;
};

TEST_F(UniquePtrTest, defaultConstructAndDestruct)
{
}

TEST_F(UniquePtrTest, constructAndDestruct)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr(new Foo(mock));
    }
}

TEST_F(UniquePtrTest, moveConstruct)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr1(new Foo(mock));
        UniquePtr<Foo> ptr2(std::move(ptr1));
        EXPECT_FALSE(static_cast<bool>(ptr1));
        EXPECT_TRUE(static_cast<bool>(ptr2));
    }
}

TEST_F(UniquePtrTest, moveAssign)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr1(new Foo(mock));
        UniquePtr<Foo> ptr2;
        ptr2 = std::move(ptr1);
        EXPECT_FALSE(static_cast<bool>(ptr1));
        EXPECT_TRUE(static_cast<bool>(ptr2));
    }
}

TEST_F(UniquePtrTest, release)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr(new Foo(mock));
        Foo* rawPtr = ptr.release();
        EXPECT_FALSE(static_cast<bool>(ptr));
        delete rawPtr;
    }
}

TEST_F(UniquePtrTest, reset)
{
    EXPECT_CALL(mock, constructor()).Times(1);
    EXPECT_CALL(mock, destructor()).Times(1);
    {
        UniquePtr<Foo> ptr(new Foo(mock));
        ptr.reset();
        EXPECT_FALSE(static_cast<bool>(ptr));
    }
}

TEST_F(UniquePtrTest, swap)
{
    EXPECT_CALL(mock, constructor()).Times(2);
    EXPECT_CALL(mock, destructor()).Times(2);
    {
        UniquePtr<Foo> ptr1(new Foo(mock));
        UniquePtr<Foo> ptr2(new Foo(mock));
        ptr1.swap(ptr2);
        EXPECT_TRUE(static_cast<bool>(ptr1));
        EXPECT_TRUE(static_cast<bool>(ptr2));
    }
}

TEST_F(UniquePtrTest, dereferenceOperators)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr(new Foo(mock));
        EXPECT_NO_THROW(*ptr);
    }
}

TEST_F(UniquePtrTest, selfMoveAssign)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr(new Foo(mock));
        ptr = std::move(ptr);
        EXPECT_TRUE(static_cast<bool>(ptr));
    }
}

TEST_F(UniquePtrTest, boolOperator)
{
    EXPECT_CALL(mock, constructor());
    EXPECT_CALL(mock, destructor());
    {
        UniquePtr<Foo> ptr(new Foo(mock));
        EXPECT_TRUE(static_cast<bool>(ptr));
        ptr.reset();
        EXPECT_FALSE(static_cast<bool>(ptr));
    }
}

} // namespace Test