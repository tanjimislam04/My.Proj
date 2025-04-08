# Authentication System in C

A simple authentication system written in C that supports user registration and login functionality. The program allows a new user to register, then logs in with their credentials. If the login fails multiple times, the system shuts down. This system stores user credentials in a text file (`users.txt`).

## Features
- User registration with a username and password.
- Login system with a maximum of 3 attempts before the system shuts down.
- User credentials are stored in a plain text file (`users.txt`).

## Installation

1. Clone this repository:
   ```sh
   git clone https://github.com/your-username/authentication-system.git
   cd authentication-system

2. Compile the C program using GCC:
   ```sh
   gcc authentication_system.c -o auth_system
   
3. Run the program:
      ```sh
      ./auth_system

# Usage

## Main Menu
  When you run the program, it will ask if you are a new user: 
  ```
  ----------------------------------------
Hey Buddy! Are you a new user? (Yes/No):
```
- If you are a new user, you will be prompted to register:
  ```
  Please Register First:
  Enter username: <your_username>
  Enter password: <your_password>
  Registration successful!
  Please login:
  Enter username: <your_username>
  Enter password: <your_password>
  Login successful!
  Thank you for using the system
  ```
- If you are an existing user, you will log in:
    ```
    Please Login:
    Enter username: <your_username>
    Enter password: <your_password>
    Login successful!
    Thank you for using the system
    ```
# Invalid Login Attempt
  If you fail to log in, you will be prompted up to 3 times:
  ```
Invalid username or password! Attempts 1/3
Invalid username or password! Attempts 2/3
Invalid username or password! Attempts 3/3
Too many failed login attempts. System shutting down...
```
# users.txt File Format
  The file stores the registered user credentials in the following format:
  ```
username1 password1
username2 password2
```
Each line contains a username and its corresponding password.
# Code Flow

1. **Register User:**

  - The program will prompt for a username and password, then store these in a file users.txt.

2. **Login User:**

- The program will ask for a username and password, then check if these match any of the stored credentials in the users.txt file.

- The user has up to 3 attempts to enter correct credentials. If all attempts fail, the program will exit.

3. **Shutdown on Multiple Failed Attempts:**

- After 3 failed login attempts, the system will display an error message and shut down the program.

# License

This project is open-source and available under the MIT License.
