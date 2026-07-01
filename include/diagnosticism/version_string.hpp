
/** @file diagnosticism/version_string.hpp
 * @brief Version-string formatting (C++ API).
 *
 * @ingroup diagnosticism_version
 */

#include <diagnosticism/version_string.h>

#include <stdexcept>
#include <string>


namespace diagnosticism {

/** C++ wrapper around diagnosticism_calc_version_string().
 *
 * @param verMajor Major version component.
 * @param verMinor Minor version component.
 * @param verPatch Patch version component.
 * @param verAlphaBeta Alpha/beta/rc/build encoding; see
 *  diagnosticism_calc_version_string().
 *
 * @return Formatted version string (for example @c "1.2.3").
 *
 * @throws std::runtime_error on formatting failure.
 */
inline
std::string
calc_version_string(
    uint16_t    verMajor
,   uint16_t    verMinor
,   uint16_t    verPatch
,   uint16_t    verAlphaBeta
)
{
    char        buff[93];
    size_t      n;
    int const   r = diagnosticism_calc_version_string(
        buff, sizeof(buff) / sizeof(buff[0])
    ,   verMajor, verMinor, verPatch, verAlphaBeta
    ,   &n
    );

    if (r < 0)
    {
        throw std::runtime_error("failed to calculate version string");
    }

    return std::string(buff, n);
}

} // namespace diagnosticism


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#pragma once

/* ///////////////////////////// end of file //////////////////////////// */
