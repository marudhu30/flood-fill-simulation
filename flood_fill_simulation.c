#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point items[MAX * MAX];
    int front, rear;
} Queue;

void enqueue(Queue *q, Point p) {
    if (q->rear < MAX * MAX) {
        q->items[q->rear++] = p;
    }
}

Point dequeue(Queue *q) {
    return q->items[q->front++];
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int isValid(int x, int y, int ROW, int COL) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL);
}

void floodFill(int screen[MAX][MAX], int x, int y, int newColor, int ROW, int COL) {
    int oldColor = screen[x][y];
    if (oldColor == newColor) {
        printf("\nNew color is same as original color. No changes made.\n");
        return;
    }

    Queue q;
    q.front = q.rear = 0;
    enqueue(&q, (Point){x, y});

    while (!isEmpty(&q)) {
        Point p = dequeue(&q);
        int currX = p.x;
        int currY = p.y;

        screen[currX][currY] = newColor;

        for (int i = 0; i < 4; i++) {
            int nx = currX + dx[i];
            int ny = currY + dy[i];

            if (isValid(nx, ny, ROW, COL) && screen[nx][ny] == oldColor) {
                enqueue(&q, (Point){nx, ny});
            }
        }
    }
}

void printScreen(int screen[MAX][MAX], int ROW, int COL) {
    printf("\n----------------- Screen -----------------\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%2d ", screen[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------------------\n");
}

int main() {
    int screenPortrait[MAX][MAX] = {
        {1,1,1,0,0,1,1,1,1},
        {1,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,1,0,1},
        {1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,1,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1},
    };

    int screenLandscape[MAX][MAX] = {
        {1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1},
        {1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
        {1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1},
        {1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,1},
        {1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1},
        {1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1}
    };

    int choice;
    printf("Choose screen aspect ratio:\n");
    printf("1. Portrait (9:16)\n");
    printf("2. Landscape (16:9)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    int x, y, newColor;
    if (choice == 1) {
        int ROW = 16, COL = 9;
        printScreen(screenPortrait, ROW, COL);

        printf("Enter the starting point coordinates (row,col): ");
        scanf("%d %d", &x, &y);

        if (!isValid(x, y, ROW, COL)) {
            printf("Error: Invalid coordinates. Please enter values between 0 and (%d, %d).\n", ROW - 1, COL - 1);
            return 1;
        }

        printf("Enter the new color (integer): ");
        scanf("%d", &newColor);

        floodFill(screenPortrait, x, y, newColor, ROW, COL);

        printf("\nAfter applying flood fill on 9:16 screen:\n");
        printScreen(screenPortrait, ROW, COL);
    } else if (choice == 2) {
        int ROW = 9, COL = 16;
        printScreen(screenLandscape, ROW, COL);

        printf("Enter the starting point coordinates (x y): ");
        scanf("%d %d", &x, &y);

        if (!isValid(x, y, ROW, COL)) {
            printf("Error: Invalid coordinates. Please enter values between 0 and (%d, %d).\n", ROW - 1, COL - 1);
            return 1;
        }

        printf("Enter the new color (integer): ");
        scanf("%d", &newColor);

        floodFill(screenLandscape, x, y, newColor, ROW, COL);

        printf("\nAfter applying flood fill on 16:9 screen:\n");
        printScreen(screenLandscape, ROW, COL);
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    return 0;
}
