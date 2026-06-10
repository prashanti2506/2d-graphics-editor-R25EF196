# 2D Graphics Editor

A terminal-based 2D graphics editor written in C that allows you to draw and manipulate geometric shapes using ASCII characters (`*` and `_`).

## Features

### Core Functionality
- **Draw Shapes**: Create circles, rectangles, lines, and triangles
- **Add Objects**: Add unlimited shapes to the canvas (up to 50 objects)
- **Delete Objects**: Remove shapes from the canvas
- **Modify Objects**: Edit existing shapes by changing their coordinates
- **Display Canvas**: View the current drawing on a 100x40 character canvas

### Shapes Supported
1. **Line** - Draw lines between two points using Bresenham's algorithm
2. **Rectangle** - Draw rectangular outlines by specifying top-left and bottom-right corners
3. **Circle** - Draw filled circles by specifying center point and radius
4. **Triangle** - Draw triangular outlines by specifying three vertices

## Project Structure

```
.
├── main.c              # Main program with menu system
├── graphics_editor.c   # Core graphics functions
├── Makefile           # Build configuration
└── README.md          # Project documentation
```

## Requirements

- GCC compiler
- Unix/Linux environment (or MinGW on Windows)
- Standard C library

## Installation & Compilation

### Using Make (Recommended)
```bash
make          # Compile the program
make run      # Compile and run
make clean    # Remove build artifacts
```

### Manual Compilation
```bash
gcc -Wall -g -o graphics_editor main.c -lm
```

## Usage

Run the program:
```bash
./graphics_editor
```

### Menu Options
1. **Draw Line** - Create a line between two points
2. **Draw Rectangle** - Create a rectangular outline
3. **Draw Circle** - Create a filled circle
4. **Draw Triangle** - Create a triangular outline
5. **Delete Object** - Remove a shape from the canvas
6. **Modify Object** - Edit coordinates of existing shape
7. **Display Canvas** - View the current drawing
8. **Clear Canvas** - Clear all objects
9. **List Objects** - Show all active objects
0. **Exit** - Close the program

### Canvas Specifications
- **Width**: 100 characters
- **Height**: 40 characters
- **Max Objects**: 50 shapes
- **Supported Characters**: `*` (default), `_`, or any printable ASCII character

## Example Usage

### Drawing a Rectangle
```
Menu -> 2 (Draw Rectangle)
Enter top-left point: 10 5
Enter bottom-right point: 30 15
Enter character: *
```

### Drawing a Circle
```
Menu -> 3 (Draw Circle)
Enter center: 50 20
Enter radius: 8
Enter character: *
```

### Drawing a Triangle
```
Menu -> 4 (Draw Triangle)
Enter first point: 20 10
Enter second point: 40 10
Enter third point: 30 25
Enter character: *
```

## Technical Implementation

### Drawing Algorithms
- **Line**: Bresenham's line algorithm for efficient line drawing
- **Rectangle**: Horizontal and vertical line segments
- **Circle**: Midpoint circle algorithm with filled area
- **Triangle**: Three connected line segments

### Data Structures
```c
// Canvas: 2D array of characters
char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

// Shape: Object metadata
typedef struct {
    ShapeType type;
    int x1, y1, x2, y2, x3, y3;
    char character;
    int active;
} Shape;
```

### Key Functions
- `create_canvas()` - Initialize canvas
- `draw_line()` - Draw line using Bresenham's algorithm
- `draw_rectangle()` - Draw rectangle outline
- `draw_circle()` - Draw filled circle
- `draw_triangle()` - Draw triangle outline
- `add_object()` - Add shape to canvas
- `delete_object()` - Remove shape from canvas
- `modify_object()` - Update shape coordinates
- `display_canvas()` - Render canvas to terminal
- `redraw_canvas()` - Redraw all active objects

## Limitations & Future Improvements

### Current Limitations
- Text-based only (no graphics library)
- Fixed canvas size (100x40)
- Maximum 50 objects

### Future Enhancements
- [ ] Implement ncurses for better terminal UI
- [ ] Add filled shapes option
- [ ] Support for rotated shapes
- [ ] Add polygon drawing
- [ ] Color support (if terminal supports it)
- [ ] Save/load drawings to file
- [ ] Undo/redo functionality
- [ ] Shape layer management

## Compilation Notes

The program links against the math library (`-lm`) for mathematical operations used in circle and line drawing algorithms.

## Testing

To test the program:
1. Compile: `make`
2. Run: `make run`
3. Try drawing different shapes
4. Use option 7 to display the canvas
5. Test delete and modify functions
6. Use option 9 to list all objects

## Author

Created as a 2D Graphics Editor assignment project.

## License

This project is open source and available for educational purposes.
