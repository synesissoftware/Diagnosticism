
#include <diagnosticism/abort.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[])
{
    char                time_buf[64];
    time_t              t;
    struct tm           tm;
    size_t              n;

    ((void)&argc);
    ((void)&argv);

    time(&t);

#if 0
#elif defined(_MSC_VER) &&\
      _MSC_VER >= 1400

    if (0 != localtime_s(&tm, &t))
    {
        return EXIT_FAILURE;
    }
#else /* ? _MSC_VER */

    {
        struct tm const* const tm_p = localtime(&t);

        if (NULL == tm_p)
        {
            return EXIT_FAILURE;
        }

        tm = *tm_p;
    }
#endif /* _MSC_VER */

    n = strftime(&time_buf[0], sizeof(time_buf), "%c", &tm);

    if (0 == n)
    {
        return EXIT_FAILURE;
    }

    fprintf(stdout, "calling `diagnosticism_abort()` ...\n");

    diagnosticism_abortf(stderr, "ex-abort", "time to bug out: %s", time_buf);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
