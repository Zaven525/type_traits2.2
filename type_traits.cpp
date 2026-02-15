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
        static auto test(void *) -> decltype(static_cast<To>(std::declval<U>()), std::true_type{});

        template <typename U>
        static std::false_type test(...) {}

    public:
        constexpr static bool { value = decltype(test<From(nullptr))::value };
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