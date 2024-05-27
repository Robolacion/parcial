#include "memoria_dinamica.h"
int *resize(int *vector,int old_size,int new_size)
{
    int *v,i;
    if(new_size>=old_size)
    {
        v=new int[new_size];
        for (i = 0; i < old_size; i++)
        {
            v[i]=vector[i];
        }
    }
    else
    {
        for (i = 0; i < new_size; i++)
        {
            v[i]=vector[i];
        }
    
    }
 delete[]vector;
    return v;
}
int *remove_item(int*vector,int vec_size,int item_pos)
{
    int i;
    for (i = item_pos; i < vec_size; i++)
    {
        if(i==item_pos)
        {
            vector[i]=0;
        }
        else
        {
            vector[i-1]=vector[i];
        }
      
    }
    vector=resize(vector,vec_size,vec_size-1);  
    
}
int*insert_item(int*vector,int vec_size,int insert_pos,int insert_value)
{
    int i,aux;
    vector=resize(vector,vec_size,vec_size+1);
    for ( i = insert_pos; i < vec_size+1; i++)
    {
        aux=vector[i];
        if(i==insert_pos)
             vector[i]=insert_value;
        if(i<vec_size+1)
        vector[i+1]=aux;
    }
    
}
int*concat(int *vector_a,int vector_a_size,int*vector_b,int vector_b_size){
    int *aux,i;
    aux=new int[vector_a_size+vector_b_size];
    for ( i = 0; i < vector_a_size+vector_b_size; i++)
    {
        if(i<vector_a_size) 
        aux[i]=vector_a[i];

        if (i>=vector_a_size)
        {
            aux[i]=vector_b[i-vector_a_size];
        }
        delete []vector_a;
        delete []vector_b;

        return aux;

    }   
}