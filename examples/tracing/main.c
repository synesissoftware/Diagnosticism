
#include <diagnosticism/tracing.h>

#include <clasp/clasp.h>

#include <stdio.h>
#include <stdlib.h>


void f(void)
{
    diagnosticism_trace(stderr, "");
}

void g(char const* argument)
{
    diagnosticism_trace(stderr, "argument=%s", argument);
}

int main(int argc, char* argv[])
{
    ((void)&argv);

    diagnosticism_trace(stderr, "argc=%d, argv=...", argc);

    f();

    g("the argument to g");

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

