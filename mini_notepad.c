#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTE_LEN 256
#define FILE_NAME "notes.txt"

typedef struct {
    char *text;
} Note;

// ... function declarations ...

void addNote();
void listNotes();
void deleteNote();
int loadNotes(Note **notes);

int main() {
    int choice;
    while (1) {
        printf("\n--- Mini Notepad --- yusffa\n");
        printf("1. Not Yaz\n");
        printf("2. Notlari Listele\n");
        printf("3. Not Sil\n");
        printf("4. Cikis\n");
        printf("Yapmak istediğiniz seyi seciniz: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                addNote();
                break;
            case 2:
                listNotes();
                break;
            case 3:
                deleteNote();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// ... existing code ...

void addNote() {
    char buffer[MAX_NOTE_LEN];
    printf("Enter your note: ");
    fgets(buffer, MAX_NOTE_LEN, stdin);

    if (strlen(buffer) <= 1) {
        printf("Bos not eklenemez!\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s", buffer);
    fclose(file);
    printf("Note added.\n");
}

void listNotes() {
    Note *notes = NULL;
    int count = loadNotes(&notes);
    if (count == 0) {
        printf("No notes found.\n");
        return;
    }
    printf("\n--- Notes ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s", i + 1, notes[i].text);
    }
    // Free memory
    for (int i = 0; i < count; i++) {
        free(notes[i].text);
    }
    free(notes);
}

void deleteNote() {
    Note *notes = NULL;
    int count = loadNotes(&notes);
    if (count == 0) {
        printf("No notes to delete.\n");
        return;
    }
    printf("\n--- Notes ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s", i + 1, notes[i].text);
    }
    printf("Enter note number to delete: ");
    int del;
    scanf("%d", &del);
    getchar(); // consume newline

    if (del < 1 || del > count) {
        printf("Invalid note number.\n");
        // Free memory
        for (int i = 0; i < count; i++) {
            free(notes[i].text);
        }
        free(notes);
        return;
    }

    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error opening file!\n");
        // Free memory
        for (int i = 0; i < count; i++) {
            free(notes[i].text);
        }
        free(notes);
        return;
    }
    for (int i = 0; i < count; i++) {
        if (i != del - 1) {
            fprintf(file, "%s", notes[i].text);
        }
    }
    fclose(file);
    printf("Note deleted.\n");

    // Free memory
    for (int i = 0; i < count; i++) {
        free(notes[i].text);
    }
    free(notes);
}

int loadNotes(Note **notes) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        *notes = NULL;
        return 0;
    }
    int count = 0;
    char buffer[MAX_NOTE_LEN];
    Note *temp = NULL;
    while (fgets(buffer, MAX_NOTE_LEN, file)) {
        temp = realloc(*notes, sizeof(Note) * (count + 1));
        if (!temp) {
            printf("Memory allocation error!\n");
            break;
        }
        *notes = temp;
        (*notes)[count].text = malloc(strlen(buffer) + 1);
        strcpy((*notes)[count].text, buffer);
        count++;
    }
    fclose(file);
    return count;
}