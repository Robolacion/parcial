#include "networklib2.h"
/**
 * @brief La funcion debe lee el archivo y genera el vector de estructuras de tipo Reg1stry
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
    uint16_t aux,NH,NL;
    fseek(Data,0,SEEK_SET);
    Network_structure=new struct Reg1ster[Network_structure_size];
   // printf("antes del while");
    while (ftell(Data)< END)
    {
        fread(&Network_structure[count].ID,sizeof(uint16_t),1,Data);
        Network_structure[count].Lower_device_count=Network_structure[count].ID&0x3f;
        Network_structure[count].ID=Network_structure[count].ID>>6;
   //printf("a");
        fread(&Network_structure[count].Device_tipe,sizeof(uint16_t),1,Data);
        Network_structure[count].info=((Network_structure[count].Device_tipe<<4)>>8);
        NH=(Network_structure[count].Device_tipe&0x1000)>>12;
        NL=(Network_structure[count].Device_tipe&0x0008)>>3;
        Network_structure[count].Device_tipe=(2*NH)+NL;
    //printf("b");   
        fread(&Network_structure[count].Upper_level_device_ID,sizeof(uint16_t),1,Data);
        Network_structure[count].Upper_level_device_ID=(Network_structure[count].Upper_level_device_ID<<3)>>6;

        Network_structure[count].List_of_devices=new uint16_t [Network_structure[count].Lower_device_count];
      //  printf("antes del for");
        for (aux_cont = 0; aux_cont < Network_structure[count].Lower_device_count; aux_cont++)
        {
            fread(&Network_structure[count].List_of_devices[aux_cont],sizeof(uint16_t),1,Data);
               Network_structure[count].List_of_devices[aux_cont]=(Network_structure[count].List_of_devices[aux_cont]>>6);
         //   printf("-%u",aux_cont);   
        }

        Network_structure=resize(Network_structure,Network_structure_size,Network_structure_size+1);
        Network_structure_size=Network_structure_size+1;
        count=count+1;
      //  printf("%d",count);
    }
    *final_size=count-1;
    return Network_structure;
}
/**
 * @brief muestra el vector, no muestra las id de los dispositivos del nivel inferior
 * 
 * @param Data puntero del vector de Reg1stros
 * @param lenght numero de elementos del vector Reg1stros
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
        if (Data[i].Upper_level_device_ID<1023)
        printf("\n Upper level device ID:%u\n",Data[i].Upper_level_device_ID);
        else
        printf("\n Upper level device ID:None \n");
        printf("Lower device count:%u\n",Data[i].Lower_device_count);
        printf("\n ----------------------- \n");
    }
    
}

/**
 * @brief muestra cuantos dispositivos de cada tipo hay en la red
 * 
 * @param Data puntero vector register
 * @param data_size largo del vector
 */
void count_devices(struct Reg1ster *Data,int data_size)
{
    uint16_t CPU=0,CON=0,ACT=0,SEN=0,i;
    printf("\n ----------------------- \n La red conta de: %d dispositivos ennumerados por tipo a continuacion\n");
    for ( i = 0; i < data_size; i++)
    {   
        
        if (Data[i].Device_tipe==0)
        {
            //("CPU");
            CPU++;
        }
        if (Data[i].Device_tipe==1)
        {
            //("Sensor");
            SEN++;
        }
        if (Data[i].Device_tipe==2)
        {
            //("Actuator");
            ACT++;

        }
        if (Data[i].Device_tipe==3)
        {
            //("Concentrator");
            CON++;
        }
  
    }
        printf("CPU:%u \n",CPU);
        printf("Temp concentrator: %u \n",CON);
        printf("Temp Sensor: %u \n",SEN);
        printf("Valve: %u \n",ACT);

        printf("\n ----------------------- \n");  
     
}    
/**
 * @brief compara ID y devuelve el elemento correspondiente a dicha ID
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
/**
 * @brief Aumenta el tamaño de un vector de estructuras de tipo reg1stry
 * 
 * @param vector puntero del vector de reg1stros
 * @param old_size tamaño actual del vector 
 * @param new_size tamaño nuevo del vector
 * @return struct Reg1ster* 
 */
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
/**
 * @brief Aumenta el tamaño de un vector de tipo unsigned int 16
 * 
 * @param vector puntero del vector
 * @param old_size tamaño actual del vector
 * @param new_size tamaño nuevo del vector
 * @return uint16_t* 
 */
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

/**
 * @brief 
 * 
 * @param out Puntero asociado al archivo que se desea escribir
 * @param Data Puntero del vector de estructuras de tipo Reg1stry
 * @param lenght Numero de elementos del vector de tipo Reg1stry
 */
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
        if (Data[i].Upper_level_device_ID<1023)
        fprintf(out,"\n Upper level device ID:%u\n",Data[i].Upper_level_device_ID);
        else
        fprintf(out,"\n Upper level device ID:None \n");
        fprintf(out,"Lower device count:%u\n",Data[i].Lower_device_count);
        fprintf(out,"\n ----------------------- \n");
    }

}