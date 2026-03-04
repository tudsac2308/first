#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year; 
    int price;
    int id;
    char name[20];
    char producer[20];
    char* description;
} Wine;

void read_description(Wine* w) {
    printf("Enter description: ");
    w->description = (char*)malloc(10 * sizeof(char)); 
    if (w->description == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    int  index = 0;
    int size = 10;
    char c;
    while((c = getchar()) != EOF) {
        if (c == '\n') {
            break; 
        }
        if (index >= size - 1) {
            size *= 2; 
            char* temp = (char*)realloc(w->description, size * sizeof(char));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(w->description);
                return;
            }
            w->description = temp;
        }
        w->description[index++] = c;
        w->description[index] = '\0';
    }
}

Wine* add_wine(Wine* w, int count) {

    static int id_counter = 1;
    
    Wine* temp = (Wine*)realloc(w, (count + 1) * sizeof(Wine)); 
    if (temp == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        return w;
    }

    w = temp;
    w[count].id = id_counter++;
    printf("Enter year: ");
    scanf("%d", &w[count].year);
    while (w[count].year < 1900 || w[count].year > 2026) {
        fprintf(stderr, "Invalid year. Please enter a year between 1900 and 2026.\n");
        scanf("%d", &w[count].year);
    }
    printf("Enter price: ");
    scanf("%d", &w[count].price);
    while (w[count].price < 0) {
        fprintf(stderr, "Invalid price. Please enter a non-negative price.\n");
        scanf("%d", &w[count].price);
    }
    printf("Enter name: ");
    scanf(" %[^\n]", w[count].name); // Read name with spaces
    while (strlen(w[count].name) == 0) {
        fprintf(stderr, "Invalid name. Please enter a non-empty name.\n");
        scanf("%[^\n]", w[count].name);
    }
    printf("Enter producer: ");
    scanf(" %[^\n]", w[count].producer); // Read producer with spaces
    while (strlen(w[count].producer) == 0) {
        fprintf(stderr, "Invalid producer. Please enter a non-empty producer.\n");
        scanf("%[^\n]", w[count].producer);
    }
    getchar();
    read_description(&w[count]);
    return w;
}

void show_wine(int index, Wine* w) {
    printf("ID: %08d\n", w[index].id);
    printf("Year: %d\n", w[index].year);
    printf("Price: %d\n", w[index].price);
    printf("Name: %s\n", w[index].name);
    printf("Producer: %s\n", w[index].producer);
    printf("Description: %s\n", w[index].description);
}

Wine* delete_wine(int index, Wine* w, int count) {
    free(w[index].description);
    for (int i = index; i < count - 1; i++) {
        w[i] = w[i + 1];
    }
    Wine* temp = (Wine*)realloc(w, (count - 1) * sizeof(Wine)); 
    if (temp == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        return w;
    }
    w = temp;
    return w;
}

void change_price(int index, Wine* w, int new_price) {
    w[index].price = new_price;
}

void file_writing(int count, Wine* Cellar) {
    FILE* file = fopen("wine_data.txt", "w");
    fprintf(file, "Wine Cellar Management System\n");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        return;
    }
    for (int i = 0; i < count; i++) {
    fprintf(file, "Year: %d\n", Cellar[i].year);
    fprintf(file, "Price: %d\n", Cellar[i].price);
    fprintf(file, "Name: %s\n", Cellar[i].name);
    fprintf(file, "Producer: %s\n", Cellar[i].producer);
    fprintf(file, "Description: %s\n", Cellar[i].description);
    }
    fprintf(file, "-----------------------\n");
    fclose(file);
}

void free_memory(int count, Wine* Cellar) {
    for (int i = 0; i < count; i++) {
        free(Cellar[i].description);
    }
    free(Cellar);
}

int compare_names(const void* a, const void* b) {
    const Wine* wineA = (const Wine*)a;
    const Wine* wineB = (const Wine*)b;
    return strcmp(wineA->name, wineB->name);
}

int main() {
    Wine* Cellar = (Wine*)malloc(sizeof(Wine));
    int count = 0;
    printf("Welcome to the wine cellar management system!\n");
    printf("If you want to add a wine, press 1\n");
    printf("If you want to show a wine, press 2\n");
    printf("If you want to delete a wine, press 3\n");
    printf("If you want to change the price of a wine, press 4\n");
    printf("If you want to show a wine by age, press 5\n");
    while(1) {
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
    Cellar = add_wine(Cellar, count);
    count++;
    break;
        case 2:
    printf("Enter the ID of the wine you want to show: ");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (Cellar[i].id == id) {
            show_wine(i, Cellar);
            break;
        }
    }
    break;
        case 3:
    printf("Enter the ID of the wine you want to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (Cellar[i].id == id) {
            Cellar = delete_wine(i, Cellar, count);
            count--;
            break;
        }
    }
    break;
        case 4:
    printf("Enter the ID of the wine you want to change the price of: ");
    scanf("%d", &id);
    printf("Enter the new price: ");
    int new_price;
    scanf("%d", &new_price);
    for (int i = 0; i < count; i++) {
        if (Cellar[i].id == id) {
            change_price(i, Cellar, new_price);
            break;
        }
    }
    break;
        case 5:
    printf("Enter the age of the wine you want to show: ");
    int age;
    scanf("%d", &age);
    for (int i = 0; i < count; i++) {
        if (2026 - Cellar[i].year >= age) {
            show_wine(i, Cellar);
        }
    }
    break;
    case 6:
    if (count > 1) {
        qsort(Cellar, count, sizeof(Wine), compare_names);
        printf("Wines sorted by name:\n");
    }
        else {
            printf("Not enough wines to sort.\n");
        }
    break;
    case 0:
    printf("Exiting the program...\n");
    file_writing(count, Cellar);
    free_memory(count, Cellar);
    return 0;
        default:    
    printf("Invalid choice\n");
    break;
    }
    }
    return 0;
}