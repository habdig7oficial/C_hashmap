
#include "hashmap.h"
#include "stdbool.h"



int hash(Hashmap *ctx, void *key){
  char *str = (char *)key;

  int acc = 0;
  for(int i = 0; str[i] != '\0'; i++){
    //printf("%c", str[i]);
    acc += (int) str[i];
  }
  return acc % ctx -> buckets;
}

bool comparable_str(void *ptr1, void *ptr2){
  return 0 == strcmp((char *)ptr1, (char *)ptr2);
}
int comparator_int(Hashmap *ctx, void *key){
  return *(int *)key / ctx -> buckets;
}

void print_str(void *ptr){
  printf("%s ", (char *)ptr);
}


int main(){

  Hashmap *hashmap = hashmap_init(7, hash, comparable_str, print_str, print_str);

  char key1[] = "hello";
  char val1[] = "world";

  int z = 41;
  int t = 42;
  
  hashmap -> insert(hashmap, (void *)key1, (void *)val1, strlen(key1), strlen(val1));

  hashmap -> print(hashmap);

  void *res = hashmap -> search(hashmap, (void *)key1);

  if(res == NULL)
    printf("Value not found");
  else
    printf("Found Value %s", (char *)res);
  /*
  t++;
  z += 3;

  hashmap -> insert(hashmap, (void *)&z, (void *)&t);
  hashmap -> print(hashmap);
   */
  
  //hashmap_insert(hashmap, (void *)key1, (void *) val1, comparator);
  
  return 0;
}
