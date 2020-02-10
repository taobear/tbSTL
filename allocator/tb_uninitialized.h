#ifndef __TB_UNITIALIZED_H_
#define __TB_UNITIALIZED_H_

#include <cstring>
#include <cstdlib>

#include "tb_type_traits.h"
#include "allocator/tb_construct.h"
#include "algorithm/tb_algobase.h"

namespace tbSTL {

template <class InputIter, class ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result, 
                                            false_type)
{
    return tbSTL::copy(first, last, result);
}

template <class InputIter, class ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result,
                                            true_type)
{
    ForwardIter cur = first;
    for ( ; first != last; ++first, ++cur) {
        tbSTL::construct(&*cur, *first);
    }
    return cur;
}

template <class InputIter, class ForwardIter, class Tp>
inline ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, Tp *) 
{
    return __uninitialized_copy_aux(first, last, result, tbSTL::is_trivally_copy_constructible<Tp>());
}

template <class InputIter, class ForwardIter>
inline ForwardIter uninitialized_copy(InputIter first, InputIter last,
                                      ForwardIter result)
{
    return __uninitialized_copy(first, last, result, value_type(result));
}

inline char *uninitialized_copy(char *first, char *last, char *result)
{
    std::memmove(result, first, last - first);
    return result + (last - first);
}

inline wchar_t *uninitialized_copy(wchar_t *first, wchar_t *last, wchar_t *result)
{
    std::memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}

} // namespace tbSTL

#endif // __TB_UNITIALIZED_H_