#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CANVAS_WIDTH 80
#define CANVAS_HEIGHT 24
#define MAX_OBJECTS 50

// Shape types
typedef enum {
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

// Object structure
typedef struct {
    ShapeType type;
    int x1, y1, x2, y2, x3, y3;
    char character;
    int active;
} Shape;

// Canvas structure
typedef struct {
    char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    Shape objects[MAX_OBJECTS];
    int object_count;
} Canvas;

// Function declarations
Canvas* create_canvas();
void clear_canvas(Canvas* canvas);
void draw_line(Canvas* canvas, int x1, int y1, int x2, int y2, char ch);
void draw_rectangle(Canvas* canvas, int x1, int y1, int x2, int y2, char ch);
void draw_circle(Canvas* canvas, int cx, int cy, int radius, char ch);
void draw_triangle(Canvas* canvas, int x1, int y1, int x2, int y2, int x3, int y3, char ch);
void display_canvas(Canvas* canvas);
int add_object(Canvas* canvas, ShapeType type, int x1, int y1, int x2, int y2, int x3, int y3, char ch);
void delete_object(Canvas* canvas, int index);
void redraw_canvas(Canvas* canvas);
void modify_object(Canvas* canvas, int index, int x1, int y1, int x2, int y2, int x3, int y3);
void free_canvas(Canvas* canvas);

// Implementation

Canvas* create_canvas() {
    Canvas* canvas = (Canvas*)malloc(sizeof(Canvas));
    canvas->object_count = 0;
    clear_canvas(canvas);
    return canvas;
}

void clear_canvas(Canvas* canvas) {
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            canvas->canvas[i][j] = '_';
        }
    }
}

// Bresenham's line algorithm
void draw_line(Canvas* canvas, int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int x = x1, y = y1;
    while (1) {
        if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
            canvas->canvas[y][x] = ch;
        }
        if (x == x2 && y == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void draw_rectangle(Canvas* canvas, int x1, int y1, int x2, int y2, char ch) {
    // Ensure x1 < x2 and y1 < y2
    if (x1 > x2) { int temp = x1; x1 = x2; x2 = temp; }
    if (y1 > y2) { int temp = y1; y1 = y2; y2 = temp; }

    // Draw horizontal lines
    for (int x = x1; x <= x2; x++) {
        if (x >= 0 && x < CANVAS_WIDTH) {
            if (y1 >= 0 && y1 < CANVAS_HEIGHT) canvas->canvas[y1][x] = ch;
            if (y2 >= 0 && y2 < CANVAS_HEIGHT) canvas->canvas[y2][x] = ch;
        }
    }

    // Draw vertical lines
    for (int y = y1; y <= y2; y++) {
        if (y >= 0 && y < CANVAS_HEIGHT) {
            if (x1 >= 0 && x1 < CANVAS_WIDTH) canvas->canvas[y][x1] = ch;
            if (x2 >= 0 && x2 < CANVAS_WIDTH) canvas->canvas[y][x2] = ch;
        }
    }
}

void draw_circle(Canvas* canvas, int cx, int cy, int radius, char ch) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = cx + x;
                int py = cy + y;
                if (px >= 0 && px < CANVAS_WIDTH && py >= 0 && py < CANVAS_HEIGHT) {
                    canvas->canvas[py][px] = ch;
                }
            }
        }
    }
}

void draw_triangle(Canvas* canvas, int x1, int y1, int x2, int y2, int x3, int y3, char ch) {
    draw_line(canvas, x1, y1, x2, y2, ch);
    draw_line(canvas, x2, y2, x3, y3, ch);
    draw_line(canvas, x3, y3, x1, y1, ch);
}

void display_canvas(Canvas* canvas) {
    printf("\n");
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            printf("%c", canvas->canvas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int add_object(Canvas* canvas, ShapeType type, int x1, int y1, int x2, int y2, int x3, int y3, char ch) {
    if (canvas->object_count >= MAX_OBJECTS) {
        printf("Maximum objects reached!\n");
        return -1;
    }

    Shape* obj = &canvas->objects[canvas->object_count];
    obj->type = type;
    obj->x1 = x1;
    obj->y1 = y1;
    obj->x2 = x2;
    obj->y2 = y2;
    obj->x3 = x3;
    obj->y3 = y3;
    obj->character = ch;
    obj->active = 1;

    // Draw the object
    switch (type) {
        case LINE:
            draw_line(canvas, x1, y1, x2, y2, ch);
            break;
        case RECTANGLE:
            draw_rectangle(canvas, x1, y1, x2, y2, ch);
            break;
        case CIRCLE:
            draw_circle(canvas, x1, y1, x2, ch);  // x2 is radius
            break;
        case TRIANGLE:
            draw_triangle(canvas, x1, y1, x2, y2, x3, y3, ch);
            break;
    }

    printf("Object added with index %d.\n\n", canvas->object_count);
    return canvas->object_count++;
}

void delete_object(Canvas* canvas, int index) {
    if (index < 0 || index >= canvas->object_count) {
        printf("Invalid object index!\n");
        return;
    }

    canvas->objects[index].active = 0;
    redraw_canvas(canvas);
}

void modify_object(Canvas* canvas, int index, int x1, int y1, int x2, int y2, int x3, int y3) {
    if (index < 0 || index >= canvas->object_count || !canvas->objects[index].active) {
        printf("Invalid object index!\n");
        return;
    }

    canvas->objects[index].x1 = x1;
    canvas->objects[index].y1 = y1;
    canvas->objects[index].x2 = x2;
    canvas->objects[index].y2 = y2;
    canvas->objects[index].x3 = x3;
    canvas->objects[index].y3 = y3;

    redraw_canvas(canvas);
}

void redraw_canvas(Canvas* canvas) {
    clear_canvas(canvas);

    for (int i = 0; i < canvas->object_count; i++) {
        if (!canvas->objects[i].active) continue;

        Shape* obj = &canvas->objects[i];
        switch (obj->type) {
            case LINE:
                draw_line(canvas, obj->x1, obj->y1, obj->x2, obj->y2, obj->character);
                break;
            case RECTANGLE:
                draw_rectangle(canvas, obj->x1, obj->y1, obj->x2, obj->y2, obj->character);
                break;
            case CIRCLE:
                draw_circle(canvas, obj->x1, obj->y1, obj->x2, obj->character);
                break;
            case TRIANGLE:
                draw_triangle(canvas, obj->x1, obj->y1, obj->x2, obj->y2, obj->x3, obj->y3, obj->character);
                break;
        }
    }
}

void list_objects(Canvas* canvas) {
    printf("Objects:\n");
    for (int i = 0; i < canvas->object_count; i++) {
        if (!canvas->objects[i].active) continue;
        
        Shape* obj = &canvas->objects[i];
        printf("Object %d: ", i);
        
        switch (obj->type) {
            case LINE:
                printf("Line from (%d,%d) to (%d,%d)\n", 
                       obj->x1, obj->y1, obj->x2, obj->y2);
                break;
            case RECTANGLE:
                printf("Rectangle from (%d,%d) to (%d,%d)\n", 
                       obj->x1, obj->y1, obj->x2, obj->y2);
                break;
            case CIRCLE:
                printf("Circle center=(%d,%d), radius=%d\n", 
                       obj->x1, obj->y1, obj->x2);
                break;
            case TRIANGLE:
                printf("Triangle (%d,%d)-(%d,%d)-(%d,%d)\n", 
                       obj->x1, obj->y1, obj->x2, obj->y2, obj->x3, obj->y3);
                break;
        }
    }
    printf("\n");
}

void free_canvas(Canvas* canvas) {
    free(canvas);
}
