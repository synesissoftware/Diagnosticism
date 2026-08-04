
#include <diagnosticism/ev.h>

#include <errno.h>
#include <stdlib.h>


DIAGNOSTICISM_CALL(char const*)
diagnosticism_getenv(
    char const*             name
,   char const*             defaultValueOrNull
)
{
    char const* r = getenv(name);

    if (NULL == r)
    {
        errno = ENOENT;

        return defaultValueOrNull;
    }
    else
    {
        return r;
    }
}

DIAGNOSTICISM_CALL(int)
diagnosticism_getenv_atoi(
    char const*             name
,   int                     defaultValue
)
{
    char const* r = getenv(name);

    if (NULL == r)
    {
        errno = ENOENT;

        return defaultValue;
    }
    else
    {
        return atoi(r);
    }
}

