#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit) // O(2*n) -> O(n)
{
    HashTable *ht = create_hash_table(16);
    
    Answer *answer = malloc(sizeof(Answer));
    
    
    printf("****** limit: %d\n", limit);
    
    // Insert all weights into a hash table (O(n))
    for (int i = 0; i < length; i++) {
        hash_table_insert(ht, weights[i], i);
        printf("insert key: %d, value: %d\n", weights[i], i);
    }
    
    // Go through weights and check if there is a matching weight that sums up to limit (O(n))
    for (int i = 0; i < length; i++) {
        int weight = weights[i];
        int currWeightIndex = hash_table_retrieve(ht, weights[i]);
        int *matchingWeightIndex = hash_table_retrieve(ht, limit-weight);
        
        // If a matching weight exists in the hash table then return it
        if (matchingWeightIndex != -1) {
            if (i > matchingWeightIndex) {
                answer->index_1 = i;
                answer->index_2 = matchingWeightIndex;
                return answer;
            } else {
                answer->index_1 = matchingWeightIndex;
                answer->index_2 = i;
                return answer;
            }
        }
        
    }
    
    return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif
