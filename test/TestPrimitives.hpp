#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    Foo(MockClass& mock)
        : m_mock(mock)
    {
        m_mock.constructor();
    }

    Foo(const Foo& other) = delete;
    Foo(Foo&& other) = delete;

    ~Foo()
    {
        m_mock.destructor();
    }

private:
    MockClass& m_mock;
};