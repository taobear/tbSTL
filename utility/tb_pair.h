#ifndef __TB_PAIR_H_
#define __TB_PAIR_H_

namespace tbSTL {

template <typename T>
void swap(T& a, T& b);

template <typename T1, typename T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    pair() : first(T1()), second(T2()) { }
    pair(const T1& t1, const T2& t2)
        : first(t1), second(t2) { }
    pair& operator=(const pair& p);

    template <typename U, typename V>
    pair(const pair<U, V>& other)
        : first(other.first), second(other.second) { };

    void swap(pair& p);

    T1 first;
    T2 second;
};

template <typename T1, typename T2>
pair<T1, T2> &
pair<T1, T2>::operator=(const pair<T1, T2>& p) {
    if (this != &p) {
        first = p.first;
        second = p.second;
    }
    return *this;
};

template <typename T1, typename T2>
void pair<T1, T2>::swap(pair<T1, T2>& p) {
    swap(first, p.first);
    swap(second, p.second);
};

template <typename T1, typename T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first == rhs.second && lhs.second == rhs.second;
};

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
};

template <typename T1, typename T2>
bool operator< (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first < rhs.first ||
            (lhs.first == rhs.first && lhs.second < rhs.second);
};

template <typename T1, typename T2>
bool operator> (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return rhs < lhs;
};

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(rhs < lhs);
};

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(const T1& t1, const T2& t2) {
    return pair<T1, T2>(t1, t2);
}

} // namespace tbSTL

#endif // __TB_PAIR_H_
