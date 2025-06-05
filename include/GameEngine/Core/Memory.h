#pragma once
#include <memory>
#include <vector>
#include <cstddef>

namespace GameEngine {
namespace Core {

// Simple memory pool for fixed-size allocations
template<typename T, size_t PoolSize = 1024>
class MemoryPool {
private:
    alignas(T) char pool[sizeof(T) * PoolSize];
    std::vector<T*> freeList;
    size_t nextFree;

public:
    MemoryPool() : nextFree(0) {
        // Initialize free list
        for (size_t i = 0; i < PoolSize; ++i) {
            freeList.push_back(reinterpret_cast<T*>(&pool[i * sizeof(T)]));
        }
    }

    template<typename... Args>
    T* Allocate(Args&&... args) {
        if (freeList.empty()) {
            return nullptr; // No free memory available
        }

        T* ptr = freeList.back();
        freeList.pop_back();

        // Placement new
        new(ptr) T(std::forward<Args>(args)...);
        return ptr;
    }

    void Deallocate(T* ptr) {
        if (ptr == nullptr) return;

        // Call destructor
        ptr->~T();

        // Return to free list
        freeList.push_back(ptr);
    }

    size_t AvailableCount() const { return freeList.size(); }
    size_t UsedCount() const { return PoolSize - freeList.size(); }
};

// RAII wrapper for memory pool
template<typename T>
class PoolPtr {
private:
    T* ptr;
    MemoryPool<T>* pool;

public:
    PoolPtr(T* p, MemoryPool<T>* pool) : ptr(p), pool(pool) {}

    ~PoolPtr() {
        if (ptr && pool) {
            pool->Deallocate(ptr);
        }
    }

    // Move semantics
    PoolPtr(PoolPtr&& other) noexcept : ptr(other.ptr), pool(other.pool) {
        other.ptr = nullptr;
        other.pool = nullptr;
    }

    PoolPtr& operator=(PoolPtr&& other) noexcept {
        if (this != &other) {
            if (ptr && pool) {
                pool->Deallocate(ptr);
            }
            ptr = other.ptr;
            pool = other.pool;
            other.ptr = nullptr;
            other.pool = nullptr;
        }
        return *this;
    }

    // Disable copy semantics
    PoolPtr(const PoolPtr&) = delete;
    PoolPtr& operator=(const PoolPtr&) = delete;

    T* operator->() { return ptr; }
    T& operator*() { return *ptr; }
    bool isValid() const { return ptr != nullptr; }
};

}} // namespace GameEngine::Core