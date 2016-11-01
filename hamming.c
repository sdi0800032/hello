#ifndef HAMMING_C
#define HAMMING_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "records.h"
//#include <math.h>
#define LINESZ 1024




/////////////////voithaei stin metatropi apo duadiko se dekadiko
/*int Pow(int p){

	int i;
	int x=1;
	if(p == 0)
		return 1;
	else{
		for(i=0;i<p;i++)
			x = x*2;
	}
	return x;

}*/


void hamming(char *path,int k,int L,char *query,char *output){

	int j=0,mikos,i=0,o=0,z=0,bucket=0,aut=0,amount=0;
	char c;
	char buff[80];
	unsigned long long item1;
	char item[64],number[64],gramma[50],gramma2[64],result[k];
	int **tuxaioi= malloc (sizeof (int*) * k);       //////////edw apothikeuontai oi tuxaioi arithmoi gia to hash
	for(i=0;i<k;i++){
		tuxaioi[i]=(int*)malloc(sizeof(int) * L);
	}
		


 	FILE* stream = fopen(path, "r");

	i=0;
	fscanf(stream,"%s %s ",gramma,gramma2);
	//printf("%s  \n", gramma2);



	while(fgets (buff, LINESZ, stream)!=NULL){
		sscanf(buff,"%s %s",item,number);
		//printf( "%s \t",item);
		//printf(" %s \n",number);
		mikos=strlen(number);	///// vriskoume poso megaloi einai oi arithmoi	
		amount++;   		///////kai to plithos tous
	}
	//printf("mikos %d \n",mikos);
	//printf("amount %d \n",amount);
	char **inputs;			///// edw apothikeuontai ta dedomena apo ta datasets
	inputs=malloc(sizeof(char*)*amount);
	for(i=0;i<amount;i++){
		inputs[i]=(char*)malloc(sizeof(char)*100);
	}
	i=0;
	rewind(stream);
	fscanf(stream,"%s %s ",gramma,gramma2);
	while(j<L){ 		//////////paragontai oi tuxaioi arithmoi
		while(i<k){
			int tuxaios=rand()%(mikos+1);
			//printf("tuxaios %d \n",tuxaios);
			tuxaioi[i][j]=tuxaios;
			i++;


		}
		i=0;
		j++;
	}
	i=0;
	j=0;


	memset(result, 0, sizeof result);
	initHashtable(64,L);		/////arxikopoiisi hashtable
	for(o=0;o<amount;o++){
		if (fgets (buff, LINESZ, stream)){		////diavazoume enan ena ta dedomena
			sscanf(buff,"%s %s",item,number);
			//printf( "%s \t",item);
			//printf(" %s \n",number);
			number_ptr noumero=malloc(sizeof(number_ptr));
			noumero->name= malloc(sizeof(char) * 100);
			noumero->id= malloc(sizeof(char) * 100);
			strcpy(inputs[o],number);
			strcpy(noumero->name,number);
			strcpy(noumero->id,item);
			noumero->position=o;
			while(j<L){
			bucket=hamming_hash(k,L,number,tuxaioi,j);		/////kaloume ti sunartisi pou epistrefei se poio bucket prepei na mpei kathe entry
						//printf("bucket %d \n",bucket);
			bucketentry1( noumero , bucket ,j);		///// vazoume to entry sto antistoixo bucket
			
			j++;
		}
	j=0;
	}
	
	}
////// afou diavasame ola ta dedomena kaloume ti sunartisi pou dexetai ta queries
	hamming_Search(query,k,L,tuxaioi,mikos,amount,inputs,output);

	for(i=0;i<k;i++){
		free(tuxaioi[i]);
	}
	free(tuxaioi);
	for(i=0;i<amount;i++){
		free(inputs[i]);
	}
	free(inputs);
}

//////////Kanei to hash kai epistrefei to keli sto opoio prepei na mpei o kathe arithmos

int hamming_hash(int k,int L,char number[64],int **tuxaioi,int j){
	char *result=malloc(sizeof(char)*k);
//////// ftiaxnoume enan pinaka me ta tuxaia psifia tou arithmou pou epilexame nwritera gia kathe diaforetiko L
///// metatrepoume meta ton pinaka auton pou einai mia anaparastasi k duadikwn psifiwn se dekadiko arithmo
//// gia na exoume to bucket pou psaxnoume
	int i=0,aut=0,bucket=0;
	memset(result, 0, sizeof result+1);
		while(i<k){	

			result[i]=number[64-tuxaioi[i][j]-1];
			aut=atoi(&result[i]);
			bucket=bucket+aut*Pow(k-i-1);
			i++;
		};
		i=0;
		
	//printf("result %s \n",result);
	free(result);
	return bucket;

}


/////////analamvanei na vrei ta entries pou einai sto idio bucket me auto pou dinetai apo to query
/////// kai upologizei ta kontina se auto me vasi tin aktina
////// kathws kai to kontinotero kai tin apostasi tou

