/* Simple list insert
*/

#include "p2.h"

int main()
{
    int element = 255;
    unsigned int key = 127;
    list_t lst;
    List_Init(&lst);
    List_Insert(&lst, (void*)&element, key);
    void *val = List_Lookup(&lst, key);
    if (val)
	return 0;
    else
	return -1;
}

