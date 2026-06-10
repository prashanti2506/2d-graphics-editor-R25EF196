#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics_editor.c"

void display_menu() {
    printf("2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", CANVAS_WIDTH, CANVAS_HEIGHT);
    printf("1. Add object\n");
    printf("2. Delete object\n");
    printf("3. Modify object\n");
    printf("4. Display picture\n");
    printf("5. List objects\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

int main() {
    Canvas* canvas = create_canvas();
    int choice;
    int x1, y1, x2, y2, x3, y3, radius, index;
    int shape_type;

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1:  // Add object
                printf("\nChoose shape type:\n");
                printf("1. Line\n");
                printf("2. Rectangle\n");
                printf("3. Circle\n");
                printf("4. Triangle\n");
                printf("Enter shape type: ");
                scanf("%d", &shape_type);
                getchar();

                if (shape_type == 1) {  // Line
                    printf("Enter x1 y1 x2 y2: ");
                    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                    add_object(canvas, LINE, x1, y1, x2, y2, 0, 0, '*');
                } else if (shape_type == 2) {  // Rectangle
                    printf("Enter top-left x y and bottom-right x y: ");
                    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                    add_object(canvas, RECTANGLE, x1, y1, x2, y2, 0, 0, '*');
                } else if (shape_type == 3) {  // Circle
                    printf("Enter center x y and radius: ");
                    scanf("%d %d %d", &x1, &y1, &radius);
                    add_object(canvas, CIRCLE, x1, y1, radius, 0, 0, 0, '*');
                } else if (shape_type == 4) {  // Triangle
                    printf("Enter x1 y1 x2 y2 x3 y3: ");
                    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
                    add_object(canvas, TRIANGLE, x1, y1, x2, y2, x3, y3, '*');
                }
                getchar();  // Consume newline
                printf("\n");
                break;

            case 2:  // Delete object
                printf("Enter object index to delete: ");
                scanf("%d", &index);
                delete_object(canvas, index);
                printf("\n");
                getchar();
                break;

            case 3:  // Modify object
                printf("Enter object index to modify: ");
                scanf("%d", &index);
                
                if (index >= 0 && index < canvas->object_count && canvas->objects[index].active) {
                    Shape* obj = &canvas->objects[index];
                    
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
                } else {
                    printf("Invalid object index!\n");
                }
                getchar();
                printf("\n");
                break;

            case 4:  // Display Canvas
                display_canvas(canvas);
                break;

            case 5:  // List Objects
                list_objects(canvas);
                break;

            case 0:  // Exit
                printf("Goodbye.\n");
                free_canvas(canvas);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n\n");
        }
    }

    return 0;
}
