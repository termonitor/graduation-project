#ifndef __M_ACTION_H__
#define __M_ACTION_H__

#include <stdio.h>
#include <stdlib.h>
#include "MOled.h"
#include "MGpio.h"
#include "MFile.h"
#include "MPeripheral.h"

int gameLdStatus;

void action(int *signal, int config);
void initAction();

#endif