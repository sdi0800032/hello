#ifndef METRIC_C
#define METRIC_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "hash.h"
#include "records.h"

//#include <math.h>
#define LINESZ 4096






void matrix(char* path,int k,int L,char *query,char *output){

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

    read = getline(&line, &len, stream);

    //printf("%s", line);
    read = getline(&line, &len, stream);
    //printf("Retrieved line of length %zu :\n", read);
 
	char *token = strtok(line," \n\t");  ////metrame to plithos apostasew kathe stoixeiou
	while( token != NULL) 
	{
		count++;
		int d = atoi(token);
		token = strtok(NULL," \n\t");
	}
	//printf("count %d\n",count);
	int **pinakas= malloc (sizeof (int*) * count); //////edw apothikeuontai ola ta dedomena apo to dataset
	for(i=0;i<count;i++){
		pinakas[i]=(int*)malloc(sizeof(int) * count);
	}
	i=0;
	rewind(stream);
	fscanf(stream,"%s %s ",gramma,gramma2);
    read = getline(&line, &len, stream);
	char **onomata= malloc (sizeof (char*) * count); ///////////ftiaxnoume ena pinaka me to onoma kathe entry gia na ektupwthei argotera

	for(i=0;i<count;i++){
		onomata[i]=(char*)malloc(sizeof(char) * 64);
		memset(onomata[i], 0, sizeof onomata[i]);
	}
	i=0;
	while(    read = getline(&line, &len, stream)!=0 && i<count){
       //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
		char noumero[6];
		strcat(onomata[i],"item");
		sprintf(noumero,"%d",i);
		strcat(onomata[i],noumero);
		//printf("onoma %s \n",onomata[i]);
		char *token = strtok(line," \n\t");  //should use delimiter
		while( token != NULL) {
			int d = atoi(token);
	   
			//printf("j=%d\n",j);
			pinakas[i][j]=d;
	   		token = strtok(NULL," \n\t");
			j++;
		}
		i++;
		j=0;


	}
	i=0;
	int **tuxaioi= malloc (sizeof (int*) *(2* k));	////edw apothikeuontai oi tuxaioi arithmoi pou paragontai gia kathe L
	for(i=0;i<(2*k);i++){
		tuxaioi[i]=(int*)malloc(sizeof(int) * L);
	}
	for(j=0;j<L;j++){		////////apothikeusi tuxaiwn arithmwn
	for(i=0;i<k;i++){
		int tuxaios1=rand()%(count);
		int tuxaios2=rand()%(count);
		while(tuxaios1==tuxaios2){
			tuxaios1=rand()%(count);
			tuxaios2=rand()%(count);

		}
		//printf("tuxaioi :%d %d\n",tuxaios1,tuxaios2);
		tuxaioi[j][2*i]=tuxaios1;
		tuxaioi[j][2*i+1]=tuxaios2;

	}
	}
	int o=0;
	initHashtable(1000,L);		////arxikopoiisi hashtable
	for(o=0;o<1000;o++){
		for(j=0;j<L;j++){

		int bucket=metric_hash(pinakas,tuxaioi,o,count,L,k,j);	//////kanoume to hashing gia na vroume to bucket pou tha mpei to entry
		//printf("o %d bucket : %d \n",o,bucket);
		matrix_ptr neo=malloc(sizeof(matrix_ptr));    ////ftiaxnoume to node tou hashtable
	    neo->matrix_distances= malloc(sizeof(int) * 1000);
		neo->matrix_distances=pinakas[o];
		neo->id=onomata[o];
		neo->position=o;
		bucketentry2( neo , bucket, o, j);	////vazoume to neo node sto hashtable
			
		}
	}
	//printf(" QUERY %s \n",query);
	metric_Search(query,k,L,tuxaioi,count,pinakas,output); ////kaloume ti sunartisi pou analamvanei to query file


	for(i=0;i<count;i++){
		free(pinakas[i]);
		free(onomata[i]);
	}
	free(pinakas);
	free(onomata);
	/*for(i=0;i<(2*k);i++){
		free(tuxaioi[i]);
	}
	free(tuxaioi);*/
}

///////////vriskei ton median aritmo anamesa se ena array me tis apostaseis analoga me tous tuxaious arithmous gia to hashing

int find_median(int k,int L,int **pinakas,int line){
    int temp;
    int i, j;
    for(i=0; i<k-1; i++) {
        for(j=i+1; j<k; j++) {
            if(pinakas[line][j] < pinakas[line][i]) {
                temp = pinakas[line][i];
                pinakas[line][i] = pinakas[line][j];
                pinakas[line][j] = temp;
            }
        }
    }
/////////elegxoume an to megethos tou pinaka einai pollaplasio tou 2 kai kinoumaste analoga
    if(k%2==0) {
        return((pinakas[line][k/2] + pinakas[line][(k/2) - 1]) / 2);
    } else {
        return pinakas[line][k/2];
    }
}


/////////////////voithaei stin metatropi apo duadiko se dekadiko
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
	
///////ulopoiei ti sunartisi g tou hashing xrisimopoiontas ton pinaka me tous tuxaious arithmous 

