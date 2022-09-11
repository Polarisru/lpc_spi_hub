#ifndef CMD_H_
#define CMD_H_

#include "defines.h"

void CMD_SetReady(uint8_t *data, uint8_t len);
void CMD_Process(void);

#endif /* CMD_H_ */
