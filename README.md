# SSC CGL Quiz CLI

A simple, lightweight terminal tool written in C to practice SSC CGL General Awareness previous year questions.

## Features
- Interactive question-and-answer format.
- Automatic scoring and instant feedback.
- Highlights correct and incorrect options in color.
- Supports multi-line explanations and text formatting.
- Reads questions directly from custom plain-text files.

## How to Compile and Run (Linux)

1. Ensure GCC is installed on your system.
2. Compile the source code:
   gcc -Wall -Wextra quiz_file.c -o quiz_file
3. Run with default sample questions:
   ./quiz_file
4. Or specify a custom question file:
   ./quiz_file custom_questions.txt
