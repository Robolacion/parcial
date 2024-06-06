#pragma once
#include <stdint.h>
#include <stdio.h>

struct Reg1ster{
    uint16_t ID;
    uint16_t Lower_device_count;
    uint16_t Device_tipe;
    uint16_t info;
    uint16_t Upper_level_device_ID;
    uint16_t *List_of_devices;
};
struct Reg1ster *Get_network(FILE *Data,int *final_size);
void Show_IDs(struct Reg1ster *Data,int lenght);
void count_devices(struct Reg1ster *data,int data_size);
struct Reg1ster get_register(struct Reg1ster *List,uint16_t ID,int Lenght);
struct Reg1ster *resize(struct Reg1ster *vector,int old_size,int new_size);
uint16_t *int_resize(uint16_t *vector,int old_size,int new_size);
void print_network(FILE *out,struct Reg1ster *Data,int lenght);