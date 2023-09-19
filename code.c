#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define USER_DATA_FILE "userdata.txt"
#define MAX_TEXT_LENGTH 1000

// Structure to represent a user
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Function prototypes
size_t count_letters(char text[]);
size_t count_words(char text[]);
size_t count_sentences(char text[]);
void loadUserData();
void saveUserData();
void registerUser();
int authenticateUser();

// Array to store user data
User users[MAX_USERS];
int numUsers = 0;

int main(void) {
    char text[MAX_TEXT_LENGTH];
    char check;
    char fileName[100];
    FILE *file;
    int choice;
    int currentUserIndex = -1;

    // Load user data from the file when the program starts
    loadUserData();

    while (1) {
        if (currentUserIndex == -1) {
            printf("\n1. Login\n");
            printf("2. Register\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    currentUserIndex = authenticateUser();
                    if (currentUserIndex != -1) {
                        printf("Login successful! Welcome, %s.\n", users[currentUserIndex].username);
                    } else {
                        printf("Login failed. Invalid username or password.\n");
                    }
                    break;
                case 2:
                    registerUser();
                    break;
                case 3:
                    // Save user data to the file when exiting
                    saveUserData();
                    printf("Exiting...\n");
                    exit(0);
                    break; // Added break here
                default:
                    printf("Invalid choice. Please try again.\n");
                    break; // Added break here
            }
        } else {
            printf("Do you choose to give input text through command-line terminal or text file? (y/n): \n");
            scanf(" %c", &check); // Added a space before %c to skip leading whitespace

            if (check == 'y' || check == 'Y') {
                printf("Text: ");
                scanf(" %[^\n]s", text); // Corrected the format specifier
            } else {
                int i = 0;
                printf("Enter the name of the text file (including extension): \n");
                scanf("%s", fileName);

                file = fopen(fileName, "r");

                if (file == NULL) {
                    printf("Failed to open the file.\n");
                    return 1; // Exit with an error code
                }

                while ((i < MAX_TEXT_LENGTH - 1) && ((text[i] = fgetc(file)) != EOF)) {
                    i++;
                }
                text[i] = '\0';

                printf("Text from the file:\n%s\n", text);

                fclose(file);
            }

            size_t letters = count_letters(text);
            size_t words = count_words(text);
            size_t sentences = count_sentences(text);
            float l = letters / (float)words * 100.0;
            float s = sentences / (float)words * 100.0;

            int index = round(0.0588 * l - 0.296 * s - 15.8); // Coleman Liau index formula

            if (index < 1) {
                printf("Before Grade 1\n");
            } else if (index > 16) {
                printf("Grade 16+\n");
            } else {
                printf("Grade %i\n", index);
            }
        exit(0);
        }
    }
}

size_t count_letters(char text[]) {
    size_t letters = 0;

    for (size_t i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            letters++;
        }
    }
    return letters;
}

size_t count_words(char text[]) {
    size_t words = 1;
    int spaceFlag = 0;

    for (size_t i = 0; i < strlen(text); i++) {
        if (isspace(text[i])) {
            spaceFlag = 1;
        } else if (spaceFlag) {
            words++;
            spaceFlag = 0;
        }
    }
    return words;
}

size_t count_sentences(char text[]) {
    size_t sentences = 0;

    for (size_t i = 0; i < strlen(text); i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            sentences++;
        }
    }
    return sentences;
}

// Function to load user data from a file
void loadUserData() {
    FILE* file1 = fopen(USER_DATA_FILE, "r");
    if (file1 == NULL) {
        return; // No user data file exists yet
    }

    while (fscanf(file1, "%s %s", users[numUsers].username, users[numUsers].password) != EOF) {
        numUsers++;
    }

    fclose(file1);
}

// Function to save user data to a file
void saveUserData() {
    FILE* file = fopen(USER_DATA_FILE, "w");
    if (file == NULL) {
        printf("Error: Unable to save user data.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

// Function to register a new user
void registerUser() {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached. Cannot register more users.\n");
        return;
    }

    printf("Enter a username (up to %d characters): ", MAX_USERNAME_LENGTH - 1);
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    // Check if the username is already taken
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists. Please choose a different one.\n");
            return;
        }
    }

    printf("Enter a password (up to %d characters): ", MAX_PASSWORD_LENGTH - 1);
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    // Add the new user
    strcpy(users[numUsers].username, username);
    strcpy(users[numUsers].password, password);
    numUsers++;

    printf("Registration successful.\n");

    // Save user data to the file
    saveUserData();
}

// Function to authenticate a user
int authenticateUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // User authenticated, return user index
        }
    }

    return -1; // Authentication failed
}
