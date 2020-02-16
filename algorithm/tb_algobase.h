#ifndef __TB_ALGOBASE_H_
#define __TB_ALGOBASE_H_

#include <cstring>

#include "tb_type_traits.h"
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
    std::memmove(result, first, sizeof(Tp) * (last - first));
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
struct __copy_dispatch<Tp*, Tp*> {
    Tp *operator()(Tp *first, Tp *last, Tp *result) {
        return _copy_pod_type(first, last, result,
                              tbSTL::is_trivally_copy_assignable<Tp>());
    }
};

template <class Tp> 
struct __copy_dispatch<const Tp*, Tp*> {
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

/**
 * @brief 因为fill只有字节级的memset，只有char和unisigned char的特例化
 */
template <class ForwardIter, class Tp>
void fill(ForwardIter first, ForwardIter last, const Tp &value)
{
    for ( ; first != last; ++first) {
        *first = value;
    }
}

void fill(char *first, char *last, const char &value)
{
    std::memset(first, value, last - first);
}

void fill(unsigned char *first, unsigned char *last, const unsigned char &value)
{
    std::memset(first, value, last - first);
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter __copy_n(InputIter first, Size count, ForwardIter result,
                     input_iterator_tag)
{
    for ( ; count > 0; --count) {
         *result = *first;
         result++;
         first++;
    }
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter __copy_n(InputIter first, Size count, ForwardIter result, 
                     random_access_iterator_tag)
{
    return tbSTL::copy(first, first + count, result);
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter copy_n(InputIter first, Size count, ForwardIter result)
{
    return __copy_n(first, count, result, tbSTL::iterator_category(result));
}

template <class InputIter, class Size, class Tp>
InputIter __fill_n(InputIter first, Size count, const Tp &value, input_iterator_tag)
{
    for ( ; count > 0; --count) {
        *first++ = value;
    }

    return first;
}

template <class InputIter, class Size, class Tp>
InputIter __fill_n(InputIter first, Size count, const Tp &value, random_access_iterator_tag)
{
    fill(first, first + count, value);
    return first + count;
}

template <class InputIter, class Size, class Tp>
InputIter fill_n(InputIter first, Size count, const Tp &value)
{
    return __fill_n(first, count, value, tbSTL::iterator_category(first));
}

}

#endif