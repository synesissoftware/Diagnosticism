
#include <diagnosticism/abort.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char* argv[])
{
    time_t              t;
    struct tm const*    tm;
    char const*         asc;
    size_t              n;

    ((void)&argc);
    ((void)&argv);

    time(&t);
    tm = localtime(&t);
    asc = asctime(tm);
    n = strlen(asc);

    if ('\n' == asc[n - 1])
    {
        --n;
    }

    fprintf(stdout, "calling `diagnosticism_abort()` ...\n");

    diagnosticism_abortf(stderr, "ex-abort", "time to bug out: %.*s", (int)n, asc);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

