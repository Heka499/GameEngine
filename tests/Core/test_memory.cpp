#include <gtest/gtest.h>
#include "GameEngine/Core/Memory.h"

using namespace GameEngine::Core;

// Simple test class for memory pool testing
class TestObject {
public:
    int value;
    static int constructorCalls;
    static int destructorCalls;
    
    TestObject(int v = 0) : value(v) { constructorCalls++; }
    ~TestObject() { destructorCalls++; }
    
    static void ResetCounters() {
        constructorCalls = 0;
        destructorCalls = 0;
    }
};

int TestObject::constructorCalls = 0;
int TestObject::destructorCalls = 0;

class MemoryPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
        TestObject::ResetCounters();
    }
    
    void TearDown() override {
        TestObject::ResetCounters();
    }
};

TEST_F(MemoryPoolTest, BasicAllocation) {
    MemoryPool<TestObject, 10> pool;
    
    EXPECT_EQ(pool.AvailableCount(), 10);
    EXPECT_EQ(pool.UsedCount(), 0);
    
    TestObject* obj = pool.Allocate(42);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->value, 42);
    EXPECT_EQ(TestObject::constructorCalls, 1);
    
    EXPECT_EQ(pool.AvailableCount(), 9);
    EXPECT_EQ(pool.UsedCount(), 1);
    
    pool.Deallocate(obj);
    EXPECT_EQ(TestObject::destructorCalls, 1);
    EXPECT_EQ(pool.AvailableCount(), 10);
    EXPECT_EQ(pool.UsedCount(), 0);
}

TEST_F(MemoryPoolTest, PoolExhaustion) {
    MemoryPool<TestObject, 2> smallPool;
    
    TestObject* obj1 = smallPool.Allocate(1);
    TestObject* obj2 = smallPool.Allocate(2);
    TestObject* obj3 = smallPool.Allocate(3); // Should fail
    
    EXPECT_NE(obj1, nullptr);
    EXPECT_NE(obj2, nullptr);
    EXPECT_EQ(obj3, nullptr); // Pool exhausted
    
    EXPECT_EQ(smallPool.UsedCount(), 2);
    EXPECT_EQ(smallPool.AvailableCount(), 0);
}

TEST_F(MemoryPoolTest, PoolPtrRAII) {
    MemoryPool<TestObject, 10> pool;
    
    {
        PoolPtr<TestObject> ptr(pool.Allocate(100), &pool);
        EXPECT_TRUE(ptr.isValid());
        EXPECT_EQ(ptr->value, 100);
        EXPECT_EQ(pool.UsedCount(), 1);
    } // ptr goes out of scope, should auto-deallocate
    
    EXPECT_EQ(pool.UsedCount(), 0);
    EXPECT_EQ(TestObject::destructorCalls, 1);
}

TEST_F(MemoryPoolTest, MoveSemantics) {
    MemoryPool<TestObject, 10> pool;
    
    auto createPtr = [&pool]() {
        return PoolPtr<TestObject>(pool.Allocate(200), &pool);
    };
    
    PoolPtr<TestObject> ptr = createPtr();
    EXPECT_TRUE(ptr.isValid());
    EXPECT_EQ(ptr->value, 200);
    EXPECT_EQ(pool.UsedCount(), 1);
}