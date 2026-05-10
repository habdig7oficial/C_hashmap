#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

struct Hashmap;

typedef struct Pair{
  void *key;
  void *val;
} Pair;

typedef int (*hash_func)(struct Hashmap *, void *);
typedef void (*insert_func)(struct Hashmap *, void *, void *, size_t, size_t);
typedef void* (*search_func)(struct Hashmap *, void *);
typedef void (*delete_func)(struct Hashmap *, void *);
typedef bool (*comparator)(void *, void *);
typedef void* (*free_func)(struct Hashmap *);

typedef void (*printer_func)(struct Hashmap *);
typedef void (*printer_impl)(void *);

typedef struct Hashmap{
  Pair **hashmap;
  int buckets;
  
  hash_func hash;
  insert_func insert;
  search_func search;
  delete_func delete;
  free_func free;

  comparator comparator;

  printer_func print;
  printer_impl print_key;
  printer_impl print_val;
  
} Hashmap;


void insert_hashmap(Hashmap *ctx, void *key, void *value, size_t size_key, size_t size_val){
  int pos = ctx -> hash(ctx, key);
  printf("\nPos: %d\n", pos);

  //ctx -> print_key(key);
  //ctx -> print_val(value);

  void *save_key = (void *) malloc(size_key);
  void *save_val = (void *) malloc(size_val);

  memcpy(save_key, key, size_key);
  memcpy(save_val, value, size_val);

  Pair *pair = (Pair *)malloc(sizeof(Pair));
  pair -> key = save_key;
  pair -> val = save_val;

  printf("Pair %p\n", pair);

  int i = pos;
  while(i < ctx -> buckets && ctx -> hashmap[i] != NULL)
    i++;
  ctx -> hashmap[i] = pair;

}

void *search(Hashmap *ctx, void *key){
  int hash = ctx -> hash(ctx, key);
  Pair *node = ctx -> hashmap[hash];
  int i;
  for(i = 0; i < ctx -> buckets && node != NULL; i++){
    //ctx -> print_key(((Pair *)node -> ptr_value) -> key);
    if(ctx -> comparator(node -> key, key)){
      printf("\nSought %d times\n", i);
      return node -> val;
    }
    node = ctx -> hashmap[hash + i];
  }

  return NULL;
}

void delete(Hashmap *ctx, void *key){
  int hash = ctx -> hash(ctx, key);
  Pair *node = ctx -> hashmap[hash];

  int i;
  for(i = 0; i < ctx -> buckets && node != NULL; i++){
    //ctx -> print_key(((Pair *)node -> ptr_value) -> key);
    if(ctx -> comparator(node -> key, key))
      break;
    node = ctx -> hashmap[hash + i];
  }
  printf("GOT: %d ", hash + i);
  ctx -> print_key(node -> key);
  
  free(node -> key);
  free(node -> val);
  
  free(node);
  ctx -> hashmap[hash + i] = NULL;
  return;
}


void *free_hashmap(Hashmap *ctx){
  for(int i = 0; i < ctx -> buckets; i++){
    if(ctx -> hashmap[i] != NULL){
      free(ctx -> hashmap[i] -> key);
      free(ctx -> hashmap[i] -> val);
      free(ctx -> hashmap[i]);
    }
  }
  free(ctx -> hashmap);
  free(ctx);
  return NULL;
}

void printer_hashmap(Hashmap *ctx){
 for(int i = 0; i < ctx -> buckets; i++){
    printf("\nBucket %d\n", i);
    if(ctx -> hashmap[i] != NULL){
      printf("\t{ ");
      ctx -> print_key(ctx -> hashmap[i]  -> key);
      printf(": ");
      ctx -> print_val(ctx -> hashmap[i] -> val);
      printf("}, ");
    }
  }
}

void impl_printer_str(void *ptr){
  if(ptr != NULL)
    printf("%s", (char *)ptr);
}


Hashmap *hashmap_init(int m, hash_func h, comparator comparator, printer_impl printer_key, printer_impl printer_val){
  Hashmap *hashmap = (Hashmap *)malloc(sizeof(Hashmap));
  hashmap -> buckets = m;

  hashmap -> hashmap = (Pair **)malloc(sizeof(Pair *) * m);

  hashmap -> hash = h;
  hashmap -> insert = insert_hashmap;
  hashmap -> comparator = comparator;
  
  hashmap -> print_key = printer_key;
  hashmap -> print_val = printer_val;
  hashmap -> print = printer_hashmap;
  hashmap -> search = search;
  
  hashmap -> delete = delete;
  hashmap -> free = free_hashmap;


  
  for(int i = 0; i < m; i++){
    ///hashmap -> hashmap[i] = (Node *) malloc(sizeof(Node));
    hashmap -> hashmap[i] = NULL;

    printf("%d) %p\n", i, hashmap -> hashmap[i]);
    //print_list(hashmap -> hashmap[i], int_printer);
  }
  
  return hashmap;
}

