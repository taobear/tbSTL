#ifndef __TB_ALLOC_H_
#define __TB_ALLOC_H_

#include <cstdlib>
#include <assert.h>

namespace tbSTL {

template <class Tp, class Alloc>
class simple_alloc {
public:
    static Tp *allocate(size_t n) { 
        return 0 == n ? 0 : (T*)Alloc::allocate(n*sizeof(Tp)); 
    }
    static Tp *allocate() {
        return (T*)Alloc::allocate(sizeof(Tp));
    } 
    static void deallocate(Tp *p, size_t n) {
        if (0 != n) { Alloc::deallocate(p, n * sizeof(Tp)); }
    }
    static void deallocate(Tp *p) {
        Alloc::deallocate(p, sizeof(Tp));
    }
};

class __malloc_alloc {
public:
  typedef void (*malloc_new_handler_t)();

  static void *allocate(size_t n);
  static void *reallocate(void *p, size_t old_sz, size_t new_sz);
  static void deallocate(void *p, size_t n);
  static malloc_new_handler_t set_malloc_handler(malloc_new_handler_t func);
private:
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static malloc_new_handler_t oom_handler;
};

void *__malloc_alloc::allocate(size_t n)
{
    void *result = std::malloc(n);
    if (result == nullptr) {
        result = oom_malloc(n);
    }
    return result;
}

void *__malloc_alloc::reallocate(void *p, size_t old_sz, size_t new_sz)
{
    void *result = std::realloc(p, new_sz);
    if (result == nullptr) {
        result = oom_malloc(new_sz);
    }
    return result;
}

void __malloc_alloc::deallocate(void *p, size_t n)
{
    std::free(p);
}

__malloc_alloc::malloc_new_handler_t
__malloc_alloc::set_malloc_handler(malloc_new_handler_t func)
{
    malloc_new_handler_t old_handler = oom_handler;
    oom_handler = func;
    return old_handler;
}

__malloc_alloc::malloc_new_handler_t __malloc_alloc::oom_handler = nullptr;

void *__malloc_alloc::oom_malloc(size_t n)
{
    void *result;
    malloc_new_handler_t my_alloc_handler;
    
    while (true) {
        my_alloc_handler = oom_handler;
        assert(my_alloc_handler != 0);
        my_alloc_handler();
        result = malloc(n);
        if (result) return result;
    }
}

void *__malloc_alloc::oom_realloc(void *p, size_t n)
{
    void *result;
    malloc_new_handler_t my_alloc_handler;

    while (true) {
        my_alloc_handler = oom_handler;
        assert(my_alloc_handler != 0);
        my_alloc_handler();
        result = realloc(p, n);
        if (result) return result;
    }
}

static constexpr int __ALIGN = 8;
static constexpr int __MAX_BYTES = 128;
static constexpr int __NFREELISTS = __MAX_BYTES / __ALIGN;
class __default_alloc {
public:
    static void *allocate(size_t n);
    static void *reallocate(void *p, size_t old_sz, size_t new_sz);
    static void deallocate(void *p, size_t n);
private: 
   union obj {
        union obj * free_list_link;
        char client_data[];
    };
    static obj * volatile free_list[__NFREELISTS];
    
    static size_t ROUND_UP(size_t bytes) {
        return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1)); // 先加7，再将二进制后三位置0
    }

    static size_t FREELIST_INDEX(size_t bytes) {
        return ((bytes + __ALIGN - 1) / __ALIGN - 1);
    }

private:
    static void *refill(size_t n);
    static char *chunk_alloc(size_t size, int &nobjs);

    static char *start_free;
    static char *end_free;
    static size_t heap_size;
};

char *__default_alloc::start_free = 0;
char *__default_alloc::end_free = 0;
size_t __default_alloc::heap_size = 0;

__default_alloc::obj * volatile
__default_alloc::free_list[__NFREELISTS] = 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

} // namespace tbSTL

#endif // __BT_ALLOC_H_