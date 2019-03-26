#include "bal_tree.h"
#include <stdio.h>


//just in linux //
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


/* Hagar Osama */
// last changed Thu 19.26
typedef struct database{

	char word[32];

	} database;


	database db[4000];
	database st[256];
	database parents[11];


	int print_d =0;
	char add[32];

	int par_index=0;



int read_dictionary(char* filename);
int check_dup(char *word);
void null_it(void);
void show_found(void);
void check_my_sentence(node *ptr);
void subString(char* word , char* subWord);
void get_suc_and_pre(node *ptr , char *suc , char *pre , char *word);
void print_parent(char *suc , char *pre , char* token);
void toLowerCase(char*str);
void terminate_it(char* word);
int check_symbols(char* word);


int main(){


    int flag =0;

    //creating root node
	struct node *root = (struct node *)malloc(sizeof(struct node));
    root = NULL;





	int lim = read_dictionary("English Dictionary.txt");

	// inserting words into tree
	printf(CYN"loading database with %d words....."RESET,lim);

	printf(YEL"\n(Method #1)");
	get_height(lim);
	printf(YEL"\n"RESET);

    int i=0;
	for(i=0 ; i<lim ; i++){

		if( search(root,db[i].word) == NULL )
                root = insert(db[i].word, root, &flag);
            else
                printf("Cannot insert ..Duplicate entity\n");

		}


	printf(GRN"(Method #2)Height is : %d\n....."RESET,height(root));

	while(1){
			puts(CYN"\nenter a sentence to check"RESET);
			check_my_sentence(root);
			//null_it();
		}

	//inorder(search(root , "cat"));

    return 0;


}



int read_dictionary(char* filename){

	  FILE *fp;

	int wrd_no=0;
	char word[20];

		fp = fopen(filename,"r");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}



	while(fscanf(fp, "%s\n", word) ==1)
	{

		//printf("%s\n", word);
		strcpy(db[wrd_no++].word , word);
		//wrd_no++;

	}

	return wrd_no++;
  fclose(fp);

	}


void null_it(void){
    int i =0;
	for(i=0; i<256 ; i++)

		st[i].word[0] = '\0';

	}

void print_sug(void){

	int c = 4;
    int i=0;
	for(i=1; i<256 &&c ; i++){

		if(st[i].word[0] != '\0'){
			printf("**Did you mean : %s\n",st[i].word);
			c--;

			}

		}






	}

void show_found(void){

	puts("**entering display ...**");

	int i =0;
	for(i=0 ; i<256 ; i++){

		if(st[i].word[0] !='\0')
		printf(YEL "[%d] %s\n" RESET,i,st[i].word);

		}

	puts("**leaving display ...**");

	}

void check_my_sentence(struct node *ptr){

char *origin;
char *token;
char str[256];
//char last[32];

par_index = 0;

fgets(str,sizeof(str)-1, stdin);
//scanf("%[^\n]",str);


//replace '\n' with null character
int i =0;
for(i=0 ; i<256 ; i++){
	if(str[i] == '\n'){

		str[i] ='\0';
		break;

		}

	} // end of if



//check if the sentence is empty
if(strlen(str)<1){

puts("You entered an empty String");
return;

}

toLowerCase(str);
origin = strdup(str);


int flag_f = 0;
int flag_s;


char pre[32] , suc[32];

 token = strtok(str, " ");
 while( token != NULL ) {
      //printf( " %s\n", token );
    //terminate_it(token);
		toLowerCase(token);

flag_s = check_symbols(token);
if(!flag_s)
{

printf(MAG "Word %s is invalid\n" RESET,token);

}else{



if(search(ptr , token) == NULL){

			if(!flag_f){
					printf(RED "Word (%s) not found\n" RESET,token);

					par_index = 0;
					get_suc_and_pre(ptr , suc ,pre,token);
					printf(YEL "Did you mean %7s ?\n" RESET,suc);
					printf(YEL "Did you mean %7s ?\n" RESET,pre);

					print_parent(suc , pre ,token);
					//printf("Parent is : %s\n" , search(ptr , suc)->parent->word);



					}

			}else{

				printf(CYN "Word %7s is found\n" RESET,token);

				}












		flag_f = 0;



}




      token = strtok(NULL, " ");
   }

   //changed >> strsep not available in Windows
  /*
while( (token = strsep(&origin," "))!= NULL){


		token[strlen(token)] = '\0';
		//terminate_it(token);
		toLowerCase(token);

flag_s = check_symbols(token);
if(!flag_s)
{

printf(MAG "Word %s is invalid\n" RESET,token);

}else{



if(search(ptr , token) == NULL){

			if(!flag_f){
					printf(RED "Word (%s) not found\n" RESET,token);

					par_index = 0;
					get_suc_and_pre(ptr , suc ,pre,token);
					printf(YEL "Did you mean %7s ?\n" RESET,suc);
					printf(YEL "Did you mean %7s ?\n" RESET,pre);

					print_parent(suc , pre ,token);
					//printf("Parent is : %s\n" , search(ptr , suc)->parent->word);



					}

			}else{

				printf(CYN "Word %7s is found\n" RESET,token);

				}












		flag_f = 0;



}






	} // end of while

	*/





	}



void subString(char* word , char* subWord){

	int len = strlen(word);
	int i=0;

	for(i =0; i<len-1 ; i++){
		subWord[i] = word[i];
		}
	subWord[i] = '\0';



	}



void get_suc_and_pre(struct node *ptr , char *suc , char *pre , char *word){

	if(ptr!=NULL){

		if(strcmp(word , ptr->word) <0){
			strcpy(suc , ptr->word);
			get_suc_and_pre(ptr->left , suc , pre , word);

		}else{

			strcpy(pre , ptr->word);
			get_suc_and_pre(ptr->right , suc , pre , word);

			}

		//printf("Parent is : %s\n" , ptr->word);


		strcpy(parents[par_index++].word , ptr->word);


		}


	}


void get_parent( struct node *ptr , char *word){

	while(ptr!=NULL){

		if( !strcmp(ptr->left->word , word))
		{

			printf("Parent is : %s\n", ptr->word);
			return;
			}

		ptr = ptr->left;


		}

	}


void print_parent(char *suc , char *pre , char* token){

					int flag =0;
					int h=0;
					for(h=0 ; h<11 ; h++){
						if(strcmp(suc , parents[h].word) && strcmp(pre , parents[h].word) && !flag ){
								if( parents[h].word[0] == token[0]){
										printf(YEL "Did you mean %7s ?\n" RESET, parents[h].word);
										return;


									}

							}


	}
}



void toLowerCase(char*str){

	if(strlen(str) ==1 && *str == 'I')
	return;

	if(*str == 'I' && *str+1 != ' '){
		*str++;
	}


	while(*str != '\0'){

		if(*str > 64 && *str <91){
			*str = *str + 32;

			}
		//printf("*%c" , *str);
		str++;
		}
	//puts("it");


	}

void terminate_it(char* word){

		int i=0;
		while(word[i++] != '\n'){


			}
			word[i] = '\0';


	}


int check_symbols(char* word){


while(*word != '\0'){
if((strlen(word) == 1) && *word == 'I')
return 1;
if(*word>'z' || *word < 'a'){

return 0;
}

word++;


 } //end of while

return 1;
}
