#ifndef __discovery_H
#define __discovery_H

#include "headers.h"

void discover(char *path, int flag1, int flag2, int flag3);
void executediscover(char *path, char *home, char *argumentList[50], int len);
int default_filter2(const struct dirent *ent);

#endif