# Lexile-Luminosity-A-Text-Comprehension-Grade-Level-Estimator

This GitHub repository contains a program that calculates the approximate grade level needed to comprehend some text. The program allows input from the command-line terminal or a text file.

## Usage

To use the program, follow these steps:

1. Clone the repository to your local machine:

   ```
   git clone <repository_url>
   ```

2. Compile the program:

   ```
   gcc -o text_comprehension text_comprehension.c
   ```

3. Run the program:

   ```
   ./text_comprehension
   ```

## Program Overview

The program is written in C and performs the following tasks:

- User registration and authentication.
- Accepts input text either from the command-line terminal or a text file.
- Analyzes the input text to calculate the grade level required for comprehension using the Coleman-Liau index formula.

## Program Structure

The program consists of several components:

- `count_letters`: Counts the number of letters in the text.
- `count_words`: Counts the number of words in the text.
- `count_sentences`: Counts the number of sentences in the text.
- `loadUserData`: Loads user data from a file.
- `saveUserData`: Saves user data to a file.
- `registerUser`: Allows users to register with a username and password.
- `authenticateUser`: Authenticates users based on their credentials.
- Main program loop: Handles user login, registration, and text analysis.
