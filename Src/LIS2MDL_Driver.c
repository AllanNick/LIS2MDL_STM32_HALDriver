#include "stdint.h"
#include "LIS2MDL_Driver.h"

#define PI 3.2415926

/*
LIS2MDL_STM32_HALDriver
 Allan_Nick 2024
*/

//HEADERS:
/*
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
void LIS2MDL_DataUpdate(I2C_HandleTypeDef *hi2c, uint8_t *REGHXVAL, uint8_t *REGHYVAL, uint8_t *REGLXVAL, uint8_t *REGLYVAL);
void LIS2MDL_CalcAngle(int16_t *IN_X, int16_t *IN_Y, float *RES_CONTAINER);
*/

void LIS2MDL_Init(I2C_HandleTypeDef *hi2c){
  HAL_I2C_Mem_Read(hi2c, 0x3C, 0x4F, I2C_MEMADD_SIZE_8BIT, &HUMI, 1, 0xFF);
  //VALUE IN WHO_AM_I REGISTER WAS 64 [DEC]
  if(HUMI == 64){
    //EXECUTE CONFIGURATION WHILE DEVICEID MATCHED
    HAL_I2C_Mem_Write(hi2c, 0x3C, 0x60, I2C_MEMADD_SIZE_8BIT, &CONFIGA, 1, 0xFF);
    //GET TARGET VALUES IN DEVICE REGESTER AS INITIALIZE VALUES
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x69, I2C_MEMADD_SIZE_8BIT, &REGHXVAL, 1, 0xFF);
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x68, I2C_MEMADD_SIZE_8BIT, &REGLXVAL, 1, 0xFF);
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x6A, I2C_MEMADD_SIZE_8BIT, &REGHYVAL, 1, 0xFF);
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x6B, I2C_MEMADD_SIZE_8BIT, &REGLYVAL, 1, 0xFF);
  }
}

/*Uses Pointer to optimize memory usage 
and improving execution performance

All address to save data can be re-modify

For performance issue, suggest to run code on 
F4 or other MCU Series which contains FPU with higher performence
*/
void LIS2MDL_CalcAngle(int16_t *IN_X, int16_t *IN_Y, float *RES_CONTAINER){
  float CalcIN_X = (*IN_X+300) *0.0125663704;
  float CalcIN_Y = (*IN_Y+400) *0.0125663704;
  float theta_radius = atan2(CalcIN_Y, CalcIN_X) *180;

  float theta_degrees = (theta_radius / PI)*2.2;

  //*RES_CONTAINER = fmod((theta_degrees + 360), 360);
  *RES_CONTAINER = fmod(theta_degrees+360, 360); 
}
/*Parameters can also exchange to an uint8_t array*/
void LIS2MDL_DataUpdate(I2C_HandleTypeDef *hi2c, uint8_t *REGHXVAL, uint8_t *REGHYVAL, uint8_t *REGLXVAL, uint8_t *REGLYVAL){
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x69, I2C_MEMADD_SIZE_8BIT, REGHXVAL, 1, 0xFF);
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x68, I2C_MEMADD_SIZE_8BIT, REGLXVAL, 1, 0xFF);
    
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x6B, I2C_MEMADD_SIZE_8BIT, REGHYVAL, 1, 0xFF);
    HAL_I2C_Mem_Read(hi2c, 0x3C, 0x6A, I2C_MEMADD_SIZE_8BIT, REGLYVAL, 1, 0xFF);
  
    COMPASSX = *REGHXVAL << 8 | *REGLXVAL;
    COMPASSY = *REGHYVAL << 8 | *REGLYVAL;
}

/*Example application:*/
int main(){
    LIS2MDL_Init(&hi2c2);
    while(1){
        HAL_Delay(20);
        /*Fetch data from Regsiter in sensor*/
        LIS2MDL_DataUpdate(&hi2c2, &REGHXVAL, &REGHYVAL, &REGLXVAL, &REGLYVAL);
        /*Execute Angle calculation*/
        LIS2MDL_CalcAngle(&REGHXVAL, &REGHYVAL, &RES_CONTAINERZ);
    }
}