int metric_hash(int **pinakas,int **tuxaioi,int o,int count,int L,int k,int j){
	int i=0,a=0,b=0;
	int z=0;
	int **distances=malloc(sizeof(int*)*L);
	int **true_distances=malloc(sizeof(int*)*L);
	for(a=0;a<L;a++){
			distances[a]=malloc(sizeof(int)*k);
			true_distances[a]=malloc(sizeof(int)*k);

	}
	char result[k],final[k];
	int aut=0,bucket=0;
	memset(result, 0, sizeof result);
	memset(final, 0, sizeof final);

	for(i=0;i<k;i++){
///pairnoume apo ton pinaka me ta dedomena tis sugkekrimenes apostaseis pou mas deixnoun oi tuxaioi arithmoi gia kathe hashtable L
	//printf("chosens :%d %d %d\n",pinakas[o][tuxaioi[j][2*i]],pinakas[o][tuxaioi[j][2*i+1]],pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]);
	int distance=(pinakas[o][tuxaioi[j][2*i]]*pinakas[o][tuxaioi[j][2*i]]+pinakas[o][tuxaioi[j][2*i+1]]*pinakas[o][tuxaioi[j][2*i+1]]-pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]*pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]])/(2*pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]);
	if(distance<0){
		distance=-1*distance;
	}	
//////ftiaxnoume duo pinakes me tis apostaseis giati o enas tha taxinomithei gia na vrethei o median
	//printf("distance :%d\n",distance);
	distances[j][i]=distance;
	true_distances[j][i]=distance;
	}
	int median=find_median(k,L,distances,j);
//	printf("median :%d\n",median);
////sugkrinoume tis apostaseis me ton median gia na vroume to string apo duadika psifia pou psaxnoume
	for(z=0;z<k;z++){
		if(true_distances[j][z]>=median){
			result[z]='1';
		}
		else{
			result[z]='0';
		}
		

	}
	//	printf("result : %s \n",result);
///// metatrepoume to duadiko string se dekadiko gia na exoume to bucket sto opoio 8a katalixei to entry
		z=0;
		while(z<k){	
			final[z]=result[z];
			aut=atoi(&final[z]);
			bucket=bucket+aut*Pow(k-z-1);
			z++;
		}
	for(a=0;a<L;a++){
		free(distances[a]);
		free(true_distances[a]);

	}
	free(distances);
	free(true_distances);
	return bucket;
	



}
//////////kanei ta idia me to metric_hash apla dexetai kai to int *antikeimeno pou einai oi apostaseis tou antikeimenou tou qyery me ta antikeimena pou exoun idi apothikeutei sti domi mas
///// ti xrisimopoioume gia na vroume to bucket sto opoio 8a pigaine to entry apo to query

int metric_hash2(int *antikeimeno,int **pinakas,int **tuxaioi,int count,int L,int k,int j){
	int i=0,a=0;
	int z=0;
	int **distances=malloc(sizeof(int*)*L);
	int **true_distances=malloc(sizeof(int*)*L);
	for(a=0;a<L;a++){
			distances[a]=malloc(sizeof(int)*k);
			true_distances[a]=malloc(sizeof(int)*k);

	}
	char result[k],final[k];
	int aut=0,bucket=0;
	memset(result, 0, sizeof result);
memset(final, 0, sizeof final);

	for(i=0;i<k;i++){
	//printf("tuxaioi[j][2*i] %d tuxaioi[j][2*i+1] %d \n",tuxaioi[j][2*i] ,tuxaioi[j][2*i+1]);
	//printf("chosens :%d %d %d\n",antikeimeno[tuxaioi[j][2*i]],antikeimeno[tuxaioi[j][2*i+1]],pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]);
	int distance=(antikeimeno[tuxaioi[j][2*i]]*antikeimeno[tuxaioi[j][2*i]]+antikeimeno[tuxaioi[j][2*i+1]]*antikeimeno[tuxaioi[j][2*i+1]]-pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]*pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]])/(2*pinakas[tuxaioi[j][2*i]][tuxaioi[j][2*i+1]]);
	if(distance<0){
		distance=-1*distance;
	}	
	//printf("distance :%d\n",distance);
	distances[j][i]=distance;
	true_distances[j][i]=distance;
	}
	int median=find_median(k,L,distances,j);
	//printf("median :%d\n",median);
	for(z=0;z<k;z++){
		if(true_distances[j][z]>=median){
			result[z]='1';
		}
		else{
			result[z]='0';
		}
		

	}
		//printf("result : %s \n",result);
		z=0;
		while(z<k){	
			final[z]=result[z];
			aut=atoi(&final[z]);
			bucket=bucket+aut*Pow(k-z-1);
			z++;
		}
	for(a=0;a<L;a++){
		free(distances[a]);
		free(true_distances[a]);

	}
	free(distances);
	free(true_distances);
	return bucket;
	



}


//////analamvanei na diavasei to query file na vrei to bucket tou kathe entry sto hashtable kai na vrei se auto to bucket tous kontinoterous
////episis kanei tin ektupwsi sto arxeio pou tou dinoume

