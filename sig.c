#include "headers.h"
#include "echo.h"
#include "globals.h"

void sigfunc(char *argumentList[250], int len)
{
    if (len != 3)
    {
        fprintf(stderr, "Invalid Number of Arguments\n");
        return;
    }
    int signal = atoi(argumentList[2]);
    int JobNo = atoi(argumentList[1]);

    // Invalid for job_no > no of bg proc.

    if (JobNo <= 0)
    {
        fprintf(stderr, "Invalid Job Number\n");
        return;
    }
    else if (signal <= 0)
    {
        fprintf(stderr, "Invalid Signal Number\n");
        return;
    }
    int retval = kill(arrbg[JobNo], signal);
}