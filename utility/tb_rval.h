#ifndef __TB_RVAL_H_
#define __TB_RVAL_H_

namespace tbSTL {

template <typename Tp>
struct remove_reference {
    typedef Tp type;
};

template <typename Tp>
struct remove_reference <Tp&> {
    typedef Tp type;
};

template <typename Tp>
using remove_reference_t = typename remove_reference<Tp>::type;

template <typename Tp>
Tp && forward(remove_reference_t<Tp>& t) noexcept {
    return static_cast<Tp&&>(t);
}

template <typename Tp>
Tp && forward(remove_reference_t<Tp>&& t) noexcept {
    return static_cast<Tp&&>(t);
}

template <typename Tp>
remove_reference_t<Tp>&& move(Tp&& t) noexcept {
    return static_cast<remove_reference_t<Tp>&&>(t);
}

} // namespace tbSTL

#endif // __TB_RVAL_H_
