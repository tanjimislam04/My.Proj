// first you have to login with username and password "admin" and "admin123"
// if you don't have password you have to register after that
// setup election and register voter with age check (18+ eligibility) after that 
// voter can vote 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 10       // Maximum number of candidates
#define MAX_VOTERS 100 // Maximum number of voters

// -------------------------
// Structure Definitions
// -------------------------

// Candidate structure stores the name and tally of votes.
typedef struct {
    char name[50];
    int votes;
} Candidate;

// Voter structure stores the name, password, age, and a flag to indicate whether they have voted.
typedef struct {
    char name[50];
    char password[50];
    int age;
    int voted; // 0 if not voted, 1 if voted
} Voter;

// -------------------------
// Global Variables
// -------------------------

Candidate candidates[MAX_C];
int candidateCount = 0;

Voter voters[MAX_VOTERS];
int voterCount = 0;

// Officer credentials (default: "admin"/"admin123")
char officerUsername[50] = "admin";
char officerPassword[50] = "admin123";
// A flag to indicate if a custom officer was registered (optional)
int officerRegistered = 0;

// -------------------------
// Function Prototypes
// -------------------------

void officerMenu(void);
void voterMenu(void);
void setupElection(void);
void registerVoters(void);
void showResults(void);
int officerLogin(void);
void officerRegistration(void);

// -------------------------
// Officer Functions
// -------------------------

