/* 
 *  Author : Suyash Mahar
*/

#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

/*
 * minSeparation : Minimum separation between the start and end of a 
 *                 valid path in the maze.
 * height        : Height of the matrix.
 * width         : Width of the matrix.
 * maxPaths      : Maximum number of valid paths to generate in the 
                   matrix.
*/
int minSeparation = 23;
int height = 23;
int width = 23;
int maxPaths = 23;

struct coordinate {
    int x;
    int y;
};


/*
 * generateMaze         : Generate a maze with border.
 * generateLinePath     : Generates path of a straight line with given initial and final points.
 * drawPath             : Draws the path provided in the matrix.
 * printMatrix          : Prints the provided matrix 
*/
char** generateMaze(int x, int y);
vector<coordinate> generateLinePath(int srcX, int srcY, int desX, int desY);
char** drawPath(vector<coordinate> path, char** matrix);
void printMatrix(char** inputMatrix, int x, int y);


int main(){
    srand(time(NULL));

    cout << "Enter staring x coordinate of the line: ";
    int startX; cin >> startX;
    cout << "Enter staring y coordinate of the line: ";
    int startY; cin >> startY;

    cout << "Enter ending x coordinate of the line: ";
    int endX; cin >> endX;
    cout << "Enter ending y coordinate of the line: ";
    int endY; cin >> endY;

    char** matrix = generateMaze(height, width);

    matrix = drawPath(generateLinePath(startX, startY, endX, endY), matrix);

    printMatrix(matrix, height,  width);
}

char** drawPath(vector<coordinate> path, char** matrix) {
    for (int i = 0; i < path.size(); i++){
        matrix[path[i].y][path[i].x] = '*';
    }    
    return matrix;
}

vector<coordinate> generateLinePath(int srcX, int srcY, int desX, int desY){
    int dX = desX - srcX; 
    int dY = desY - srcY; 

    // Slope
    float m = dY/(float)dX;
    m = 1/m;
    vector<coordinate> path;

    int x = 0, y = srcY;

    while (y != desY){
        x = (int)(srcX + m*(y - srcY)) /*!= 0 ? (int)(srcX + m*(y - srcY)) : y*/;

        coordinate crdToInsert;

        crdToInsert.x = x;
        crdToInsert.y = y++;

        path.push_back(crdToInsert);
    }    
    return path;
}

char** generateMaze(int x, int y){
    char** newMaze = new char*[x];

    for (int i = 0; i < height; i++){
        char *row = new char[width];
        newMaze[i] = row;

        for (int j = 0; j < width; j++){
            if (i*j == 0 || j == width-1 || i == height-1) { 
                newMaze[i][j] = '*';
            } else {
                newMaze[i][j] = ' ';
            }
        }
    }
    return newMaze;
}

void printMatrix(char** inputMatrix, int x, int y){
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            cout << inputMatrix[i][j] << " ";
        }
        cout << endl;
    }
}