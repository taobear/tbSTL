#ifndef __TB_ITERBASE_H_
#define __TB_ITERBASE_H_

#include <cstddef>

namespace tbSTL {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag : public input_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class Tp, class Distance = std::ptrdiff_t,
          class Pointer = Tp*, class Reference = Tp&>
struct iterator {
    typedef Category  iterator_category;
    typedef Tp        value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
};

template <class Tp>
struct iterator_traits<Tp*> {
    typedef random_access_iterator_tag iterator_category;
    typedef Tp                         value_type;
    typedef std::ptrdiff_t             difference_type;
    typedef Tp*                        pointer;
    typedef Tp&                        reference;  
};

template <class Tp>
struct iterator_traits<const Tp*> {
    typedef random_access_iterator_tag iterator_category;
    typedef Tp                         value_type;
    typedef std::ptrdiff_t             difference_type;
    typedef const Tp*                  pointer;
    typedef const Tp&                  reference;
};

template <class Iter>
inline typename iterator_traits<Iter>::iterator_category
iterator_category(const Iter&) {
    typedef typename iterator_traits<Iter>::iterator_category category;
    return category();
}

template <class Iter>
inline typename iterator_traits<Iter>::difference_type*
difference_type(const Iter&) {
    typedef typename iterator_traits<Iter>::difference_type* difference_type;
    return static_cast<difference_type>(nullptr);
}

template <class Iter>
inline typename iterator_traits<Iter>::value_type*
value_type(const Iter&) {
    typedef typename iterator_traits<Iter>::value_type* value_type;
    return static_cast<value_type>(nullptr);
}

template <class InputIter>
inline typename iterator_traits<InputIter>::difference_type
__distance(InputIter first, InputIter last, input_iterator_tag) {
    typename iterator_traits<InputIter>::difference_type n = 0;
    while (first != last) {
        first++; n++;
    }
    return n;
}

template <class RandomIter>
inline typename iterator_traits<RandomIter>::difference_type
__distance(RandomIter first, RandomIter last, random_access_iterator_tag) {
    return last - first;
}

template <class InputIter>
inline typename iterator_traits<InputIter>::difference_type
distance(InputIter first, InputIter last)
{
    return __distance(first, last, iterator_category(first));
}

template <class InputIter, class Distance>
inline void __advance(InputIter &i, Distance n, 
                      input_iterator_tag) {
    while (n--) ++i;
}

template <class BidirectIter, class Distance> 
inline void __advance(BidirectIter &i, Distance n, 
                      bidirectional_iterator_tag) {
    if (n >= 0) {
        while (n--) ++i;
    } else {
        while (n++) --i;
    }
}

template <class RandomIter, class Distance>
inline void __advance(RandomIter &i, Distance n, 
                      random_access_iterator_tag) {
    i += n;
}

template <class InputIter, class Distance>
inline void advance(InputIter &i, Distance n) {
    __advance(i, n, iterator_category(i));
}



} // namespace tbSTL

#endif // __TB_ITERBASE_H_