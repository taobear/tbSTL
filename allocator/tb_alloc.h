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

void *__default_alloc::allocate(size_t n)
{
    if (n >= __MAX_BYTES) {
        return __malloc_alloc::allocate(n);
    }

    obj * volatile *my_free_list;
    obj *result;

    my_free_list = free_list + FREELIST_INDEX(n);
    result = *my_free_list;
    if (result == nullptr) {
        return refill(n);
    }
    
    *my_free_list = result->free_list_link;
    return result;
}

void *__default_alloc::reallocate(void *p, size_t old_sz, size_t new_sz)
{

}

void __default_alloc::deallocate(void *p, size_t n)
{
    if (n >= __MAX_BYTES) {
        return __malloc_alloc::deallocate(p, n);
    }

    obj *volatile *my_free_list;
    obj *q = (obj *)p;

    my_free_list = free_list + FREELIST_INDEX(n);
    q->free_list_link = *my_free_list;
    *my_free_list = q;        
}

void *__default_alloc::refill(size_t n)
{
    int nobjs = 20;
    obj * volatile * my_free_list;
    obj *result;
    obj *next_obj, *current_obj;
    char *chunk = chunk_alloc(n, nobjs);

    if (nobjs == 1) {
        return chunk;
    }

    my_free_list = free_list + FREELIST_INDEX(n);
    result = (obj *)chunk;
    *my_free_list = next_obj = (obj *)(chunk + n);

    for (int i = 1; ; i++) {
        current_obj = next_obj;
        next_obj = (obj *)((char*)next_obj + n);
        if (i == nobjs - 1) {
            current_obj->free_link_list = next_obj;
        } else {
            current_obj->free_link_list = nullptr;
        }
    }
    return result;
}

void *__default_alloc::chunk_alloc(size_t n, int &nobjs) 
{
    char *result;
    size_t total_bytes = n * nobjs;
    size_t left_bytes = end_free - start_free;

    if (left_bytes >= total_bytes) {
        result = start_free;
        start_free += total_bytes;
        return result;
    } else if (left_bytes >= n) {
        nobjs = left_bytes / n;
        total_bytes = n * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    } else {
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        if (left_bytes > 0) {
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(left_bytes);
            ((obj *)start_free) -> free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }

        start_free = (char *)malloc(bytes_to_get);
        if (start_free == 0) {
            int i;
            obj * volatile * my_free_list, *p;
            for ( i = n; i <= __MAX_BYTES; i += __ALIGN) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (p != 0) {
                    *my_free_list = p->free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    return chunk_alloc(n, nobjs);
                }
            }
            end_free = 0;
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
        }

        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

} // namespace tbSTL

#endif // __BT_ALLOC_H_