#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Print a string, turning pairs of '*' into bold terminal text
void print_formatted(const char *str) {
    int bold = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*') {
            if (!bold) {
                printf("\033[1m"); // Turn ON bold
                bold = 1;
            } else {
                printf("\033[0m"); // Turn OFF bold
                bold = 0;
            }
        } else {
            putchar(str[i]);
        }
    }
    if (bold) {
        printf("\033[0m"); // Safety reset
    }
}

void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]) {
    // If a filename is passed in the terminal, use it; otherwise default to "questions.txt"
    const char *filename = (argc > 1) ? argv[1] : "questions.txt";

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Could not open file '%s'!\n", filename);
        return 1;
    }

    char line[2048];
    char user_choice = '\0';
    int q_num = 1; // Tracks question numbers automatically
    int score = 0;

    printf("\033[1m==========================================\033[0m\n");
    printf("\033[1m   SSC CGL GENERAL AWARENESS PRACTICE     \033[0m\n");
    printf("\033[1m==========================================\033[0m\n\n");

    while (fgets(line, sizeof(line), fp)) {
        // Automatically replace leading "Q." with "Q1.", "Q2.", etc.
        if (strncmp(line, "Q.", 2) == 0) {
            printf("\033[1mQ%d.\033[0m", q_num);
            print_formatted(line + 2); // Print the rest of the question text
            continue;
        }

        // Delimiter between Question and Answer
        if (strncmp(line, "---", 3) == 0) {
            printf("\nYour Option (a/b/c/d): ");
            if (scanf(" %c", &user_choice) == 1) {
                clear_input();
            }
            printf("\n------------------------------------------\n");
            continue;
        }

        // Detect the answer line: e.g. "Ans. (b)"
        if (strncmp(line, "Ans.", 4) == 0) {
            char correct_opt = '\0';
            for (int i = 4; line[i] != '\0'; i++) {
                if (isalpha((unsigned char)line[i])) {
                    correct_opt = tolower((unsigned char)line[i]);
                    break;
                }
            }

            if (tolower((unsigned char)user_choice) == correct_opt) {
                printf("\033[1;32m[✓ Correct Answer]\033[0m\n");
                score++;
            } else {
                printf("\033[1;31m[✗ Incorrect Answer]\033[0m\n");
            }
        }

        // Delimiter marking the end of a question
        if (strncmp(line, "===", 3) == 0) {
            printf("------------------------------------------\n");
            printf("Press Enter for next question...");
            getchar();
            printf("\n\n");
            q_num++; // Increment counter for the next question
            continue;
        }

        print_formatted(line);
    }

    fclose(fp);
    printf("\nAll %d questions completed.\n", q_num - 1);
    printf("\033[1mYour Final Score: %d / %d\033[0m\n", score, q_num - 1);
    return 0;
}