void hamming_Search(char *query,int k,int L,int **tuxaioi,int mikos,int amount,char **inputs,char *output){
	FILE* stream = fopen(query, "r");
	FILE* out = fopen(output, "w");
	int **ektupwmena= malloc (sizeof (int*) * 100);		///////enas pinakas pou voi8aei na doume an kapoios kontinos exei idi ektupwthei
	int a=0,b=0;									////// apotrepei to na ektupwnoume polles fores to idio entry se diaforeiko hashtable L 
	for(a=0;a<100;a++){
		ektupwmena[a]=(int*)malloc(sizeof(int) * amount);
		for(b=0;b<amount;b++){
			ektupwmena[a][b]=0;
		}
	}		
	char gramma[64];
	int aktina;
	char number[64];
	int query_counter=0;
	fscanf(stream,"%s %d ",gramma,&aktina);
	fprintf(out,"%s ", gramma);
	fprintf(out,"%d  \n", aktina);
	while(	fscanf(stream,"%s %s ",gramma,number)!=EOF){
			clock_t begin_hash = clock(); //// arxi tou clock gia to LSH
			fprintf(out,"\nQuery: %s  \t", gramma);
			fprintf(out,"%s \n R=%d-near neighbours: \n", number,aktina);
			int j=0;
			int i=0;
			int lowest_distance=100;		/////arxikopoioime to distance me kati pou sigoura 8a vroume mikrotero tou
			char nearest[64];		
			for(j=0;j<L;j++){
				int true_distance=0;
///////// vriskoume to bucket pou antistoixei sto query
				int bucket=hamming_hash(k,L,number,tuxaioi,j);
				//printf("bucket %d \n",bucket);
////// diatrexoume olo to bucket sto opoio 8a pigaine to query
				if(BucketArray[j][bucket]->count>0){
					for(i=0;i<BucketArray[j][bucket]->count;i++){
						//printf("sto hash %s \n",BucketArray[j][bucket]->bucketarray[i].n_ptr->name);
						true_distance=find_distance(BucketArray[j][bucket]->bucketarray[i].n_ptr->name,number,mikos,amount);
						if(true_distance<=(aktina)){	
							if(ektupwmena[query_counter][BucketArray[j][bucket]->bucketarray[i].n_ptr->position]==0){
								ektupwmena[query_counter][BucketArray[j][bucket]->bucketarray[i].n_ptr->position]=1;
			///////////elegxoume an exei xanaektupw8ei auto to entry		
								fprintf(out," %s \n ",BucketArray[j][bucket]->bucketarray[i].n_ptr->id);	
							}
						//printf("-----true distance %d \n ",true_distance);
						}
////////// vriskoume ti mikroteri apostasi kai kratame to id tou entry
						if(true_distance<lowest_distance){
							lowest_distance=true_distance;
							strcpy(nearest,BucketArray[j][bucket]->bucketarray[i].n_ptr->id);
						}					
					}
				}
			}
			clock_t end_hash = clock();   /////telos tou clock tou LSH
			double time_spent = (double)(end_hash - begin_hash) / CLOCKS_PER_SEC;
			fprintf(out,"Nearest Neighbour: %s \n ",nearest);
			fprintf(out,"distanceLSH:%d \n ",lowest_distance);
			clock_t begin_normal = clock(); ////arxi clock gia kanoniko scanning
			int normal_distance= find_normal_distance(inputs,number,mikos,amount);  //////sunartisi upologismou apostasis
			clock_t end_normal = clock();
			double time_spent_normal = (double)(end_normal - begin_normal) / CLOCKS_PER_SEC;
			fprintf(out,"distanceTRUE : %d \n ",normal_distance);
			fprintf(out,"tLSH: %f \n",time_spent);
			fprintf(out,"tTrue: %f \n",time_spent_normal);
			query_counter++;
	}

	for(a=0;a<100;a++){
		free(ektupwmena[a]);
	}
	free(ektupwmena);

}

///////upologizei ti mikroteri apostasi metaxu tou query kai olwn twn stoixeiwn tou dataset

int find_normal_distance(char **inputs,char *number,int mikos,int amount){
	int i=0,j=0;
	int distance=0;
	int smallest_distance=30;
	for(j=0;j<amount;j++){
	for(i=0;i<mikos;i++){
		if(inputs[j][i]!=number[i]){
			distance++;
		}

	}
	if(distance<smallest_distance){
		smallest_distance=distance;
	}
	distance=0;
	}
	return smallest_distance;


}

////////////upologizei tin apostasi tou query me ena entry tou hashtable

int find_distance(char *sto_hashtable,char *apexw,int mikos,int amount){
	int i=0;
	int distance=0;
	for(i=0;i<64;i++){
		if(sto_hashtable[i]!=apexw[i]){
			distance++;
		}

	}
	return distance;



}


#endif  /* HAMMING_C */
