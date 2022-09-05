#include "headers.h"

char *cmpfile;
char *cmpdirec;

int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int tk1 = 0;
int tk2 = 0;

char pathdiscover[200];
int length;

void discover(char *path, int flag1, int flag2, int flag3)
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
        // printf("---> %s\n", concat1);

        if (list[i]->d_name[0] != '.')
        {
            if (!isFile(concat1))
            {
                if (flag1 == 0 && flag2 == 0 && flag3 == 1)
                {
                    if (strcmp(cmpfile, list[i]->d_name) == 0)
                    {
                        printf("Found : %s\n", concat1 + length);
                        tk1 = 1;
                        return;
                    }
                }
                else if (flag1 == 0 && flag2 == 0 && flag3 == 0)
                {
                    printf(".%s\n", concat1 + length);
                }
                else if (flag1 == 0 && flag2 == 1 && flag3 == 0)
                {
                    printf(".%s\n", concat1 + length);
                }
            }
        }

        if (isFile(concat1) && list[i]->d_name[0] != '.')
        {
            if (flag1 == 0 && flag2 == 0 && flag3 == 0)
            {
                printf(".%s\n", concat1 + length);
            }
            else if (flag1 == 0 && flag2 == 1 && flag3 == 1)
            {
                printf(".%s\n", concat1 + length);
            }
            discover(concat1, flag1, flag2, flag3);
        }
    }
}

