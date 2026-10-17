/** @file diagnosticism/nanoseconds_to_string.hpp
 * @brief Compact nanosecond duration formatting (C++ API).
 *
 * @ingroup diagnosticism_nanoseconds_to_string
 */


#ifndef DIAGNOSTICISM_INCL_DIAGNOSTICISM_HPP_NANOSECONDS_TO_STRING
#define DIAGNOSTICISM_INCL_DIAGNOSTICISM_HPP_NANOSECONDS_TO_STRING


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/nanoseconds_to_string.h>

#include <stdexcept>
#include <string>


namespace diagnosticism {

/** Formats a nanosecond count into @a result.
 *
 * @tparam T_string A mutable string-like type providing
 *  `assign(char const* s, size_t n)` (e.g. `std::string`,
 *  `stlsoft::simple_string`, `stlsoft::basic_static_string`).
 *
 * @param result Destination string; overwritten with the formatted
 *  duration;
 * @param nanoseconds The duration, in nanoseconds;
 * @param flags `DIAGNOSTICISM_NS_TO_STRING_F_*` flags; defaults to
 *  `DIAGNOSTICISM_NS_TO_STRING_F_NONE`;
 *
 * @return A reference to @a result.
 *
 * @throws std::runtime_error on formatting failure.
 *
 * @see nanoseconds_to_string(int64_t, uint32_t)
 * @see diagnosticism_nanoseconds_to_string()
 */
template <typename T_string>
inline
T_string&
nanoseconds_to_string(
    T_string&   result
,   int64_t     nanoseconds
,   uint32_t    flags = DIAGNOSTICISM_NS_TO_STRING_F_NONE
)
{
    char        buff[DIAGNOSTICISM_NS_TO_STRING_MIN_CCH];
    size_t      n;
    int const   r = diagnosticism_nanoseconds_to_string(
        sizeof(buff) / sizeof(buff[0])
    ,   buff
    ,   nanoseconds
    ,   flags
    ,   &n
    );

    if (r < 0)
    {
        throw std::runtime_error("failed to format nanoseconds string");
    }

    result.assign(buff, n);

    return result;
}

/** Formats a nanosecond count as a compact duration `std::string`.
 *
 * @param nanoseconds The duration, in nanoseconds;
 * @param flags `DIAGNOSTICISM_NS_TO_STRING_F_*` flags; defaults to
 *  `DIAGNOSTICISM_NS_TO_STRING_F_NONE`;
 *
 * @return Formatted duration (for example @c "123.4ms").
 *
 * @throws std::runtime_error on formatting failure.
 *
 * @see nanoseconds_to_string(T_string&, int64_t, uint32_t)
 * @see diagnosticism_nanoseconds_to_string()
 */
inline
std::string
nanoseconds_to_string(
    int64_t     nanoseconds
,   uint32_t    flags = DIAGNOSTICISM_NS_TO_STRING_F_NONE
)
{
    std::string result;

    return nanoseconds_to_string(result, nanoseconds, flags);
}

} // namespace diagnosticism


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !DIAGNOSTICISM_INCL_DIAGNOSTICISM_HPP_NANOSECONDS_TO_STRING */

/* ///////////////////////////// end of file //////////////////////////// */

