
#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef STRING_H
#include <string.h>
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef BAL_TREE_H_INCLUDED
#define BAL_TREE_H_INCLUDED

#ifndef STDIO_H
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LOG_2 1.44269504088896340736



//*** node *****//
typedef struct node
{

    char word[32];

    struct node *left;
    struct node *right;
    struct node *parent;
    int balance;
} node;





char *str_rev(char *str)
{
    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}



//**** search ******//

////////////////////////////////////////////////////////////////////////
////////////////search///////////////////////////////////
////////////////////////////////////////////////////////////////////////
node* search(node *ptr, char* data)
{
    if(ptr!=NULL)
    {
        //if the string given is less than the one in the node
        if(strcmp(data, ptr->word) < 0){
        ptr = search(ptr -> left,data);
        //puts("data is in left");

        }else if(strcmp(data, ptr->word) > 0){

			ptr = search(ptr-> right, data);
            //puts("data is in right");


			}


    }

    return(ptr);
}
////////////////////////////////////////////////////////////////////////
////////////////insert/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


node *insert (char* data, node *ptr, int *flag)
{

    node *ptr_1;
    node *ptr_2;


    if(ptr==NULL)
    {

        ptr = (node *) malloc(sizeof(node));

        strcpy(ptr->word, data);
        *flag = 1;
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->parent = NULL;
        ptr->balance = 0;

        return (ptr);
    }


    if(strcmp(data, ptr->word) < 0)
    {

        //ptr->left->parent = ptr;
        ptr->left = insert(data, ptr->left, flag);

        if(*flag==1)
        {
            switch(ptr->balance)
            {

			// already balanced
            case 0:
                ptr->balance = 1;
                break;

			// the right branch is heavy
            case -1:
                ptr->balance = 0;
                *flag = 0;
                break;

			// the left branch is heavy
            case 1:
                ptr_1 = ptr->left;
                if(ptr_1-> balance == 1)
                {


                    ptr->left = ptr_1->right;

                    ptr_1->right = ptr;
                    ptr->balance = 0;
                    ptr_1->balance=0;
                    ptr = ptr_1;
                }

                else
                {

                    ptr_2 = ptr_1->right;
                    ptr_1->right = ptr_2->left;
                    ptr_2->left = ptr_1;
                    ptr->left = ptr_2->right;
                    ptr_2->right = ptr;

                    if(ptr_2-> balance == 1 )
                        ptr->balance = -1;
                    else
                        ptr->balance = 0;

                    if(ptr_2->balance == -1)
                        ptr_1->balance = 1;
                    else
                        ptr_1->balance = 0;

                    ptr_2->balance=0;
                    ptr = ptr_2;

                }
                *flag = 0;

            }//end of switch

        } //end of inner if

    } //end of outer if


    if(strcmp(data, ptr ->word) > 0)
    {
		//ptr->right->parent = ptr;
        ptr-> right = insert(data, ptr->right, flag);

        if(*flag==1)
        {
            switch(ptr->balance)
            {

			// already balanced
            case 0:
                ptr->balance = -1;
                break;
			// the left branch is heavy
            case 1:

                ptr->balance = 0;
                *flag = 0;
                break;

			// the right branch is heavy
            case -1:
                ptr_1 = ptr->right;

                if(ptr_1->balance == -1)
                {


                    ptr->right= ptr_1->left;
                    ptr_1->left = ptr;
                    ptr->balance = 0;
                    ptr_1->balance=0;
                    ptr = ptr_1;

                }

                else
                {

                    ptr_2 = ptr_1-> left;
                    ptr_1->left = ptr_2->right;
                    ptr_2->right = ptr_1;
                    ptr->right = ptr_2->left;
                    ptr_2->left = ptr;

                    if(ptr_2-> balance == -1)
                        ptr->balance = 1;
                    else
                        ptr->balance = 0;

                    if(ptr_2->balance == 1)
                        ptr_1->balance = -1;
                    else
                        ptr_1->balance = 0;
                    ptr_2->balance=0;
                    ptr = ptr_2;
                }

                *flag = 0;
            }


        }// end of if

    }
    return(ptr);
}


////////////////////////////////////////////////////////////////////////
/////////////Calculating Height/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

/* calc #ofNodes >> height = ceil(log2(n))*/


void get_height(int lim){

	printf("Height of the tree is %0.2lf",ceil(log(lim) * LOG_2));
	 //return ceil(log(lim) * LOG_2);

	}

int height_left(node* ptr){

if(ptr !=NULL)
return 1+ height_left(ptr->left);

return 0;
}


int height_right(node* ptr){


if(ptr !=NULL)
return 1+ height_right(ptr->right);

return 0;
}


int height(node* ptr){


int left_branch = height_left(ptr);
int right_branch = height_right(ptr);
int value;
value = left_branch > right_branch ? left_branch : right_branch;

return value;
return left_branch;


}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////



#endif // BAL_TREE_H_INCLUDED
