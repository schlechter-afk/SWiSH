#ifndef __fg_H
#define __fg_H

#include "headers.h"

int fgproctime(char *list[250], int len);
int fgproc(char *argumentList[250], int len);
int fgbgcall(char *line[50], int len);
int bgproc(char *argumentList[250], int len);

#endif