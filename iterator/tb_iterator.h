#ifndef __TB_ITERATOR_H_
#define __TB_ITERATOR_H_

#include "tb_iterbase.h"

namespace tbSTL {

template <class Container> 
class back_insert_iterator {
public:
    typedef Container container_type;
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit back_insert_iterator(Container &_x) : container(&_x) {}
    back_insert_iterator<container_type> &
    operator=(const typename container_type::value_type &val) {
        container->push_back(val);
        return *this;
    }

    back_insert_iterator<container_type> &operator*() { return *this; }
    back_insert_iterator<container_type> &operator++() { return *this; }
    back_insert_iterator<container_type> &operator++(int) { return *this; }
protected:
    container_type *container;
};

template <class Container>
inline back_insert_iterator<Container> back_inserter(Container& _x) {
    return back_insert_iterator<Container>(_x);
}

template <class Container>
class front_insert_iterator {
public:
    typedef Container container_type;
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit front_insert_iterator(container_type &x) : container(&x) {}
    front_insert_iterator<container_type> &
    operator=(const typename container_type::value_type &val) {
        container->push_front(val);
        return *this;
    }

    front_insert_iterator<container_type> &operator*() { return *this; }
    front_insert_iterator<container_type> &operator++() { return *this; }
    front_insert_iterator<container_type> &operator++(int) { return *this; }

protected:
    container_type *container;
};

template <class Container>
inline front_insert_iterator<Container> front_inserter(Container& _x) {
    return front_insert_iterator<Container>(_x);
}

template <class Container>
class insert_iterator {
public:
    typedef Container container_type;
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    insert_iterator(Container &x, typename container_type::iterator i)
        : container(&x), iter(i) {}
    insert_iterator<container_type> &
    operator=(const typename container_type::value_type &val) {
        iter = container->insert(iter, val);
        ++iter;
        return *this;
    }

    insert_iterator<container_type> &operator*() { return *this; }
    insert_iterator<container_type> &operator++() { return *this; }
    insert_iterator<container_type> &operator++(int) { return *this; }
protected:
    container_type *container;
    typename container_type::iterator iter;
};

template <class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& _x, Iterator _i) {
    typedef typename Container::iterator iterator_type;
    return insert_iterator<Container>(_x, iterator_type(_i));
}

template <class Iterator>
class reverse_iterator {
public:
    typedef typename iterator_traits<Iterator>::iterator_category 
            iterator_category;
    typedef typename iterator_traits<Iterator>::value_type   
            value_type;
    typedef typename iterator_traits<Iterator>::difference_type
            difference_type;
    typedef typename iterator_traits<Iterator>::pointer
            pointer;
    typedef typename iterator_traits<Iterator>::reference
            reference;
    
    typedef Iterator iterator_type;
    typedef reverse_iterator<Iterator> _Self;

public:
    reverse_iterator() {}
    explicit reverse_iterator(iterator_type _x) : current(_x) {}

    reverse_iterator(const _Self& _x) : current(_x.current) {}
    template <class _Iter>
    reverse_iterator(const reverse_iterator<_Iter>& _x) 
        : current(_x.base()) {}

    iterator_type base() const { return current; }
    reference operator*() const {
        iterator_type tmp = current;
        return *--tmp;
    }
    pointer operator->() const { return &(this->operator*()); }

    _Self& operator++() {
        --current;
        return *this;
    }
    _Self operator++(int) {
        _Self tmp = *this;
        --current;
        return tmp;
    }
    _Self& operator--() {
        ++current;
        return *this;
    }
    _Self operator--(int) {
        _Self tmp = *this;
        ++current;
        return tmp;
    }

    _Self operator+(difference_type n) const {
        return _Self(current - n);
    }
    _Self& operator+=(difference_type n) {
        current -= n;
        return *this;
    }
    _Self operator-(difference_type n) const {
        return _Self(current + n);
    }
    _Self& operator-=(difference_type n) {
        current += n;
        return *this;
    }
    
    reference operator[](difference_type n) const {
        return *(*this + n);
    }

protected:
    Iterator current;
};

template <class Iterator>
inline bool operator==(const reverse_iterator<Iterator> &lhs,
                       const reverse_iterator<Iterator> &rhs) {
    return lhs.base() == rhs.base();
}
template <class Iterator>
inline bool operator!=(const reverse_iterator<Iterator> &lhs,
                       const reverse_iterator<Iterator> &rhs) {
    return !(lhs == rhs);
}
template <class Iterator>
inline bool operator<(const reverse_iterator<Iterator> &lhs,
                      const reverse_iterator<Iterator> &rhs) {
    return rhs.base() < lhs.base();
}
template <class Iterator>
inline bool operator>(const reverse_iterator<Iterator> &lhs,
                      const reverse_iterator<Iterator> &rhs) {
    return rhs < lhs;
}
template <class Iterator>
inline bool operator<=(const reverse_iterator<Iterator> &lhs,
                       const reverse_iterator<Iterator> &rhs) {
    return !(rhs < lhs);
}
template <class Iterator>
inline bool operator>=(const reverse_iterator<Iterator> &lhs,
                       const reverse_iterator<Iterator> &rhs) {
    return !(lhs < rhs);
}

template <class Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& x, 
          const reverse_iterator<Iterator>& y) {
    return x - y;
}
template <class Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator>& x) {
    return x + n;    
}

} // namespace tbSTL

#endif // __TB_ITERATOR_H_