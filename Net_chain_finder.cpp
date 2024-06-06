
#include "networklib.h"
int main(int argc, char const *argv[])
{
    FILE *Network_structure;
    int  Registry_size[1];
    uint16_t registry_size,*ID_buffer,count=0;
    Network_structure=fopen("C:\\Users\\alear\\OneDrive\\Escritorio\\Parcial Info II\\network_structure.dat","r");
    Reg1ster *Network, Target_Register;
    char Command='n' ;
    uint16_t Input;
    Network=Get_network(Network_structure,Registry_size);
    fclose(Network_structure);
    registry_size=Registry_size[0];
    //printf("%u",registry_size);
 
        printf("Introduzca el ID de su equipo\n");
        scanf("%u",&Input);
        Target_Register=get_register(Network,Input,registry_size);
        printf("ID:%u",Target_Register.ID);
        while (Target_Register.Upper_level_device_ID != 65535)
        {               
            printf(" --> ID:%u",Target_Register.Upper_level_device_ID);
            Target_Register=get_register(Network,Target_Register.Upper_level_device_ID,registry_size);     
        }
       

    
    return 0;
}
