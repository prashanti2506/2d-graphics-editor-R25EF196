#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics_editor.c"

void display_menu() {
    printf("\n========== 2D GRAPHICS EDITOR ==========\n");
    printf("1. Draw Line\n");
    printf("2. Draw Rectangle\n");
    printf("3. Draw Circle\n");
    printf("4. Draw Triangle\n");
    printf("5. Delete Object\n");
    printf("6. Modify Object\n");
    printf("7. Display Canvas\n");
    printf("8. Clear Canvas\n");
    printf("9. List Objects\n");
    printf("0. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

void list_objects(Canvas* canvas) {
    printf("\n--- Objects List ---\n");
    if (canvas->object_count == 0) {
        printf("No objects on canvas.\n");
        return;
    }
    
    for (int i = 0; i < canvas->object_count; i++) {
        if (!canvas->objects[i].active) continue;
        
        Shape* obj = &canvas->objects[i];
        printf("Object %d: ", i);
        
        switch (obj->type) {
            case LINE:
                printf("LINE from (%d,%d) to (%d,%d), char='%c'\n", 
                       obj->x1, obj->y1, obj->x2, obj->y2, obj->character);
                break;
            case RECTANGLE:
                printf("RECTANGLE from (%d,%d) to (%d,%d), char='%c'\n", 
                       obj->x1, obj->y1, obj->x2, obj->y2, obj->character);
                break;
            case CIRCLE:
                printf("CIRCLE center=(%d,%d), radius=%d, char='%c'\n", 
                       obj->x1, obj->y1, obj->x2, obj->character);
                break;
            case TRIANGLE:
                printf("TRIANGLE (%d,%d)-(%d,%d)-(%d,%d), char='%c'\n", 
                       obj->x1, obj->y1, obj->x2, obj->y2, obj->x3, obj->y3, obj->character);
                break;
        }
    }
    printf("-------------------\n");
}

int main() {
    Canvas* canvas = create_canvas();
    int choice;
    int x1, y1, x2, y2, x3, y3, radius, index;
    char character;

    printf("\n*** Welcome to 2D Graphics Editor ***\n");
    printf("Canvas size: %d x %d\n", CANVAS_WIDTH, CANVAS_HEIGHT);

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1:  // Draw Line
                printf("\nEnter starting point (x1 y1): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter ending point (x2 y2): ");
                scanf("%d %d", &x2, &y2);
                printf("Enter character (default '*'): ");
                character = getchar();
                if (character == '\n') character = '*';
                else getchar();  // Consume newline
                
                add_object(canvas, LINE, x1, y1, x2, y2, 0, 0, character);
                printf("Line added successfully!\n");
                break;

            case 2:  // Draw Rectangle
                printf("\nEnter top-left point (x1 y1): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter bottom-right point (x2 y2): ");
                scanf("%d %d", &x2, &y2);
                printf("Enter character (default '*'): ");
                character = getchar();
                if (character == '\n') character = '*';
                else getchar();  // Consume newline
                
                add_object(canvas, RECTANGLE, x1, y1, x2, y2, 0, 0, character);
                printf("Rectangle added successfully!\n");
                break;

            case 3:  // Draw Circle
                printf("\nEnter center (cx cy): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter radius: ");
                scanf("%d", &radius);
                printf("Enter character (default '*'): ");
                character = getchar();
                if (character == '\n') character = '*';
                else getchar();  // Consume newline
                
                add_object(canvas, CIRCLE, x1, y1, radius, 0, 0, 0, character);
                printf("Circle added successfully!\n");
                break;

            case 4:  // Draw Triangle
                printf("\nEnter first point (x1 y1): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter second point (x2 y2): ");
                scanf("%d %d", &x2, &y2);
                printf("Enter third point (x3 y3): ");
                scanf("%d %d", &x3, &y3);
                printf("Enter character (default '*'): ");
                character = getchar();
                if (character == '\n') character = '*';
                else getchar();  // Consume newline
                
                add_object(canvas, TRIANGLE, x1, y1, x2, y2, x3, y3, character);
                printf("Triangle added successfully!\n");
                break;

            case 5:  // Delete Object
                list_objects(canvas);
                printf("Enter object index to delete: ");
                scanf("%d", &index);
                delete_object(canvas, index);
                printf("Object deleted successfully!\n");
                break;

            case 6:  // Modify Object
                list_objects(canvas);
                printf("Enter object index to modify: ");
                scanf("%d", &index);
                
                if (index >= 0 && index < canvas->object_count && canvas->objects[index].active) {
                    Shape* obj = &canvas->objects[index];
                    printf("Enter new coordinates based on shape type:\n");
                    
                    if (obj->type == LINE) {
                        printf("Enter new line points (x1 y1 x2 y2): ");
                        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                        modify_object(canvas, index, x1, y1, x2, y2, 0, 0);
                    } else if (obj->type == RECTANGLE) {
                        printf("Enter new rectangle corners (x1 y1 x2 y2): ");
                        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                        modify_object(canvas, index, x1, y1, x2, y2, 0, 0);
                    } else if (obj->type == CIRCLE) {
                        printf("Enter new circle (cx cy radius): ");
                        scanf("%d %d %d", &x1, &y1, &radius);
                        modify_object(canvas, index, x1, y1, radius, 0, 0, 0);
                    } else if (obj->type == TRIANGLE) {
                        printf("Enter new triangle points (x1 y1 x2 y2 x3 y3): ");
                        scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
                        modify_object(canvas, index, x1, y1, x2, y2, x3, y3);
                    }
                    printf("Object modified successfully!\n");
                } else {
                    printf("Invalid object index!\n");
                }
                break;

            case 7:  // Display Canvas
                display_canvas(canvas);
                break;

            case 8:  // Clear Canvas
                clear_canvas(canvas);
                canvas->object_count = 0;
                memset(canvas->objects, 0, sizeof(canvas->objects));
                printf("Canvas cleared!\n");
                break;

            case 9:  // List Objects
                list_objects(canvas);
                break;

            case 0:  // Exit
                printf("\nThank you for using 2D Graphics Editor!\n");
                free_canvas(canvas);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
