#ifndef __TB_RELOPS_H
#define __TB_RELOPS_H

namespace tbSTL {
namespace rel_ops {

template <typename T>
inline bool operator!=(const T& lhs, const T& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline bool operator> (const T& lhs, const T& rhs) {
    return rhs < lhs;
}

template <typename T>
inline bool operator<=(const T& lhs, const T& rhs) {
    return !(rhs < lhs);
}

template <typename T>
inline bool operator>=(const T& lhs, const T& rhs) {
    return !(lhs < rhs);
}

} // namespace rel_ops

} // namespace tbSTL

#endif // __TB_RELOPS_H
