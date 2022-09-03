#include "headers.h"

int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

char pathdiscover[200];
int length;

void discoverycmd(char *path)
{
    struct dirent **list = NULL;

    int count = scandir(path, &list, NULL, alphasort);
    if (count < 0)
    {
        return;
    }
    for (int i = 0; i < count; i++)
    {
        char *concat1 = malloc(sizeof(char) * 200);
        strcpy(concat1, path);

        char *toconcat21 = malloc(sizeof(char) * 200);
        strcpy(toconcat21, "/");
        strcat(concat1, toconcat21);

        char *toconcat1 = malloc(sizeof(char) * 200);
        strcpy(toconcat1, list[i]->d_name);

        strcat(concat1, toconcat1);

        if (list[i]->d_name[0] != '.')
        {
            if (!isFile(concat1))
            {
                printf(".%s\n", concat1 + length);
            }
        }

        if (isFile(concat1) && list[i]->d_name[0] != '.')
        {
            printf(".%s\n", concat1 + length);
            discoverycmd(concat1);
        }
    }
}

void executediscovery(char *path, char *home, char *argumentList[50], int len)
{
    strcpy(pathdiscover, home);
    length = strlen(pathdiscover);
    
    discoverycmd(path);
}