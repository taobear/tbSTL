#ifndef __TB_ALGOBASE_H_
#define __TB_ALGOBASE_H_

#include <cstring>

#include "iterator/tb_iterator.h"

namespace tbSTL {

template <class RandomIter, class ForwardIter, class Distance>
ForwardIter __copy_random(RandomIter first, RandomIter last, ForwardIter result,
                          Distance *)
{
    for (Distance n = last - first; n > 0; --n, ++first, ++result) {
        *result = *first;
    }
    return result;
}

template <class InputIter, class ForwardIter>
ForwardIter _copy_tag(InputIter first, InputIter last, ForwardIter result, 
                      input_iterator_tag)
{
    for ( ; first != last; ++first, ++result) {
        *result = *first;
    }
    return result;
}

template <class RandomIter, class ForwardIter>
ForwardIter _copy_tag(RandomIter first, RandomIter last, ForwardIter result,
                      random_access_iterator_tag)
{
    __copy_random(first, last, result, difference_type(first));
}

template <class Tp>
Tp* _copy_pod_type(Tp *first, Tp *last, Tp *result, true_type) {
    std::memmove(result, first, last - first);
    return result + (last - first);
}

template <class Tp>
Tp *_copy_pod_type(Tp *first, Tp *last, Tp *result, false_type) {
    return _copy_tag(first, last, result, tbSTL::iterator_category(first));
}

template <class InputIter, class ForwardIter> 
struct __copy_dispatch {
    ForwardIter operator()(InputIter first, InputIter last, ForwardIter result) {
        return _copy_tag(first, last, result, tbSTL::iterator_category(first));
    }
};

template <class Tp> 
struct __copy_dispatch <Tp, Tp> {
    Tp *operator()(Tp *first, Tp *last, Tp *result) {
        return _copy_pod_type(first, last, result,
                              tbSTL::is_trivally_copy_assignable<Tp>());
    }
};

template <class Tp> 
struct __copy_dispatch <const Tp, Tp> {
    Tp* operator()(const Tp* first, const Tp* last, Tp* result) {
        return _copy_pod_type(first, last, result,
                              tbSTL::is_trivally_copy_assignable<Tp>());
    }
};

template <class InputIter, class ForwardIter>
ForwardIter copy(InputIter first, InputIter last, ForwardIter result)
{
    return __copy_dispatch<InputIter, ForwardIter>()(first, last, result);
}

}

#endif