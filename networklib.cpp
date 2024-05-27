#include "networklib.h"

struct Reg1ster *Get_network(FILE *Data,int *final_size)
{
    struct Reg1ster *Network_structure;
    int END,Network_structure_size=1,count=0,aux_cont;
    fseek(Data,0,SEEK_END);
    END=ftell(Data);
    fseek(Data,0,SEEK_SET);
    Network_structure=new struct Reg1ster[Network_structure_size];
    while (ftell(Data)< END)
    {
        fread(&Network_structure[count].ID,sizeof(Network_structure->ID),1,Data);
        fread(&Network_structure[count].Lower_device_count,sizeof(Network_structure->Lower_device_count),1,Data);   
        fread(&Network_structure[count].Device_tipe,sizeof(Network_structure->Device_tipe),1,Data);
        fread(&Network_structure[count].info,sizeof(Network_structure->info),1,Data);
        fread(&Network_structure[count].Upper_level_device_ID,sizeof(Network_structure->Upper_level_device_ID),1,Data);

        for (aux_cont = 0; aux_cont < Network_structure[count].Lower_device_count; aux_cont++)
        {
            Network_structure[count].List_of_devices=new uint16_t[Network_structure[count].Lower_device_count]; 
            fread(&Network_structure[count].List_of_devices,sizeof(Network_structure->List_of_devices),Network_structure[count].Lower_device_count,Data);     
        }
        Network_structure=resize(Network_structure,Network_structure_size+1,Network_structure_size);
        Network_structure_size=Network_structure_size+1;
        count=count+1;
    }
    *final_size=count;
}
void Show_IDs(struct Reg1ster *Data,int lenght)
{
    uint8_t i;
    for ( i = 0; i < lenght; i++)
    {
        printf("\n ----------------------- \n");
        printf("ID:%u\n",Data[i].ID);
        // añadir condicional printf("%u",Data[i].Device_tipe);
        printf("Upper level device ID:%u\n",Data[i].Upper_level_device_ID);
        printf("Lower device count:%u\n",Data[i].Lower_device_count);
        printf("\n ----------------------- \n");
    }
    
}
int Show_devices(struct Reg1ster data)
{

}
 struct Reg1ster get_register(uint16_t ID)
{

}

struct Reg1ster *resize(struct Reg1ster *vector,int old_size,int new_size)
{
    struct Reg1ster *v;
    int i;
        v=new struct Reg1ster[new_size];
        for (i = 0; i < old_size; i++)
        {
            v[i]=vector[i];
        }
    return v;
    delete[]vector;
}
