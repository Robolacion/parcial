#pragma once
int*resize(int *vector,int new_size,int old_size);
int*remove_item(int*vector,int vec_size,int item_pos);
int*insert_item(int*vector,int vec_size,int insert_pos,int insert_value);
int*concat(int *vector_a,int vector_a_size,int*vector_b,int vector_b_size);