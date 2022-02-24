//
// Created by oran on 2/24/22.
//

#pragma once
/**
 * adapted from
 * https://stackoverflow.com/questions/8456236/how-is-a-vectors-data-aligned
 * and the lecture slides
 */
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <vector>

template<typename T, std::size_t N = 16>
class aligned_allocator {
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef T *pointer;
    typedef const T *const_pointer;

    typedef T &reference;
    typedef const T &const_reference;

public:
    inline aligned_allocator() noexcept = default;

    template<typename T2>
    inline explicit aligned_allocator(
            const aligned_allocator<T2, N> &) noexcept {}

    inline ~aligned_allocator() noexcept = default;

    inline pointer adress(reference r) { return &r; }

    inline const_pointer adress(const_reference r) const { return &r; }

    inline pointer allocate(size_type n) {
#if defined(_WIN32)
        return (pointer) _aligned_malloc(n * sizeof(value_type), N);
#else
        void *m = nullptr;
        if (posix_memalign(&m, N, n * sizeof(value_type))) {
            puts("cannot allocate that much memory!");
            exit(1); // couldn't allocate enough memory
        }
        return (pointer)m;
#endif
    }

    inline void deallocate(pointer p, size_type) {
#if defined(_WIN32)
        _aligned_free(p);
#else
        free(p);
#endif
    }

    inline void construct(pointer p, const value_type &wert) {
        new(p) value_type(wert);
    }

    inline void destroy(pointer p) { p->~value_type(); }

    inline size_type max_size() const noexcept {
        return size_type(-1) / sizeof(value_type);
    }

    template<typename T2>
    struct rebind {
        typedef aligned_allocator<T2, N> other;
    };

    bool operator!=(const aligned_allocator<T, N> &other) const {
        return !(*this == other);
    }

    // Returns true if and only if storage allocated from *this
    // can be deallocated from other, and vice versa.
    // Always returns true for stateless allocators.
    bool operator==(const aligned_allocator<T, N> &other) const { return true; }
};

//make the template class available for the whole project
template <class T>
using aligned_vector = std::vector<T, aligned_allocator<T, 64>>;
