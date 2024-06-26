#include "networklib.h"
/**
 * @brief La funcion debe leer el archivo y generar el vector de estructuras
 * 
 * por algún motivo la lectura el dato antes del for no funciona y crashea
 * @param Data puntero de archivo
 * @param final_size tamaño del vector, recuerde generar un vector de un elemento para almacenar el largo del vector dado que no se me ocurrio otra forma de devolver un 2do dato
 * @return struct Reg1ster* 
 */
struct Reg1ster *Get_network(FILE *Data,int *final_size)
{
    struct Reg1ster *Network_structure;
    int END,Network_structure_size=1,count=0,aux_cont=0;
    fseek(Data,0,SEEK_END);
    END=ftell(Data);
    uint16_t aux;
    fseek(Data,0,SEEK_SET);
    Network_structure=new struct Reg1ster[Network_structure_size];
   // printf("antes del while");
    while (ftell(Data)< END)
    {
        fread(&Network_structure[count].ID,sizeof(uint16_t),1,Data);
        fread(&Network_structure[count].Lower_device_count,sizeof(uint16_t),1,Data);
     //   printf("\n device count%u",Network_structure[count].Lower_device_count);   
        fread(&Network_structure[count].Device_tipe,sizeof(uint8_t),1,Data);
        fread(&Network_structure[count].info,sizeof(uint8_t),1,Data);
        fread(&Network_structure[count].Upper_level_device_ID,sizeof(uint16_t),1,Data);
        Network_structure[count].Device_tipe=(Network_structure[count].Device_tipe<<6)>>6;
        
        Network_structure[count].List_of_devices=new uint16_t [Network_structure[count].Lower_device_count];
       // printf("antes del for");
        for (aux_cont = 0; aux_cont < Network_structure[count].Lower_device_count; aux_cont++)
        {
            fread(&Network_structure[count].List_of_devices[aux_cont],sizeof(uint16_t),1,Data);   
       //     printf("algo");   
        }

        Network_structure=resize(Network_structure,Network_structure_size,Network_structure_size+1);
        Network_structure_size=Network_structure_size+1;
        count=count+1;
       // printf("%d",count);
    }
    *final_size=count-1;
    return Network_structure;
}
/**
 * @brief muestra el vector
 * 
 * @param Data 
 * @param lenght 
 */
void Show_IDs(struct Reg1ster *Data,int lenght)
{
    uint8_t i;
    printf("\n ----------------------- \n");
    for ( i = 0; i < lenght; i++)
    {
        
        printf("ID:%u\n",Data[i].ID);
        printf("Device tipe:");
        if (Data[i].Device_tipe==0)
        {
            printf("CPU");
        }
        if (Data[i].Device_tipe==1)
        {
            printf("Sensor");
        }
        if (Data[i].Device_tipe==2)
        {
            printf("Actuator");
        }
        if (Data[i].Device_tipe==3)
        {
            printf("Concentrator");
        }
        if (Data[i].Upper_level_device_ID<65535)
        printf("\n Upper level device ID:%u\n",Data[i].Upper_level_device_ID);
        else
        printf("\n Upper level device ID:None \n");
        printf("Lower device count:%u\n",Data[i].Lower_device_count);
        printf("\n ----------------------- \n");
    }
    
}

/**
 * @brief cuenta los dispositivos conectados a la red
 * 
 * @param data puntero vector register
 * @param data_size largo del vector anterior
 * @return int 
 */
int count_devices(struct Reg1ster *data,int data_size)
{
    uint16_t suma=0;
    for (size_t i = 0; i < data_size; i++)
    {
            if(data[i].Device_tipe==0 ||data[i].Device_tipe==3)
                suma=suma+data[i].Lower_device_count;
            if(data[i].Upper_level_device_ID==65535)
            suma=suma+1;
       
    }
     return suma;
}    
/**
 * @brief compara ID y devuelve el elemento correspondiente
 * @param List vector de estructura Reg1ster
 * @param ID ID del sipositivo que se busca
 * @param Lenght Numero de elementos del vector
 */

 struct Reg1ster get_register(struct Reg1ster *List,uint16_t ID,int Lenght)
{
    Reg1ster result; 
    int flag=0;
    for (size_t i = 0; i < Lenght; i++)
    {
        if(List[i].ID==ID){
        flag=i;
        result=List[flag];
        }

    }
    

    return result;
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
    delete[]vector;
    return v;
}
uint16_t *int_resize(uint16_t *vector,int old_size,int new_size)
{
     
    uint16_t *v, i;
        v=new uint16_t[new_size];
        for (i = 0; i < old_size; i++)
        {
            v[i]=vector[i];
        }
    delete[]vector;
    return v;
}

void print_network(FILE *out,struct Reg1ster *Data,int lenght){
     uint8_t i;
    printf("\n ----------------------- \n");
    for ( i = 0; i < lenght; i++)
    {
        
        fprintf(out,"ID:%u\n",Data[i].ID);
        fprintf(out,"Device tipe:");
        if (Data[i].Device_tipe==0)
        {
            fprintf(out,"CPU");
        }
        if (Data[i].Device_tipe==1)
        {
            fprintf(out,"Sensor");
        }
        if (Data[i].Device_tipe==2)
        {
            fprintf(out,"Actuator");
        }
        if (Data[i].Device_tipe==3)
        {
            fprintf(out,"Concentrator");
        }
        if (Data[i].Upper_level_device_ID<65535)
        fprintf(out,"\n Upper level device ID:%u\n",Data[i].Upper_level_device_ID);
        else
        fprintf(out,"\n Upper level device ID:None \n");
        fprintf(out,"Lower device count:%u\n",Data[i].Lower_device_count);
        fprintf(out,"\n ----------------------- \n");
    }

}