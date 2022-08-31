#include "headers.h"
#include "cd.h"
#include "globals.h"

int firstcd = 0;

void cdcmd(char *argumentList[50], int len)
{
    char *chktilda = (char *)malloc(sizeof(char *) * 200);

    if (argumentList[1][0] == '~')
    {
        char *tempcurrentdirectory = malloc(sizeof(char *) * 200);
        getcwd(tempcurrentdirectory, 1000);

        strcpy(prevdir, tempcurrentdirectory);

        strcpy(chktilda, homedir);

        strcat(chktilda, argumentList[1] + 1);

        chdir(chktilda);

        return;
    }
    chktilda = argumentList[1];

    int flag2 = 0;

    if (argumentList[1][0] == '-')
    {
        strcpy(chktilda, prevdir);
        if (!firstcd)
        {
            printf("bash: cd: OLDPWD not set\n");
            return;
        }
        flag2 = 1;
    }

    char *tempcurrentdirectory = malloc(sizeof(char *) * 200);
    getcwd(tempcurrentdirectory, 1000);

    if (flag2)
    {
        printf("%s\n", chktilda);
    }

    int status;

    if (argumentList[1][0] == '.' && strlen(argumentList[1]) == 1)
    {
        status = chdir(chktilda);
        firstcd = 1;
        strcpy(prevdir, tempcurrentdirectory);
        // printf("mai yaha hoon\n");
    }
    else
    {
        status = chdir(chktilda);
        firstcd = 1;
        if (status != -1)
        {
            strcpy(prevdir, tempcurrentdirectory);
        }
        // printf("mai yaha hoon nahi\n");
    }

    // printf("now previous directory is %s\n", prevdir);
    // getcwd(currDir, 1000);

    if (status == -1)
        printf("No dir called : %s\n", argumentList[1]);
}