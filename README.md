# LIS2MDL_STM32_HALDriver

 2Demension LIS2MDL Driver for Compass application

Environment: STM32 Cube, CMake, Arm-none-eabi-gcc, GDB

To Use this Driver, copy files LIS2MDL_Driver.c and LIS2MDL_Driver.h to ./Src and ./Inc which in your project folder.

ProjectFolder
|__CMakeLists.txt
|__Src
|   |__main.c
|   |__LIS2MDL_Driver.c
|   |__ ...
|__Inc
    |__LIS2MDL_Driver.h
    |__ ...
!Remind to modify CMakeLists.txt if you arn't placing the driver in a path excepted ./Inc and ./Src
