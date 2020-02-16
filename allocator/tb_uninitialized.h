#ifndef __TB_UNITIALIZED_H_
#define __TB_UNITIALIZED_H_

#include <cstring>
#include <cstdlib>

#include "tb_type_traits.h"
#include "allocator/tb_construct.h"
#include "algorithm/tb_algobase.h"

/*
 * unitialized_copy    --> copy, memmove
 * unitialized_fill    --> fill
 * unitialized_copy_n  --> copy_n, memove
 * unitialized_fill_n  --> fill_n
 */

namespace tbSTL {

template <class InputIter, class ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result, 
                                            true_type)
{
    return tbSTL::copy(first, last, result);
}

template <class InputIter, class ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result,
                                            false_type)
{
    ForwardIter cur = result;
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

template <class ForwardIter, class Tp>
inline void __uninitialized_fill_aux(ForwardIter first, ForwardIter last, const Tp &value, true_type) 
{
    tbSTL::fill(first, last, value);
}

template <class ForwardIter, class Tp>
inline void __uninitialized_fill_aux(ForwardIter first, ForwardIter last, const Tp &value, false_type)
{
    for ( ; first != last; ++first) {
        tbSTL::construct(&*first, value);
    }
}

template <class ForwardIter, class InTp, class OutTp>
inline void __uninitialized_fill(ForwardIter first, ForwardIter last, const InTp &value, OutTp *)
{
    return __uninitialized_fill_aux(first, last, value, tbSTL::is_trivally_default_constructible<OutTp>());
}

template <class ForwardIter, class Tp>
inline void uninitialized_fill(ForwardIter first, ForwardIter last, const Tp &value)
{
    return __uninitialized_fill(first, last, value, value(first));
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter __uninitialized_copy_n_aux(InputIter first, Size count, ForwardIter result, true_type)
{
    for ( ; count > 0; --count) {
        tbSTL::construct(&*first, *result);
        ++first; ++result;
    }
    return result;
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter __uninitialized_copy_n_aux(InputIter first, Size count, ForwardIter result, false_type)
{
    return copy_n(first, count, result);
}

template <class InputIter, class Size, class ForwardIter, class Tp>
ForwardIter __uninitialized_copy_n(InputIter first, Size count, ForwardIter result, Tp *)
{
    return __uninitialized_copy_n_aux(first, count, result, tbSTL::is_trivally_default_constructible<Tp>(result));
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter uninitialized_copy_n(InputIter first, Size count, ForwardIter result)
{
    return __uninitialized_copy_n(first, count, result, value_type(result)));
}

template <class ForwardIter, class Size, class Tp>
ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size count, const Tp &value, true_type)
{
    return fill_n(first, count, value);
}

template <class ForwardIter, class Size, class Tp>
ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size count, const Tp &value, false_type)
{
    for ( ; count > 0; --count) {
        tbSTL::construct(&*first, value);
        ++first;
    }

    return first;
}

template <class ForwardIter, class Size, class InTp, class OutTp>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size count, const InTp &value, OutTp *)
{
    return __uninitialized_fill_n_aux(first, count, value, tbSTL::is_trivally_default_constructible<OutTp>(first));
}

template <class ForwardIter, class Size, class Tp>
ForwardIter uninitialized_fill_n(ForwardIter first, Size count, const Tp &value)
{
    return __uninitialized_fill_n(first, count, value, value_type(first));
}

} // namespace tbSTL

#endif // __TB_UNITIALIZED_H_