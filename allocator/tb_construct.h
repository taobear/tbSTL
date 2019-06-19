#ifndef __TB_CONSTRUCT_H_
#define __TB_CONSTRUCT_H_

#include "tb_type_traits.h"
#include "iterator/tb_iterator.h"

namespace tbSTL {

template <class T1, class T2>
inline void construct(T1 *pointer, const T2& val) {
    new (pointer) T1(val);
}
template <class T>
inline void destroy(T *pointer) {
    pointer->~T();
} 

template <class ForwardIter>
inline void __destroy_aux(ForwardIter first, ForwardIter last, true_type) {

}
template <class ForwardIter>
inline void __destroy_aux(ForwardIter first, ForwardIter last, false_type) {
    for ( ; first != last; ++first) {
        destroy(&*first);
    }
}

template <class ForwardIter, class T>
inline void __destroy(ForwardIter first, ForwardIter last, T*) {
    __destroy_aux(first, last, is_trivally_destructible<T>());
}

template <class ForwardIter>
inline void destroy(ForwardIter first, ForwardIter last) {
    __destroy(first, last, value_type(first));
}
template <> inline void destroy(char*, char*) {}
template <> inline void destroy(wchar_t*, wchar_t*) {}

} // namespace tbSTL

#endif // __TB_CONSTRUCT_H_