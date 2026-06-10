#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CANVAS_WIDTH 100
#define CANVAS_HEIGHT 40

/**
 * Input Validation Module
 * Validates all user inputs for the graphics editor
 */

// Validate integer input within range
int validate_integer(int value, int min, int max, const char* field_name) {
    if (value < min || value > max) {
        printf("Error: %s must be between %d and %d. You entered: %d\n", 
               field_name, min, max, value);
        return 0;
    }
    return 1;
}

// Validate coordinate point
int validate_point(int x, int y, const char* point_name) {
    if (!validate_integer(x, 0, CANVAS_WIDTH - 1, "X coordinate")) {
        printf("  Invalid %s X coordinate\n", point_name);
        return 0;
    }
    if (!validate_integer(y, 0, CANVAS_HEIGHT - 1, "Y coordinate")) {
        printf("  Invalid %s Y coordinate\n", point_name);
        return 0;
    }
    return 1;
}

// Validate two points form a valid line/shape
int validate_different_points(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        printf("Error: Start and end points must be different!\n");
        return 0;
    }
    return 1;
}

// Validate circle parameters
int validate_circle(int cx, int cy, int radius) {
    if (!validate_point(cx, cy, "Center")) {
        return 0;
    }

    if (radius <= 0) {
        printf("Error: Radius must be positive. You entered: %d\n", radius);
        return 0;
    }

    if (radius > CANVAS_WIDTH / 2 && radius > CANVAS_HEIGHT / 2) {
        printf("Warning: Circle radius (%d) may exceed canvas boundaries.\n", radius);
        printf("Canvas is %d x %d. Continue anyway? (y/n): ", CANVAS_WIDTH, CANVAS_HEIGHT);
        char response = getchar();
        getchar(); // consume newline
        return (response == 'y' || response == 'Y');
    }

    return 1;
}

// Validate triangle points
int validate_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (!validate_point(x1, y1, "Point 1")) return 0;
    if (!validate_point(x2, y2, "Point 2")) return 0;
    if (!validate_point(x3, y3, "Point 3")) return 0;

    // Check if all three points are different
    if ((x1 == x2 && y1 == y2) || (x2 == x3 && y2 == y3) || (x1 == x3 && y1 == y3)) {
        printf("Error: Triangle points must be different!\n");
        return 0;
    }

    // Check if points are collinear (form a line, not a triangle)
    int area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    if (area == 0) {
        printf("Warning: Points are collinear (form a line). Create triangle anyway? (y/n): ");
        char response = getchar();
        getchar(); // consume newline
        return (response == 'y' || response == 'Y');
    }

    return 1;
}

// Validate character input
int validate_character(char ch) {
    if (ch < 32 || ch > 126) {
        printf("Error: Character must be printable ASCII!\n");
        return 0;
    }
    return 1;
}

// Validate object index
int validate_object_index(int index, int max_objects) {
    if (index < 0 || index >= max_objects) {
        printf("Error: Object index must be between 0 and %d\n", max_objects - 1);
        return 0;
    }
    return 1;
}

// Validate menu choice
int validate_menu_choice(int choice) {
    if (choice < 0 || choice > 10) {
        printf("Error: Please enter a valid choice (0-10)\n");
        return 0;
    }
    return 1;
}

// Safe integer input with error handling
int get_safe_integer(const char* prompt, int min, int max) {
    int value;
    int result;
    char buffer[256];

    while (1) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error: Input failed. Please try again.\n");
            continue;
        }

        result = sscanf(buffer, "%d", &value);
        
        if (result != 1) {
            printf("Error: Please enter a valid integer.\n");
            continue;
        }

        if (validate_integer(value, min, max, "Input")) {
            return value;
        }
    }
}

// Safe coordinate input
int get_safe_coordinates(int* x, int* y, const char* point_name) {
    char buffer[256];
    int result;

    while (1) {
        printf("Enter %s (x y): ", point_name);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error: Input failed. Please try again.\n");
            continue;
        }

        result = sscanf(buffer, "%d %d", x, y);
        
        if (result != 2) {
            printf("Error: Please enter two integers separated by space.\n");
            continue;
        }

        if (validate_point(*x, *y, point_name)) {
            return 1;
        }
    }
}

// Safe character input
char get_safe_character(const char* prompt) {
    char buffer[256];
    char ch;

    while (1) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error: Input failed. Please try again.\n");
            continue;
        }

        // Skip whitespace and get first non-whitespace character
        int i = 0;
        while (buffer[i] != '\0' && (buffer[i] == ' ' || buffer[i] == '\t')) {
            i++;
        }

        if (buffer[i] == '\0' || buffer[i] == '\n') {
            return '*'; // Default character
        }

        ch = buffer[i];

        if (validate_character(ch)) {
            return ch;
        }
    }
}

// Print input guidelines
void print_input_guidelines() {
    printf("\n========== INPUT GUIDELINES ==========\n");
    printf("Coordinates:\n");
    printf("  - X range: 0 to %d\n", CANVAS_WIDTH - 1);
    printf("  - Y range: 0 to %d\n", CANVAS_HEIGHT - 1);
    printf("\nCharacters:\n");
    printf("  - Use printable ASCII characters\n");
    printf("  - Examples: * _ + - # @ etc.\n");
    printf("  - Default: * (press Enter for default)\n");
    printf("========================================\n\n");
}
