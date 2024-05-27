#pragma once
#include <stdint.h>
#include <stdio.h>

struct Reg1ster{
    uint16_t ID;
    uint16_t Lower_device_count;
    uint8_t Device_tipe;
    uint8_t info;
    uint16_t Upper_level_device_ID;
    uint16_t *List_of_devices;
};
struct Reg1ster *Get_network(FILE *Data,int *final_size);
void Show_IDs(struct Reg1ster *Data,int lenght);
int Show_devices(struct Reg1ster data);
struct Reg1ster get_register(uint16_t ID);
struct Reg1ster *resize(struct Reg1ster *vector,int old_size,int new_size);