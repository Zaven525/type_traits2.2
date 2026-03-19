#include <iostream>
#include <type_traits>


template <typename T, typename U>
struct is_same : std::false_type {};
template<typename T>
struct is_same<T, T> : std::true_type {};

template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;


template <typename T>
struct is_void : std::false_type{};
template <>
struct is_void<void> : std::true_type{};

template <typename T>
inline constexpr bool is_void_v = is_void<T>::value;


template <typename T>
struct is_pointer : std::false_type{};
template <typename T>
struct is_pointer<T*> : std::true_type{};
template <typename T>
struct is_pointer<T* const> : std::true_type{};
template <typename T>
struct is_pointer<T* volatile> : std::true_type{};
template <typename T>
struct is_pointer<T* const volatile> : std::true_type{};

template <typename T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;


template <typename T>
struct remove_reference { using type = T; };
template <typename T>
struct remove_reference<T&> { using type = T; };
template <typename T>
struct remove_reference<T&&> { using type = T; };

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;


template <typename T>
struct add_reference { using type = T&; };
template <>
struct add_reference<void> { using type = void; };

template <typename T>
using add_reference_t = typename add_reference<T>::type;


template <typename T>
struct is_reference : std::false_type{};
template <typename T>
struct is_reference<T&> : std::true_type{};
template <typename T>
struct is_reference<T&&> : std::true_type{};

template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;


template <typename T>
struct is_const : std::false_type{};
template <typename T>
struct is_const<const T> : std::true_type{};

template <typename T>
inline constexpr bool is_const_v = is_const<T>::value;


template <typename T>
struct remove_const { using type = T; };
template <typename T>
struct remove_const<const T> { using type = T; };

template <typename T>
using remove_const_t = typename remove_const<T>::type;


template <typename To, typename From>
struct is_convertible
{
    private:
        template <typename U>
        static auto test(int) -> decltype(
            static_cast<To>(std::declval<U>()), 
            std::true_type{}
        );

        template <typename U>
        static std::false_type test(...);

    public:
        constexpr static bool { value = decltype(test<From>(int))::value };
};


template <bool, typename T1, typename T2>
struct conditional
{
    using type = T2;
};
template <typename T1, typename T2>
struct conditional <true, T1, T2>
{
    using type = T1;
};
template <bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;


template <bool, typename T1 = void>
struct enable_if {};
template <bool, typename T1>
struct enable_if<true, T1>
{
    using type = T1;
};
template <bool B, T1 = void>
using enable_if_t = typename enable_if<B, T1>::type;


template <typename Derived, typename Base>
struct is_base_of
{
    static std::true_type test(const Base*);
    static std::false_type test(...);

    static constexpr inline bool value = decltype(test(static_cast<Derived*>(nullptr)))::value;
};
template <typename Derived, typename Base>
using is_base_of_v = is_base_of::value;


tmeplate <typename T>
struct is_default_constructable
{
    static auto test(int) -> decltype(T(), std::true_type);
    static std::false_type test(...);

    static constexpr inline value = decltype(test(0))::value;
};
template <typename T>
using is_default_constructable_v = is_default_constructable::value;

template <typename T>
struct decay
{
    using U = std::remove_reference<T>::type;
    
    using type = std::conditional<
    is_array<U>::value, 
    typename std::remove_extent<U>::type*,
    
    typename std::conditional <
        std::is_function<U>::value, 
        typename std::add_pointer<U>::type,
        typename std::remove_cv<U>::type
    >::type
    >::type;
};


int main()
{
    static_assert(is_same<int, int>::value);
    static_assert(is_void<void>::value);
    static_assert(is_pointer<int*>::value);
    static_assert(is_reference<int&>::value);
    static_assert(is_const<const int>::value);

    return 0;
}
