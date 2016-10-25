#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
#define LINESZ 1024


void hamming(char *path,int k,int L);
int Pow(int);
int hamming_hash(int k,int L,char number[64],int **,int j);



int main(int argc, char** argv){

	char path[256];
	int i=0;
	int k=0,L=0;
	for(i=0;i<argc;i++){
		if(strcmp(argv[i],"-d")==0){
				strcpy(path,argv[i+1]);
				printf("%s\n",path);
		}
		if(strcmp(argv[i],"-k")==0){
			sscanf(argv[i+1], "%d", &k);
		}
		if(strcmp(argv[i],"-L")==0){
			sscanf(argv[i+1], "%d", &L);
		}
	}
	i=0;
	if(L==0){
		L=5;
	}
	if(k==0){
		k=4;
	}
	printf(" k : %d L : %d \n",k,L);
 	FILE* stream = fopen(path, "r");

	char gramma[50],gramma2[50];
	fscanf(stream,"%s %s ",gramma,gramma2);
	printf("%s  \n", gramma2);

	if(strcmp(gramma2,"hamming")==0){
		hamming(path,k,L);
	}
	return 1;
}

int Pow(int p){

	int i;
	int x=1;
	if(p == 0)
		return 1;
	else{
		for(i=0;i<p;i++)
			x = x*2;
	}
	return x;

}


void hamming(char *path,int k,int L){

	int j=0,mikos,i=0,o=0,z=0,bucket=0,aut=0;
	char c;
	char buff[80];
	unsigned long long item1;
	char item[64],number[64],gramma[50],gramma2[64],result[k];
	char g[k][20];
	//char this[3];
	char *tuxi1,*tuxi2,*tuxi3,*tuxi4,*tuxi5;
	int **tuxaioi= malloc (sizeof (int*) * k);
	for(i=0;i<k;i++){
		tuxaioi[i]=(int*)malloc(sizeof(int) * L);
	}
		
	char edw;


 	FILE* stream = fopen(path, "r");



	for(i=0;i<k;i++){
		memset(g[i], 0, sizeof g[i]);
	}
	i=0;
	fscanf(stream,"%s %s ",gramma,gramma2);
	printf("%s  \n", gramma2);



	fgets (buff, LINESZ, stream);
	sscanf(buff,"%s %s",item,number);
	printf( "%s \t",item);
	printf(" %s \n",number);
	//printf("gramma %s \n",item);
	//printf( "item %s \n",number);
	mikos=strlen(number);		
	printf("mikos %d \n",mikos);

	rewind(stream);
	fscanf(stream,"%s %s ",gramma,gramma2);
	while(j<L){
		while(i<k){
			int tuxaios=rand()%(mikos+1);
			//printf("tuxaios %d \n",tuxaios);
			tuxaioi[i][j]=tuxaios;
			printf("i %d tuxaioi %d \n ",i,tuxaioi[i][j]);
			/*sprintf(this, "%d", tuxaios);
			strcat(g[j],this);
			if(i!=(k-1)){
				strcat(g[j],",");
			}
			printf("%s \n" , g[j]);*/
			i++;


		}
		i=0;
		j++;
	}
	i=0;
	j=0;


	memset(result, 0, sizeof result);

	for(o=0;o<5;o++){
	if (fgets (buff, LINESZ, stream)){
		sscanf(buff,"%s %s",item,number);
		printf( "%s \t",item);
		printf(" %s \n",number);
			while(j<L){
		bucket=hamming_hash(k,L,number,tuxaioi,j);
			j++;
		}
	j=0;
	}
	}
}

int hamming_hash(int k,int L,char number[64],int **tuxaioi,int j){
	char result[k];
	int i=0,aut=0,bucket=0;
	memset(result, 0, sizeof result);
	//extern int tuxaioi[k][L];
			while(i<k){	

				result[i]=number[tuxaioi[i][j]];
				aut=atoi(&result[i]);
				bucket=bucket+aut*Pow(k-i-1);
				//printf("aut %d \n",aut);
				//printf("result[i] %c \n",result[i]);
				i++;
			};
			i=0;
			
			printf("result %s \n",result);
			printf("bucket %d \n",bucket);
			return bucket;
			bucket=0;
			aut=0;
			memset(result, 0, sizeof result);

	







}