// The officer menu first logs in the officer (using default credentials or new ones if registered).
// If login fails, the officer is prompted to register a new account.
// Once logged in, the officer can set up the election (enter candidates) and register voters.
void officerMenu(void) {
    int loginSuccess = officerLogin();
    if (!loginSuccess) {
        printf("Officer login failed.\nDo you want to register as officer? (Enter 1 for Yes, 0 for No): ");
        int regChoice;
        scanf("%d", &regChoice);
        if (regChoice == 1) {
            officerRegistration();
            // After registration, try to log in again.
            loginSuccess = officerLogin();
            if (!loginSuccess) {
                printf("Login failed after registration. Returning to main menu.\n");
                return;
            }
        } else {
            return;
        }
    }
    
    int opChoice;
    while (1) {
        printf("\n---- Officer Sub-Menu ----\n");
        printf("1. Setup Election (Register Candidates)\n");
        printf("2. Register Voters\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &opChoice);
        
        if (opChoice == 1) {
            setupElection();
        } else if (opChoice == 2) {
            registerVoters();
        } else if (opChoice == 3) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

// Officer login: checks the entered username and password against the stored credentials.
int officerLogin(void) {
    char uname[50], pass[50];
    printf("\n--- Officer Login ---\n");
    printf("Enter officer username: ");
    scanf("%s", uname);
    printf("Enter officer password: ");
    scanf("%s", pass);
    
    if (strcmp(uname, officerUsername) == 0 && strcmp(pass, officerPassword) == 0) {
        printf("Officer login successful.\n");
        return 1;
    }
    printf("Invalid officer credentials.\n");
    return 0;
}

// Officer registration: allows the officer to change the default credentials.
void officerRegistration(void) {
    printf("\n--- Officer Registration ---\n");
    printf("Enter new officer username: ");
    scanf("%s", officerUsername);
    printf("Enter new officer password: ");
    scanf("%s", officerPassword);
    officerRegistered = 1;
    printf("Officer registration successful. Use these credentials to login.\n");
}

// Election setup: the officer enters the number of candidates and their names.
void setupElection(void) {
    printf("\n--- Election Setup ---\n");
    printf("Enter number of candidates (max %d): ", MAX_C);
    scanf("%d", &candidateCount);
    
    if (candidateCount < 1 || candidateCount > MAX_C) {
        printf("Invalid number of candidates. Election setup aborted.\n");
        candidateCount = 0;
        return;
    }
    
    for (int i = 0; i < candidateCount; i++) {
        printf("Enter name for candidate %d: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
    }
    printf("Election setup complete.\n");
}

// Register voters: officer enters how many voters to add, then for each voter, their name, password, and age.
// Voters under 18 are rejected.
void registerVoters(void) {
    int num;
    printf("\n--- Voter Registration ---\n");
    printf("Enter number of voters to register: ");
    scanf("%d", &num);
    
    for (int i = 0; i < num; i++) {
        if (voterCount >= MAX_VOTERS) {
            printf("Voter registration limit reached.\n");
            break;
        }
        printf("Enter name for voter %d: ", voterCount + 1);
        scanf("%s", voters[voterCount].name);
        printf("Enter password for voter %d: ", voterCount + 1);
        scanf("%s", voters[voterCount].password);
        printf("Enter age for voter %d: ", voterCount + 1);
        scanf("%d", &voters[voterCount].age);
        
        if (voters[voterCount].age < 18) {
            printf("Voter must be at least 18 years old. %s not registered.\n", voters[voterCount].name);
        } else {
            voters[voterCount].voted = 0;
            printf("Voter %s registered successfully.\n", voters[voterCount].name);
            voterCount++;
        }
    }
}

// -------------------------
// Voter Functions
// -------------------------

// Voter menu: the voter logs in using the registered name and password.
// If the login is successful and the voter has not yet voted, the candidate list is displayed for voting.
void voterMenu(void) {
    char name[50], pass[50];
    int foundIndex = -1;
    
    printf("\n--- Voter Login ---\n");
    printf("Enter voter name: ");
    scanf("%s", name);
    printf("Enter voter password: ");
    scanf("%s", pass);
    
    // Search the voters array for a match.
    for (int i = 0; i < voterCount; i++) {
        if (strcmp(name, voters[i].name) == 0 && strcmp(pass, voters[i].password) == 0) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("Invalid voter credentials.\n");
        return;
    }
    
    // Check if the voter has already voted.
    if (voters[foundIndex].voted == 1) {
        printf("You have already cast your vote.\n");
        return;
    }
    
    // (The age check is precautionary — only eligible voters should have been registered.)
    if (voters[foundIndex].age < 18) {
        printf("You are not eligible to vote due to age restrictions.\n");
        return;
    }
    
    // Voting process.
    if (candidateCount == 0) {
        printf("Election is not set up yet.\n");
        return;
    }
    
    printf("\n--- Voting ---\n");
    printf("Candidates:\n");
    for (int j = 0; j < candidateCount; j++) {
        printf("%d. %s\n", j + 1, candidates[j].name);
    }
    
    int choice;
    printf("Enter your vote (candidate number): ");
    scanf("%d", &choice);
    
    if (choice < 1 || choice > candidateCount) {
        printf("Invalid candidate choice.\n");
        return;
    }
    
    // Record the vote.
    candidates[choice - 1].votes++;
    voters[foundIndex].voted = 1;
    printf("Your vote for %s has been recorded. Thank you!\n", candidates[choice - 1].name);
}

// -------------------------
// Results Function
// -------------------------

// showResults() prints the vote totals for each candidate.
// In addition, it shows the total number of registered voters, how many have voted, and how many have not.
void showResults(void) {
    printf("\n=== Election Results ===\n");
    
    // Display candidate vote counts.
    if (candidateCount == 0) {
        printf("Election not set up or no candidates registered.\n");
    } else {
        for (int i = 0; i < candidateCount; i++) {
            printf("Candidate %s received %d votes.\n", candidates[i].name, candidates[i].votes);
        }
    }
    
    // Count voting statistics.
    int votedCount = 0, notVotedCount = 0;
    for (int i = 0; i < voterCount; i++) {
        if (voters[i].voted == 1)
            votedCount++;
        else
            notVotedCount++;
    }
    
    printf("\nTotal registered voters: %d\n", voterCount);
    printf("Voters who have voted: %d\n", votedCount);
    printf("Voters who have not voted: %d\n", notVotedCount);
    
    // Determine the winner.
    if (candidateCount > 0) {
        int maxVotes = -1, winnerIndex = -1, tie = 0;
        for (int i = 0; i < candidateCount; i++) {
            if (candidates[i].votes > maxVotes) {
                maxVotes = candidates[i].votes;
                winnerIndex = i;
                tie = 0;
            } else if (candidates[i].votes == maxVotes) {
                tie = 1;
            }
        }
    
        if (maxVotes <= 0) {
            printf("No votes were cast.\n");
        } else if (tie) {
            printf("There is a tie between candidates.\n");
        } else {
            printf("The winner is %s with %d votes.\n", candidates[winnerIndex].name, candidates[winnerIndex].votes);
        }
    }
}

// -------------------------
// Main Function (Main Menu)
// -------------------------

int main(void) {
    int choice;
    
    while (1) {
        printf("\n==== Voting System Main Menu ====\n");
        printf("1. Officer\n");
        printf("2. Voter\n");
        printf("3. Show Results\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input.
            while (getchar() != '\n');
            continue;
        }
        
        switch(choice) {
            case 1:
                officerMenu();
                break;
            case 2:
                voterMenu();
                break;
            case 3:
                showResults();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    
    return 0;
}