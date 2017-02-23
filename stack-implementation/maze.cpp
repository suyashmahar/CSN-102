/*
 * Author : Suyash Mahar
 * NOTE: Algorithm described in the slides had a flaw as mentioned at
 *       https://www.topcoder.com/community/data-science/data-science-tutorials/an-introduction-to-recursion-part-2/
 *       So this implementation is different and uses stack to keep 
 *       track of positions visited.   
 */


/*

Pseudo Code
===========

1 > Start from START character in maze

2 > Check for possible direction of movement form start i.e. left, right, 
    up & down.

3 > Mark direction of possible motion with '+', reverse direction as '#' and 
    direction which are not possible for movement with '-'. (For information 
    on reverse direction compare current position with item at top of the stack)

4 > Push this object with information from step 2 into the stack.

5 > If current position contains END character THEN
      > Pop all items from stack and mark corresponding positions on the 
        matrix with SOLUTION character.
      > EXIT from the program.
  > If direction of movement is possible (i.e. it contains atleast one '+') THEN 
      > Move in one of the possible direction with step of unit cell distance
        and repeat from step 2.
  > ELSE If direction of movement is not possible except reverse movement THEN
        (i.e. it contains all '-' except for one '#')
      > Pop last object from stack
      > Change values of current position to item at the top of the stack
      > Store this object temporarily, compare information from temporary
        object and last item of stack. Mark this direction as '-' in last
        object of the stack.
      > Repeat step 2

  > ELSE If direction of movement is not possible THEN
        (i.e. it has all direction marked as '-')
      > print error message or throw an error
      > EXIT from the program
 */

#include<iostream>
#include<stack>
#include<string>

#define TESTING 0
#define DEBUG 1

using namespace std;

struct cell{
    int x, y;
    char up, down, left, right;
    char value;
};

const int MAZE_HEIGHT = 9;
const int MAZE_WIDTH = 9;

const char START = 'S';
const char END = 'E';
const char WALL = '#';
const char CORRECT_PATH = '@';
const char PATH = ' ';

const string UP = "up";
const string DOWN = "down";
const string LEFT = "left";
const string RIGHT = "right";

char Maze[MAZE_HEIGHT][MAZE_WIDTH+1] ={
    "#S#######",
    "# ###   #",
    "# ### # #",
    "# #   # #",
    "# # # ###",
    "#   # # #",
    "# ### # #",
    "#   #   #",
    "#######E#",
};

char checkPosition(int x, int y){
    if (x < 0 || y < 0 || x >= MAZE_WIDTH || y >= MAZE_HEIGHT){
        return '-';
    } else if (Maze[y][x] != PATH){
        return '-';
    } else {
        return '+';
    }
}

bool checkMovement(cell currentCell, char compareChar){
    int x = currentCell.x, y = currentCell.y;
    return ((checkPosition(x,y-1) == compareChar) || (checkPosition(x,y+1) == compareChar)  ||
            (checkPosition(x-1,y) == compareChar)  || (checkPosition(x+1,y) == compareChar) );
}

void testing(){
    for (int i = 0; i < MAZE_WIDTH; i++){
        for (int j = 0; j < MAZE_HEIGHT; j++){
            cout << Maze[j][i] /*<< ' '*/;
        }
        cout << endl;
    }

    cell test;
    test.x = 2;
    test.y = 2; 

    cout << "performing tests at: " << test.x << ", " << test.y << endl << endl;

    cout << "Checking current position: " << checkPosition(test.x, test.y) << endl;
    cout << "Checking possibility of movement: " << checkMovement(test, '+') << endl;
    
    test.up = checkPosition(test.x,test.y-1);
    test.down = checkPosition(test.x,test.y+1);
    test.left = checkPosition(test.x-1,test.y);
    test.right = checkPosition(test.x+1,test.y);

    cout << " " << test.up << endl;
    cout << test.left <<  " " << test.right << endl;
    cout << " " << test.down << endl;

    cout << test.right << endl;
}

bool move (stack<cell> cellStack, string movement){
    if (cellStack.size() > 150){
        cout << "Error: Stack size exceeded" << endl;
        for (int i = 0; i < MAZE_WIDTH; i++){
            for (int j = 0; j < MAZE_HEIGHT; j++){
                cout << Maze[j][i] /*<< ' '*/;
            }
            cout << endl;
        }
        return 1;
    }
    cell currentCell = cellStack.top();

    #if (DEBUG)
        for (int i = 0; i < MAZE_WIDTH; i++){
            for (int j = 0; j < MAZE_HEIGHT; j++){
                cout << Maze[j][i] /*<< ' '*/;
            }
            cout << endl;
        }
        cout << "Currently at : (" << currentCell.x << ", " << currentCell.y << ")" << endl; 
            
        cout << " " << currentCell.up << endl;
        cout << currentCell.left <<  " " << currentCell.right << endl;
        cout << " " << currentCell.down << endl;

        cout << "Value : " << currentCell.value << endl;
    #endif



    if (movement == UP) currentCell.down = '#';
    else if (movement == DOWN) currentCell.up = '#';
    else if (movement == LEFT) currentCell.right = '#';
    else if (movement == RIGHT) currentCell.left = '#';

    cell next;

    if (checkPosition(currentCell.x, currentCell.y) && Maze[currentCell.y][currentCell.x] == END) { 
        return true;
    } else if (checkMovement(currentCell, '+')){
        string nextMovement = "";

        if (currentCell.up == '+'){
            next.x = currentCell.x;
            next.y = currentCell.y - 1;
            nextMovement = UP;
            cout << "Next Movement: " << nextMovement << endl;
        } else if (currentCell.down == '+'){
            next.x = currentCell.x;
            next.y = currentCell.y + 1;
            nextMovement = DOWN;
            cout << "Next Movement: " << nextMovement << endl;
        } else if (currentCell.left == '+'){
            next.x = currentCell.x - 1;
            next.y = currentCell.y;
            nextMovement = LEFT;
            cout << "Next Movement: " << nextMovement << endl;
        } else if (currentCell.right == '+'){
            next.x = currentCell.x + 1;
            next.y = currentCell.y;
            nextMovement = RIGHT;
            cout << "Next Movement: " << nextMovement << endl;
        }

    
        next.up = checkPosition(next.x,next.y-1);
        next.down = checkPosition(next.x,next.y+1);
        next.left = checkPosition(next.x-1,next.y);
        next.right = checkPosition(next.x+1,next.y);

    
        cout << "next up: " << next.up << endl;
        cout << "next down: " << next.down << endl;
        cout << "next left: " << next.left << endl;
        cout << "next right: " << next.right << endl;

        cellStack.push(next);
        
        return move(cellStack, nextMovement);
    } else if (checkMovement(currentCell, '#')){
        cout << "--------------------------------------------" << endl;
        Maze[cellStack.top().y][cellStack.top().x] = '#';
        cellStack.pop();
        
        return move(cellStack, "");
    } else {
        return false;
    }
}

int main(){
    #if (TESTING)
        cout << "<=========TESTING=========>" << endl;
        testing();
        return 0;
    #endif
    
    stack<cell> cellStack;
    
    cell start;
    start.x = 0;
    start.y = 1;

    start.value = 'S';
    
    start.up = checkPosition(start.x,start.y-1);
    start.down = checkPosition(start.x,start.y+1);
    start.left = checkPosition(start.x-1,start.y);
    start.right = checkPosition(start.x+1,start.y);

    cellStack.push(start);

    cout << move(cellStack, "") << endl;
}

