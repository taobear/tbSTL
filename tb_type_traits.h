
#ifndef __TB_TYPE_TRAITS_H_
#define __TB_TYPE_TRAITS_H_

namespace tbSTL {

template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template <class T, T v> 
constexpr T integral_constant<T, v>::value;

template <bool _b>
using __bool_constant = integral_constant<bool, _b>;

typedef __bool_constant<true> true_type;
typedef __bool_constant<false> false_type;

template <typename T> struct __type_traits {
    typedef true_type this_dummy_member_must_be_first;
    typedef false_type has_trivally_default_constructible;
    typedef false_type has_trivally_copy_constructible;
    typedef false_type has_trivally_move_constructible;
    typedef false_type has_trivally_copy_assignable;
    typedef false_type has_trivally_move_assignable;
    typedef false_type has_trivally_destructible;
    typedef false_type is_pod;
};

#define __TB_TRIVALLY_TYPE_DECLAR \
    typedef true_type has_trivally_default_constructible; \
    typedef true_type has_trivally_copy_constructible;    \
    typedef true_type has_trivally_move_constructible;    \
    typedef true_type has_trivally_copy_assignable;       \
    typedef true_type has_trivally_move_assignable;       \
    typedef true_type has_trivally_destructible;          \
    typedef true_type is_pod;                            

#define __TB_TRIVALLY_TYPE_SPECIAL_DECLAR(_Type)         \
template <> struct __type_traits<_Type> {                \
    __TB_TRIVALLY_TYPE_DECLAR                            \
}

#define __TB_TRIVALLY_TYPE_PARTIAL_DECLAR(_Tmp, _Type)   \
template <typename _Tmp> struct __type_traits<_Type> {   \
    __TB_TRIVALLY_TYPE_DECLAR                            \
}

__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(bool);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(char);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(unsigned char);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(signed char);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(wchar_t);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(short);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(unsigned short);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(int);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(unsigned int);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(long);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(unsigned long);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(long long);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(unsigned long long);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(float);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(double);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(long double);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(char*);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(signed char*);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(unsigned char*);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(const char*);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(const signed char*);
__TB_TRIVALLY_TYPE_SPECIAL_DECLAR(const unsigned char*);

__TB_TRIVALLY_TYPE_PARTIAL_DECLAR(Tp, Tp*);

#undef __TB_TRIVALLY_TYPE_DECLAR
#undef __TB_TRIVALLY_TYPE_SPECIAL_DECLAR
#undef __TB_TRIVALLY_TYPE_PARTIAL_DECLAR


template <typename Tp> struct is_trivally_default_constructible 
    : public __type_traits<Tp>::has_trivally_default_constructible {};
template <typename Tp> struct is_trivally_copy_constructible
    : public __type_traits<Tp>::has_trivally_copy_constructible {};
template <typename Tp> struct is_trivally_move_constructible
    : public __type_traits<Tp>::has_trivally_move_constructible {};
template <typename Tp> struct is_trivally_copy_assignable 
    : public __type_traits<Tp>::has_trivally_copy_assignable {};
template <typename Tp> struct is_trivally_move_assignable
    : public __type_traits<Tp>::has_trivally_move_assignable {};
template <typename Tp> struct is_trivally_destructible 
    : public __type_traits<Tp>::has_trivally_destructible {};

template <typename Tp> struct remove_const {
    typedef Tp type;
};
template <typename Tp> struct remove_const<const Tp> {
    typedef Tp type;
};

template <typename Tp> struct remove_volatile {
    typedef Tp type;
};
template <typename Tp> struct remove_volatile<volatile Tp> {
    typedef Tp type;
};

template <typename Tp> struct remove_cv {
    typedef typename 
        remove_const<remove_volatile<Tp>::type>::type type;
};

template <typename Tp>  struct __is_void_helper : public false_type {};
template <> struct __is_void_helper<void> : public true_type {};
template <typename Tp> struct is_void 
    : public __is_void_helper<remove_cv<Tp>::type> {};

template <typename Tp> struct __is_integral_helper : public false_type {};
template <> struct __is_integral_helper<bool> : public true_type {};
template <> struct __is_integral_helper<char> : public true_type {};
template <> struct __is_integral_helper<unsigned char> : public true_type {};
template <> struct __is_integral_helper<wchar_t> : public true_type {};
template <> struct __is_integral_helper<short> : public true_type {};
template <> struct __is_integral_helper<unsigned short> : public true_type {};
template <> struct __is_integral_helper<int> : public true_type {};
template <> struct __is_integral_helper<unsigned int> : public true_type {};
template <> struct __is_integral_helper<long> : public true_type {};
template <> struct __is_integral_helper<unsigned long> : public true_type {};
template <> struct __is_integral_helper<long long> : public true_type {};
template <> struct __is_integral_helper<unsigned long long> : public true_type {};

template <typename Tp> struct is_integral
    : public __is_integral_helper<remove_cv<Tp>::type> {};

template <typename Tp1, typename Tp2>
struct is_same : public false_type {};
template <typename Tp>
struct is_same<Tp, Tp> : public true_type {};

} // namespace tbSTL

#endif // __TB_TYPE_TRAITS_H_