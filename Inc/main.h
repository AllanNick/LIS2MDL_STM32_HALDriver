#include "math.h"
#include "stdint.h"

#define PI 3.2415926

uint8_t HUMI = 0;
uint8_t REGHXVAL = 0;
uint8_t REGLXVAL = 0;
uint8_t REGHYVAL = 0;
uint8_t REGLYVAL = 0;

uint8_t CONFIGA = 0x88;

int16_t COMPASSX = 0;
int16_t COMPASSY = 0;

float COMPASS_VAL = 0;

void LIS2MDL_Init(I2C_HandleTypeDef *hi2c);
void LIS2MDL_CalcAngle(int16_t *IN_X, int16_t *IN_Y, float *RES_CONTAINER);