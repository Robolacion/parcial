#include <stdio.h>
#include <stdlib.h>
#include "networklib.h"

int main(int argc, char const *argv[])
{
    FILE *Network_structure;
    int Registry_size[1];
    Network_structure=fopen("C:\\Users\\alear\\OneDrive\\Escritorio\\Parcial Info II\\network_structure.dat","r");
    Reg1ster *Network;
    if (Network_structure==NULL)
    {
        printf("Apertura fallida");
    }
    else
    {
        printf("Apertura exitosa");
    }
    Network=Get_network(Network_structure,Registry_size);
    printf("tamaño vector %d",Registry_size);
    Show_IDs(Network);

    return 0;
}
