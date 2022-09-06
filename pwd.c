#include "headers.h"
#include "pwd.h"
#include "globals.h"

void pwdcmd()
{
    char output[300];
    getcwd(output, sizeof(output));
    printf("%s\n", output);
}