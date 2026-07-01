
#include <diagnosticism/tracing.h>

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

    //! [tracing_call]
    diagnosticism_trace(stderr, "argc=%d, argv=...", argc);
    //! [tracing_call]

    f();

    g("the argument to g");

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

