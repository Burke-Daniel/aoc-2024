#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <map>

#define MAX_LEN (4096U)

int compare_int(const void *num1, const void *num2) {
    return *(int*)num1 > *(int*)num2;
}

int main(void) {
    FILE *input_file = fopen("day1_input.txt", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
    }

    int list1[MAX_LEN], list2[MAX_LEN], distances[MAX_LEN];

    // Get all the input into lists
    
    int num1, num2;
    int i = 0;
    while (fscanf(input_file, "%d   %d", &num1, &num2) != EOF) {
        printf("Num1: %d, Num2: %d\n", num1, num2);
        list1[i] = num1;
        list2[i] = num2;
        i++;
    }

    printf("\nPart one:\n");

    // Sort the lists from least to greatest

    qsort(&list1[0], i, sizeof(int), compare_int);
    qsort(&list2[0], i, sizeof(int), compare_int);

    // Get the distance between each element
    // and get the total distance
    size_t total_distance = 0;

    for (size_t j = 0; j < i; j++) {
        printf("Num1: %d, Num2: %d\n", list1[j], list2[j]);
        printf("Distance: %d\n", abs(list1[j] - list2[j]));

        distances[j] = abs(list1[j] - list2[j]);
        total_distance += distances[j];
    }

    printf("\nTotal distance: %lu\n", total_distance);

    printf("\nPart two:\n");

    // Naive solution is to walk the list for every number
    // improved solution is to build a map of the second
    // list and then walk the first list and add up
    
    // Very naive map where index is the number and value is the frequency 
    std::map<int, size_t> frequency_map;

    for (size_t j = 0; j < i; j++) {
        frequency_map[list2[j]] += 1;
        printf("Saw number %d %lu times\n", list2[j], frequency_map[list2[j]]);
    }

    size_t similarity_score = 0;

    for (size_t j = 0; j < i; j++) {
        similarity_score += list1[j] * frequency_map[list1[j]];
    }

    printf("\nSimilarity score: %lu\n", similarity_score);

    return 0;
}
