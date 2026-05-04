// Compile with -lm flag for math.h
// gcc -lm main.c -o hashmap && ./hashmap
#include "hashmap.h"
#include "stdbool.h"
#include "math.h"

// Function Modified 
int hash(Hashmap *ctx, void *key){
  char *str = (char *)key;

  int acc = 0;
  for(int i = 0; str[i] != '\0'; i++){
    //printf("%c", str[i]);
    acc += (int) str[i];
  }

  double int_part;
  double double_part;

  double_part = modf(acc * 0.6180, &int_part);
  double hash = double_part * ctx -> buckets;

  printf("Acc %f %f %f\n", double_part, int_part, hash);
  
  return (int) round(hash);
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

  char key2[] = "hallo";
  char val2[] = "welt";

  char key3[] = "ola";
  char val3[] = "mundo";

  
  hashmap -> insert(hashmap, (void *)key1, (void *)val1, strlen(key1), strlen(val1));
  hashmap -> insert(hashmap, (void *)key2, (void *)val2, strlen(key2), strlen(val2));
  hashmap -> insert(hashmap, (void *)key3, (void *)val3, strlen(key3), strlen(val3));


  hashmap -> print(hashmap);

  void *res = hashmap -> search(hashmap, (void *)key1);

  if(res == NULL)
    printf("Value not found");
  else
    printf("\nFound Value %s\n", (char *)res);

  void *res2 = hashmap -> search(hashmap, (void *)val1);
  
  if(res2 == NULL)
    printf("Value not found");
  else
    printf("Found Value %s\n\n", (char *)res2);

  hashmap -> delete(hashmap, (void *)key1);

  hashmap -> print(hashmap);

  hashmap -> delete(hashmap, (void *)key2);

  hashmap -> print(hashmap);

  //reinsert 1
  hashmap -> insert(hashmap, (void *)key1, (void *)val1, strlen(key1), strlen(val1));
  hashmap -> insert(hashmap, (void *)key3, (void *)val3, strlen(key3), strlen(val3));

  hashmap = hashmap -> free(hashmap);

  if(hashmap == NULL)
    printf("Hashmap deallocated");
  else
    printf("Failed to free hashmap");
  

  /*
  t++;
  z += 3;

  hashmap -> insert(hashmap, (void *)&z, (void *)&t);
  hashmap -> print(hashmap);
   */
  
  //hashmap_insert(hashmap, (void *)key1, (void *) val1, comparator);
  
  return 0;
}
