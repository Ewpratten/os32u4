#if !defined(_OS_UTIL_MATH_HH)
#define _OS_UTIL_MATH_HH

namespace os {
namespace util {
namespace math {

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

}  // namespace math
}  // namespace util
}  // namespace os

#endif  // _OS_UTIL_MATH_HH
