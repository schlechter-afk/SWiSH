#include "headers.h"
#include "echo.h"
#include "globals.h"

void fgjobsfunc(char *argumentList[250], int len)
{
    if (len >= 3)
    {
        fprintf(stderr, "Invalid Number of Arguments\n");
        return;
    }
    int JobNo = atoi(argumentList[1]);

    // Invalid for job_no > no of bg proc.

    if (JobNo <= 0)
    {
        fprintf(stderr, "Invalid Job Number\n");
        return;
    }

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, arrbg[assoc[JobNo]]);
    kill(arrbg[assoc[JobNo]], SIGCONT);
    arrbg[assoc[JobNo]] = -1;
    int status;
    waitpid(-1, NULL, WUNTRACED);

    tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}