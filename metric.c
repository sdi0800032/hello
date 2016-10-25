#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <math.h>
#define LINESZ 4096


void matrix(char* path,int k,int L);
int find_median(int k,int L,int pinakas[k][L],int line);
int Pow(int);
int metric_hash(int **pinakas,int **tuxaioi,int o,int count,int L,int k);

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
 	FILE* stream = fopen(path, "r");
	char gramma[50],gramma2[50];
	fscanf(stream,"%s %s ",gramma,gramma2);
	printf("%s  \n", gramma2);

	if(strcmp(gramma2,"matrix")==0){
		matrix(path,k,L);
	}
}



void matrix(char* path,int k,int L){

 	FILE* stream = fopen(path, "r");
	int i=0,j=0;
	char buff[3000];
	char gramma[50],gramma2[50],item[3000],number[3000];
	fscanf(stream,"%s %s ",gramma,gramma2);
	printf("%s  \n", gramma2);
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	int count=0;


	/*fgets (buff, LINESZ, stream);
	fgets (buff, LINESZ, stream);
	sscanf(buff,"%s %s",item,number);
	printf( "%s \t",item);*/
	//printf(" %s \n",number);
    read = getline(&line, &len, stream);
      //  printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        read = getline(&line, &len, stream);
        printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
	char *token = strtok(line," \n\t");  //should use delimiter
	while( token != NULL) 
	{
		count++;
	   int d = atoi(token);
	   //printf("%d\n",d);
	   token = strtok(NULL," \n\t");
	}
	sleep(1);
	printf("count %d\n",count);
	//int pinakas[count][count];
	int **pinakas= malloc (sizeof (int*) * count);
	for(i=0;i<count;i++){
		pinakas[i]=(int*)malloc(sizeof(int) * count);
	}
	i=0;
	rewind(stream);
	fscanf(stream,"%s %s ",gramma,gramma2);
    read = getline(&line, &len, stream);
	while(    read = getline(&line, &len, stream)!=0 && i<count){
       //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
		char *token = strtok(line," \n\t");  //should use delimiter
		while( token != NULL) {
			int d = atoi(token);
	   
			printf("j=%d\n",j);
			pinakas[i][j]=d;
	   		token = strtok(NULL," \n\t");
			j++;
			//usleep(10000);
		}
printf("i=%d\n",i);
		i++;
		j=0;


	}
	i=0;
	//int tuxaioi[2*k][L];
	int **tuxaioi= malloc (sizeof (int*) *(2* k));
	for(i=0;i<(2*k);i++){
		tuxaioi[i]=(int*)malloc(sizeof(int) * L);
	}
	for(j=0;j<L;j++){
	for(i=0;i<k;i++){
		int tuxaios1=rand()%(count);
		int tuxaios2=rand()%(count);
		while(	tuxaios1==i || tuxaios2==i || tuxaios1==tuxaios2){
			int tuxaios1=rand()%(count);
			int tuxaios2=rand()%(count);

		}
		printf("tuxaioi :%d %d\n",tuxaios1,tuxaios2);
		tuxaioi[j][2*i]=tuxaios1;
		tuxaioi[j][2*i+1]=tuxaios2;

	}
	}
	int o=0;
	for(o=0;o<5;o++){
		int bucket=metric_hash(pinakas,tuxaioi,o,count,L,k);	
	}
}



int find_median(int k,int L,int pinakas[k][L],int line){
    int temp;
    int i, j;
    // the following two loops sort the array x in ascending order
    for(i=0; i<k-1; i++) {
        for(j=i+1; j<k; j++) {
            if(pinakas[line][j] < pinakas[line][i]) {
                // swap elements
				printf("mesa sto median %d",pinakas[line][i]);
                temp = pinakas[line][i];
                pinakas[line][i] = pinakas[line][j];
                pinakas[line][j] = temp;
            }
        }
    }

    if(k%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
        return((pinakas[line][k/2] + pinakas[line][k/2 - 1]) / 2);
    } else {
        // else return the element in the middle
        return pinakas[line][k/2];
    }
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
		

int metric_hash(int **pinakas,int **tuxaioi,int o,int count,int L,int k){
	int i=0;
	int j=0;
	int z=0;
	int distances[L][k];
	int true_distances[L][k];
	char result[k],final[k];
	int aut=0,bucket=0;
	memset(result, 0, sizeof result);
memset(final, 0, sizeof final);
for(j=0;j<L;j++){
	for(i=0;i<k;i++){

	printf("chosens :%d %d %d\n",pinakas[o][tuxaioi[j][2*i]],pinakas[o][tuxaioi[j][2*i+1]],pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]);
	int distance=(pinakas[o][tuxaioi[j][2*i]]*pinakas[o][tuxaioi[j][2*i]]+pinakas[o][tuxaioi[j][2*i+1]]*pinakas[o][tuxaioi[j][2*i+1]]-pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]*pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]])/(2*pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]);
	printf("distance :%d\n",distance);
	distances[j][i]=distance;
	true_distances[j][i]=distance;
	}
	int median=find_median(k,L,distances,j);
	printf("median :%d\n",median);
	for(z=0;z<k;z++){
		if(true_distances[j][z]>median){
			result[z]='1';
		}
		else{
			result[z]='0';
		}
		

	}
		printf("result : %s \n",result);
		z=0;
		while(z<k){	
			final[z]=result[z];
			aut=atoi(&final[z]);
			bucket=bucket+aut*Pow(k-z-1);
			z++;
		}
		printf("bucket : %d \n",bucket);
		return bucket;
	}



}


