#ifndef __TB_UNITIALIZED_H_
#define __TB_UNITIALIZED_H_

namespace tbSTL {

template <class InputIter, class ForwardIter>
inline ForwardIter __uninitialized_copy()

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last,
                               ForwardIter result)
{

}

template <class ForwardIter, class Tp>
void unitialized_fill(ForwardIter first, ForwardIter last,
                      const Tp &x)
{

}

template <class ForwardIter, class Size, class Tp>
inline ForwardIter unitialized_fill_n(ForwardIter first, Size n, const T& x)
{

}




} // namespace tbSTL

#endif // __TB_UNITIALIZED_H_