void metric_Search(char *query,int k,int L,int **tuxaioi,int count,int **pinakas,char *output){
	FILE* stream = fopen(query, "r");
	FILE* out = fopen(output, "w");
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char gramma[64];
	int aktina;
	int i=0;
	int *antikeimeno= malloc (sizeof (int*) * count);	/////////to entry pou pairnoume apo to query arxeio
	fscanf(stream,"%s %d ",gramma,&aktina);
	int j=0,summ=0,flag=0;	    
	i=0;
	int query_counter=0;




	while(read = getline(&line, &len, stream)!=-1){	////diavazoume to arxeio
		//fscanf(stream,"%s",gramma);
		char *start = strtok(line," \n\t");
		fprintf(out,"\nQuery:%s  \n", start);
		fprintf(out,"R= %d  ", aktina);
		fprintf(out,"near items\n");
		int **ektupwmena= malloc (sizeof (int*) * 100);	////mas voi8aei na doume an kapoio node exei idi ektupwthei gia kapoio entry
		int a=0,b=0;
		for(a=0;a<100;a++){
			ektupwmena[a]=(int*)malloc(sizeof(int) * count);
			for(b=0;b<count;b++){
				ektupwmena[a][b]=0;
			}
		}	
		if (strlen(line) != 0) {
			int position=0;
			char *token = strtok(NULL," \n\t");
			while( token != NULL) {
				if(flag!=0){		///////apofeugoume to prwto string kathe grammis pou einai to onoma tou entry
					int d = atoi(token);
					antikeimeno[i]=d;
				}
				if(antikeimeno[i]==0){		///////vriskoume ti 8esi tou midenikou gia na doume tin thesi tou sti domi mas
					position=i;
				}
				flag=1;
				i++;

				token = strtok(NULL," \n\t");
			}
			int minimum_distance=100;		/////arxikopoioime to distance me kati pou sigoura 8a vroume mikrotero tou
			int actual_distance=100;
			char nearest[64];
			strcpy(nearest,"none");
			clock_t begin = clock();	////clock LSH
			for(j=0;j<L;j++){
			///////vriskoume to bucket sto opoio 8a pigaine to entry
				int bucket=metric_hash2(antikeimeno,pinakas,tuxaioi,count,L,k,j);
				//printf("position %d sto query bucket %d  \n",position,bucket);
				if(BucketArray[j][bucket]->count>0){
					///// koitame to sugkekrimeo bucket sto hashtable
					for(i=0;i<BucketArray[j][bucket]->count;i++){
						if(BucketArray[j][bucket]->bucketarray[i].m_ptr->matrix_distances[position]<=aktina){
							if(BucketArray[j][bucket]->bucketarray[i].m_ptr->matrix_distances[position]!=0){
						///// an einai mikrotero tous radius kai dn einai i apostasi 0
						///// an den exei idi ektupw8ei
								if(ektupwmena[query_counter][BucketArray[j][bucket]->bucketarray[i].m_ptr->position]==0){
									ektupwmena[query_counter][BucketArray[j][bucket]->bucketarray[i].m_ptr->position]=1;
									fprintf(out,"%s \n",BucketArray[j][bucket]->bucketarray[i].m_ptr->id);
								}
							}					
						}
						////// vriskoume ti mikroteri apostasi gia ka8e L
						if(BucketArray[j][bucket]->bucketarray[i].m_ptr->matrix_distances[position]<minimum_distance && BucketArray[j][bucket]->bucketarray[i].m_ptr->matrix_distances[position]!=0){
							minimum_distance=BucketArray[j][bucket]->bucketarray[i].m_ptr->matrix_distances[position];
							strcpy(nearest,BucketArray[j][bucket]->bucketarray[i].m_ptr->id);
						}
					}
				}
			///// vriskoume ti mikroteri apostas apo ola ta L
				if(minimum_distance<actual_distance){
					actual_distance=minimum_distance;
				}
				minimum_distance=30;

		
				i=0;

				flag=0;
				summ++;
				//printf("\n\n");
				//j++;
			}
			fprintf(out,"Nearest Neighbour : %s \n",nearest);
			clock_t end = clock();	//////telos clock LSH
			fprintf(out,"distance LSH : %d \n",actual_distance);
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

			int normal_least=30;
			clock_t begin_normal = clock();
			////prospaleunoume oli ti domi mas seiriaka gia na vroume kanonika tin mikroteri apostasi
			for(i=0;i<count;i++){
				if(antikeimeno[i]<normal_least && antikeimeno[i]!=0 ){

					normal_least=antikeimeno[i];
				}
			}
			fprintf(out,"distance True: %d \n",normal_least);
			fprintf(out,"tLSH: %f \n",time_spent);
			clock_t end_normal = clock();
			double time_spent_normal = (double)(end_normal - begin_normal) / CLOCKS_PER_SEC;
			fprintf(out,"tTrue: %f \n\n",time_spent_normal);
			i=0;
			position=0;
			normal_least=30;
		}

		//free(line);


	query_counter++;
	for(a=0;a<100;a++){
		free(ektupwmena[a]);
	}
	free(ektupwmena);

	}
	free(antikeimeno);

}

#endif  /* METRIC_C */
