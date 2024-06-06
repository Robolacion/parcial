#include <stdio.h>
#include <stdlib.h>
#include "networklib2.h"

int main(int argc, char const *argv[])
{
    FILE *Network_structure,*data_out;
    int Registry_size[1],i;
    Network_structure=fopen("C:\\Users\\alear\\OneDrive\\Escritorio\\Parcial Info II\\Recuperatorio\\network_structure.dat","r");
    Reg1ster *Network;
    if (Network_structure==NULL)
    {
        printf("Apertura fallida \n");
    }
    else
    {
        printf("Apertura exitosa \n");
    }
    Network=Get_network(Network_structure,Registry_size);
    fclose(Network_structure);
    data_out=fopen("C:\\Users\\alear\\OneDrive\\Escritorio\\Parcial Info II\\Recuperatorio\\network_structure_print.txt","rt+");
    print_network(data_out,Network,Registry_size[0]);
    printf("Numero de equipos detectados %d",Registry_size[0]);
    Show_IDs(Network,Registry_size[0]);
    count_devices(Network,Registry_size[0]);
    scanf("&d",&Registry_size[0]);

    return 0;
}
