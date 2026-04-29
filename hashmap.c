#include "stdio.h"
#include "stdlib.h"
#include "linked_list.h"
#include "string.h"

struct Hashmap;

typedef int (*hash_func)(struct Hashmap *, void *);
typedef void (*insert_func)(struct Hashmap *, void *, void *, size_t, size_t);
typedef void (*printer_func)(struct Hashmap *);
typedef void (*printer_func)(struct Hashmap *);

typedef struct Hashmap{
  Node **hashmap;
  int buckets;
  
  hash_func comparator;
  insert_func insert;

  printer_func print;
  printer impl_printer;
} Hashmap;

struct Pair{
  void *key;
  void *val;
};

void insert_hashmap(Hashmap *ctx, void *key, void *value, size_t size_key, size_t size_val){
  int pos = ctx -> comparator(ctx, key);
  printf("\nPos: %d %s %s\n", pos, (char *)key, (char *)value);

  void *save_key = (void *) malloc(size_key);
  void *save_val = (void *) malloc(size_val);

  memcpy(save_key, key, size_key);
  memcpy(save_val, value, size_val);

  struct Pair *pair = (struct Pair *)malloc(sizeof(struct Pair));
  pair -> key = save_key;
  pair -> val = save_val;

  printf("Pair %p\n", pair);
  //printf("Pair key %s\n",(char *)pair -> key);
  //printf("Pair val %s\n", (char *)pair -> val);
  
  //ctx -> hashmap[pos] = prepend(ctx -> hashmap[pos], value, ctx -> size_val);
  ctx -> hashmap[pos] = prepend_ptr(ctx -> hashmap[pos], pair);
  //print_list(ctx -> hashmap[pos], int_printer);
}


void printer_hashmap(Hashmap *ctx){
  for(int i = 1; i < ctx -> buckets; i++){
    if(ctx -> hashmap[i] -> ptr_value != NULL)
      printf("%s\n", (char*)((struct Pair *)ctx -> hashmap[i] -> ptr_value) -> key);
    //print_list(ctx -> hashmap[i], ctx -> impl_printer);
  }
}

void impl_printer_str(void *ptr){
  if(ptr != NULL)
    printf("%s", (char *)ptr);
}

Hashmap *hashmap_init(int m, hash_func h, printer impl_printer){
  Hashmap *hashmap = (Hashmap *)malloc(sizeof(Hashmap));
  hashmap -> buckets = m;

  hashmap -> hashmap = (Node **)malloc(sizeof(Node *) * m);

  hashmap -> comparator = h;
  hashmap -> insert = insert_hashmap;

  hashmap -> impl_printer = impl_printer;
  hashmap -> print = printer_hashmap;
  
  for(int i = 0; i < m; i++){
    hashmap -> hashmap[i] = (Node *) malloc(sizeof(Node));

    printf("%d) %p\n", i, hashmap -> hashmap[i]);
    //print_list(hashmap -> hashmap[i], int_printer);
  }
  
  return hashmap;
}


int comparator(Hashmap *ctx, void *key){
  char *str = (char *)key;

  int acc = 0;
  for(int i = 0; str[i] != '\0'; i++){
    //printf("%c", str[i]);
    acc += (int) str[i];
  }
  return acc % ctx -> buckets;
}

int comparator_int(Hashmap *ctx, void *key){
  return *(int *)key / ctx -> buckets;
}


int main(){

  Hashmap *hashmap = hashmap_init(7, comparator, str_printer);

  char key1[] = "hello";
  char val1[] = "world";

  int z = 41;
  int t = 42;
  
  hashmap -> insert(hashmap, (void *)key1, (void *)val1, strlen(key1), strlen(val1));

  hashmap -> print(hashmap);

  /*
  t++;
  z += 3;

  hashmap -> insert(hashmap, (void *)&z, (void *)&t);
  hashmap -> print(hashmap);
   */
  
  //hashmap_insert(hashmap, (void *)key1, (void *) val1, comparator);
  
  return 0;
}