void executediscover(char *path, char *home, char *argumentList[50], int len)
{
    strcpy(pathdiscover, home);
    length = strlen(pathdiscover);

    int dotflag = 0;
    int dotdotflag = 0;
    int tildaflag = 0;
    int direcflag = 0;
    int fileflag = 0;
    int dminflag = 0;
    int fminflag = 0;
    // printf("%d\n", len);
    if (len > 1)
    {
        for (int i = 1; i < len; i++)
        {
            if (strcmp(argumentList[i], ".") == 0)
            {
                dotflag = 1;
            }
            else if (strcmp(argumentList[i], "..") == 0)
            {
                dotdotflag = 1;
            }
            else if (strcmp(argumentList[i], "~") == 0)
            {
                tildaflag = 1;
            }
            else if (strcmp(argumentList[i], "-d") == 0)
            {
                dminflag = 1;
            }
            else if (strcmp(argumentList[i], "-f") == 0)
            {
                fminflag = 1;
            }
            else
            {
                // if (direcflag == 1 || i == (len - 1))
                // {
                //     fileflag = 1;
                //     cmpfile = malloc(sizeof(char) * 200);
                //     strcpy(cmpfile, argumentList[i]);
                // }
                // if (i != len - 1)
                // {
                //     direcflag = 1;
                //     cmpdirec = malloc(sizeof(char) * 200);
                //     strcpy(cmpdirec, argumentList[i]);
                // }
                if (argumentList[i][0] == '"')
                {
                    fileflag = 1;
                    cmpfile = malloc(sizeof(char) * 200);
                    char *temp = malloc(sizeof(char) * 250);
                    // strcpy(temp, argumentList[i]);
                    int j = 1;
                    for (j = 1; j < strlen(argumentList[i]) - 1; j++)
                    {
                        temp[j - 1] = argumentList[i][j];
                    }
                    temp[j - 1] = '\0';
                    strcpy(cmpfile, temp);
                }
                else
                {
                    direcflag = 1;
                    cmpdirec = malloc(sizeof(char) * 200);
                    strcpy(cmpdirec, argumentList[i]);
                }
            }
        }
    }

    printf("dflag is %d\n", dminflag);
    printf("fflag is %d\n", fminflag);
    printf("dotflag is %d\n", dotflag);
    printf("dotdotflag is %d\n", dotdotflag);
    printf("tildaflag is %d\n", tildaflag);
    printf("direcnameflag is %d\n", direcflag);
    printf("filenameflag is %d\n", fileflag);

    if (dminflag == 0 && fminflag == 0 && dotflag == 0 && dotdotflag == 0 && tildaflag == 0 && direcflag == 0 && fileflag == 0)
    {
        discover(path, 0, 0, 0);
    }

    if (dotflag == 1)
    {
        if (dminflag == 1 && direcflag == 0 && fminflag == 0)
        {
            discover(path, 0, 1, 1); // 0,1,0
            return;
        }
        else if (fminflag == 1 && direcflag == 0 && fileflag == 0 && dminflag == 0)
        {
            discover(path, 0, 1, 0); // 0,1,1
            return;
        }
        else if (direcflag == 0 && fileflag == 1)
        {
            char *currpath = malloc(sizeof(char) * 500);
            getcwd(currpath, 500);
            strcpy(path, currpath);
            length = strlen(path);
            discover(path, 0, 0, 1); // 0,0,1
            if (!tk1)
            {
                printf("Could not find the file\n");
            }
            return;
        }
        else
        {
            discover(path, 0, 0, 0);
            return;
        }
    }
    if (dotdotflag == 1)
    {
        if (dminflag == 1 && direcflag == 0 && fminflag == 0)
        {
            chdir(path);
            char *currpath = malloc(sizeof(char) * 500);
            getcwd(currpath, 500);
            chdir("..");
            char *temp = malloc(sizeof(char) * 500);
            getcwd(temp, 500);
            strcpy(path, temp);
            length = strlen(path);
            discover(path, 0, 1, 1); // 0,1,0
            chdir(currpath);
            return;
        }
        else if (fminflag == 1 && direcflag == 0 && fileflag == 0 && dminflag == 0)
        {
            chdir(path);
            char *currpath = malloc(sizeof(char) * 500);
            getcwd(currpath, 500);
            chdir("..");
            char *temp = malloc(sizeof(char) * 500);
            getcwd(temp, 500);
            strcpy(path, temp);
            length = strlen(path);
            discover(path, 0, 1, 0); // 0,1,1
            chdir(currpath);
            return;
        }
        else if (direcflag == 0 && fileflag == 1)
        {
            chdir(path);
            char *currpath = malloc(sizeof(char) * 500);
            getcwd(currpath, 500);
            chdir("..");
            char *temp = malloc(sizeof(char) * 500);
            getcwd(temp, 500);
            strcpy(path, temp);
            length = strlen(path);
            discover(path, 0, 0, 1); // 0,0,1
            if (!tk1)
            {
                printf("Could not find the file\n");
            }
            chdir(currpath);
            return;
        }
        else
        {
            chdir(path);
            char *currpath = malloc(sizeof(char) * 500);
            getcwd(currpath, 500);
            chdir("..");
            char *temp = malloc(sizeof(char) * 500);
            getcwd(temp, 500);
            strcpy(path, temp);
            length = strlen(path);
            discover(path, 0, 0, 0);
            chdir(currpath);
            return;
        }
    }
    if (tildaflag == 1)
    {
        if (dminflag == 1 && direcflag == 0)
        {
            strcpy(path, homedir);
            length = strlen(path);
            discover(path, 0, 1, 1); // 0,1,0
        }
        else if (fminflag == 1 && direcflag == 0)
        {
            strcpy(path, homedir);
            length = strlen(path);
            discover(path, 0, 1, 0); // 0,1,1
        }
        else if (direcflag == 0 && fileflag == 1)
        {
            strcpy(path, homedir);
            length = strlen(path);
            discover(path, 0, 0, 1); // 0,0,1
            if (!tk1)
            {
                printf("Could not find the file\n");
            }
        }
        else
        {
            strcpy(path, homedir);
            length = strlen(path);
            discover(path, 0, 0, 0);
        }
    }
    if (direcflag == 1)
    {
        char *dirtemp = malloc(sizeof(char) * 200);
        strcpy(dirtemp, path);
        strcat(dirtemp, cmpdirec + 1);
        length = strlen(dirtemp);

        if (argumentList[1][0] == '~')
        {
            strcpy(dirtemp, homedir);
            strcat(dirtemp, cmpdirec + 1);
            length = strlen(dirtemp);
            discover(dirtemp, 0, 0, 0);
        }
        else if (argumentList[1][0] == '/')
        {
            length = strlen(argumentList[1]);
            strcpy(dirtemp, argumentList[1]);
        }
        else if (argumentList[1][0] != '.')
        {
            length = strlen(path);
            strcpy(dirtemp, path);
            strcat(dirtemp, "/");
            strcat(dirtemp, argumentList[1]);
            // printf("I AM HERE %s\n", dirtemp);
        }
        if (fileflag == 0)
        {
            if ((dminflag == 1 && fminflag == 1) || (dminflag == 0 && fminflag == 0))
            {
                discover(dirtemp, 0, 0, 0);
            }
            else if (dminflag == 1 && fminflag == 0)
            {
                discover(dirtemp, 0, 1, 1);
            }
            else if (dminflag == 0 && fminflag == 1)
            {
                discover(dirtemp, 0, 1, 0);
            }
        }
        else
        {
            if ((dminflag == 0 && fminflag == 0))
            {
                length = strlen(path);
                discover(dirtemp, 0, 0, 1); // 0,0,1
                if (!tk1)
                {
                    printf("Could not find the file\n");
                }
            }
            else if (dminflag == 1 && fminflag == 0)
            {
                printf("./n");
            }
            else if (dminflag == 0 && fminflag == 1)
            {
                discover(dirtemp, 0, 0, 1); // 0,0,1
                if (!tk1)
                {
                    printf("Could not find the file\n");
                }
            }
        }
    }
    else if (direcflag == 0 && dminflag == 1 && fminflag == 1 && fileflag == 0)
    {
        discover(path, 0, 0, 0);
        return;
    }
    else if (direcflag == 0 && dminflag == 1 && fminflag == 0 && fileflag == 0)
    {
        discover(path, 0, 1, 1);
        return;
    }
    else if (direcflag == 0 && dminflag == 0 && fminflag == 1 && fileflag == 0)
    {
        discover(path, 0, 1, 0);
        return;
    }
    else if (direcflag == 0 && dminflag == 1 && fminflag == 1 && fileflag == 1)
    {
        discover(path, 0, 0, 1);
        return;
    }
    else if (direcflag == 0 && dminflag == 1 && fminflag == 0 && fileflag == 1)
    {
        discover(path, 0, 0, 1);
        return;
    }
    else if (direcflag == 0 && dminflag == 0 && fminflag == 1 && fileflag == 1)
    {
        discover(path, 0, 0, 1);
        return;
    }
    else if (direcflag == 0 && dminflag == 0 && fminflag == 0 && fileflag == 1)
    {
        discover(path, 0, 0, 1);
        return;
    }

    tk1 = 0;
    // discover(path);
}