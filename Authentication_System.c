#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100      // Maximum number of users
#define USERNAME_LEN 50    // Maximum length of username
#define PASSWORD_LEN 50    // Maximum length of password
#define MAX_ATTEMPTS 3     // Maximum number of login attempts before shutdown

// Structure to store user credentials
typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

// Function to register a new user
void registerUser() {
    FILE *file = fopen("users.txt", "a"); // Open the file in append mode
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    User newUser;
    
    // Get username and password from the user
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password); // Note: In real systems, always hash the password before storing.

    // Save user credentials to the file
    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    fclose(file); // Close the file
    printf("Registration successful!\n");
}

// Function to log in an existing user
int loginUser() {
    FILE *file = fopen("users.txt", "r"); // Open the file in read mode
    if (!file) {
        printf("Error opening file! Please register first.\n");
        return 0;
    }

    User existingUser;
    char username[USERNAME_LEN], password[PASSWORD_LEN];
    int attempts = 0; // Counter for login attempts

    // Allow user to try logging in up to MAX_ATTEMPTS times
    while (attempts < MAX_ATTEMPTS) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        // Read the file line by line to check if the username and password match
        while (fscanf(file, "%s %s", existingUser.username, existingUser.password) != EOF) {
            if (strcmp(username, existingUser.username) == 0 && strcmp(password, existingUser.password) == 0) {
                fclose(file);
                printf("Login successful!\n");
                printf("\nThank you for using the system\n");
                return 1;
            }
        }

        // If login fails, increment the attempt counter
        fclose(file);
        attempts++;
        printf("Invalid username or password! Attempts %d/%d\n", attempts, MAX_ATTEMPTS);

        // If the user still has attempts left, reopen the file for another check
        if (attempts < MAX_ATTEMPTS) {
            file = fopen("users.txt", "r");
        }
    }

    // If the user fails all attempts, shutdown the system
    printf("\nToo many failed login attempts. System shutting down...\n");
    exit(0); // Exit the program
}

int main() {
    char choice[10];

    printf("\nAuthentication System\n");

    while (1) {
        // Print a separator line for better readability
        for (int i = 0; i < 40; i++) {
            printf("-");
        }
        printf("\nHey Buddy! Are you a new user? (Yes/No): ");
        scanf("%9s", choice); // Read user input

        // If the user is new, register first and then log in
        if (strcmp(choice, "Yes") == 0 || strcmp(choice, "yes") == 0 || 
            strcmp(choice, "Y") == 0 || strcmp(choice, "y") == 0) {
            printf("\nPlease Register First:\n");
            registerUser();
            printf("\nPlease login:\n");
            loginUser();
            break;
        }
        // If the user is not new, proceed to login
        else if (strcmp(choice, "No") == 0 || strcmp(choice, "no") == 0 || 
                 strcmp(choice, "N") == 0 || strcmp(choice, "n") == 0) {
            printf("Please Login:\n");
            loginUser();
            break;
        }
        // If the input is invalid, ask again
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
