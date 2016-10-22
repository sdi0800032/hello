#include "newfile.h"

//Function for initializing the hash table
void initHashtable(int k) {
    int i;
    BucketArray = malloc(k * sizeof (Bucket *));

    for (i = 0; i < k; i++) {
        BucketArray[i] = malloc(sizeof (Bucket));
        BucketArray[i]->bucketarray = malloc(3 * sizeof (BucketMember));
        BucketArray[i]->count = 0;
        BucketArray[i]->size = 3;
    }

}

void freememory() {
    int i;
    // elefterwnw thn mnhmh tou hash table
    for (i = 0; i < Infos.startbucketsize; i++) {
        free(BucketArray[i]->bucketarray);
    }
    for (i = 0; i < Infos.startbucketsize; i++) {
        free(BucketArray[i]);
    }
    free(BucketArray);
    // elefterwnw oti mnhmh exw desmeysei gia tis anages tou programmatos
    free(Infos.DataFile);

    while (Infos.commandsarraysize >= 0)
        free(Infos.commandsarray[Infos.commandsarraysize--]);

}

/* Function that search the Node in
 * our Hash Table
 * Returns The Node If is Found
 * Else return Null
 */
lnode *searchGraphWithHashtable(listNodeId id) {
    int i, j;
    lnode *temp = NULL;
    i = hashfunction1(id);
    for (j = 0; j < BucketArray[i]->size; j++) {
        if (BucketArray[i]->bucketarray[j].key == id) {
            // printf("searching %d found node with id %d\n",id,BucketArray[i]->bucketarray[j].p->id);
            return BucketArray[i]->bucketarray[j].p;
        }
    }
    return temp;
}

/* Function that adds a Node to a bucket
 * the potition of the added node 
 * will be given from the hash function
 */

void bucketentry(lnode *node) {
    int position = 0;
    position = hashfunction1(node->id);
    BucketMember temps;
    temps.key = node->id;
    temps.p = node;
    putinbucket(temps, position);
}
/* Function that adds a Node to a bucket
 * if the bucket is full we reallocate 
 * a x2 bucket
 */
void putinbucket(BucketMember temp, int position) {
    if (BucketArray[position]->count == BucketArray[position]->size) {
        BucketArray[position]->size *= 2;
        BucketArray[position]->bucketarray = realloc(BucketArray[position]->bucketarray, BucketArray[position]->size * sizeof (BucketMember));
        BucketArray[position]->bucketarray[BucketArray[position]->count++] = temp;
    } else {
        BucketArray[position]->bucketarray[BucketArray[position]->count++] = temp;
        Infos.countentries++;
    }
}

// our hash function return the position of the added Node

int hashfunction1(int key) {

    return key % Infos.startbucketsize;
}
//helper Function that prints the Hash table
void printhashtable() {
    int i, j;
    for (i = 0; i < Infos.startbucketsize; i++) {
        printf("Bucket %d:  Count:%d Size:%d Content:", i, BucketArray[i]->count, BucketArray[i]->size);
        for (j = 0; j < BucketArray[i]->count; j++) {
            printf("%d and %d ||", BucketArray[i]->bucketarray[j].key, BucketArray[i]->bucketarray[j].p->id);
        }
        printf("\n");
    }
    printf("\n");
}

//Function That deletes the Node from the Hash Table
void dellFromHashTable(listNodeId id) {
    int i, j;
    i = hashfunction1(id);
    for (j = 0; j < BucketArray[i]->size; j++) {
        if (BucketArray[i]->bucketarray[j].key == id) {
            // printf("searching %d found node with id %d\n",id,BucketArray[i]->bucketarray[j].p->id);
            BucketArray[i]->bucketarray[j].key = 0;
        }

    }

}
