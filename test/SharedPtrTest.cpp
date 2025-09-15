
#include "SharedPtr.hpp"

#include "TestPrimitives.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace Memory;

struct TestObject
{
    int value;
    explicit TestObject(int val) : value(val) {}
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
        EXPECT_EQ(1, ptr.getCount());
    }
}

TEST_F(SharedPtrTest, MoveConstructor)
{
    auto ptr1 = SharedPtr<TestObject>(new TestObject(20));
    EXPECT_EQ(ptr1.getCount(), 1);

    SharedPtr<TestObject> ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr2.getCount(), 1);
    EXPECT_EQ(ptr1.getCount(), 0);
}

TEST_F(SharedPtrTest, CopyAssignment)
{
    auto ptr1 = SharedPtr<TestObject>(new TestObject(30));
    SharedPtr<TestObject> ptr2;

    ptr2 = ptr1;
    EXPECT_EQ(ptr1.getCount(), 2);
    EXPECT_EQ(ptr2.getCount(), 2);
}

TEST_F(SharedPtrTest, MoveAssignment)
{
    auto ptr1 = SharedPtr<TestObject>(new TestObject(40));
    SharedPtr<TestObject> ptr2;

    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr2.getCount(), 1);
    EXPECT_EQ(ptr1.getCount(), 0);
}

TEST_F(SharedPtrTest, Reset)
{
    auto ptr = SharedPtr<TestObject>(new TestObject(50));
    EXPECT_EQ(ptr.getCount(), 1);

    ptr.reset(new TestObject(60));
    EXPECT_EQ(ptr.getCount(), 1);
    EXPECT_EQ(ptr->value, 60);
}

TEST_F(SharedPtrTest, MakeShared)
{
    auto ptr1 = makeShared<TestObject>(70);
    EXPECT_EQ(ptr1.getCount(), 1);
    EXPECT_EQ(ptr1->value, 70);
}

TEST_F(SharedPtrTest, Swap)
{
    auto ptr1 = makeShared<TestObject>(80);
    auto ptr2 = makeShared<TestObject>(90);
    EXPECT_EQ(ptr1->value, 80);
    EXPECT_EQ(ptr2->value, 90);

    ptr1.swap(ptr2);
    EXPECT_EQ(ptr1->value, 90);
    EXPECT_EQ(ptr2->value, 80);
}

TEST_F(SharedPtrTest, Dereference)
{
    auto ptr = makeShared<TestObject>(100);
    EXPECT_EQ((*ptr).value, 100);
    EXPECT_EQ(ptr->value, 100);
}