#include<iostream>
using namespace std;

#define gridSize 9
#define empty '*'
#define CPU 'X'
#define user '0'
int pointyIndex;

/*
 * A board/ grid. For simplicity sake, if the board is empty, it will have a start (*) on block
 ***/
char grid[gridSize] = {empty,empty,empty,empty,empty,empty,empty,empty,empty};

/*
 * function declarations
 **/
int isGridFull();
int userWins();
int computerWins();
void displayGrid();
int minMaxAlgorithm(bool flag);
void startDisplay();
void clearScreen();

int main(){
    int turn,startChoice;
    startDisplay();
    while(!(cin>>startChoice) || (startChoice < 1 || startChoice > 2)){
        cout << "[ERROR] please pick 1 or 2."<< endl ;
        cin.clear();
        cin.ignore(INT32_MAX, '\n');
        cout << "1 ---> Player\n2 ---> Computer\n";
     }
    if(startChoice == 1){
        clearScreen();
        displayGrid();
up:     cout<<endl<<"(Your turn)==>$\t";
        while(!(cin>>turn)){
            cout << "[ERROR] please pick a number from 1 to 9 - a box on the grid which is empty.\n";
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
            cout<<endl<<"(Your turn)==>$\t";
        }
        if(grid[turn-1]==empty){
            grid[turn-1] = user;
            clearScreen();
            displayGrid();
        }else{
            cout<<endl<<"[ERROR!] Invalid position on the bord. Try different one";
            goto up;
        }
   }

    while(true){
        //computer turn
        minMaxAlgorithm(true);
        grid[pointyIndex] = CPU;
        clearScreen();
        displayGrid();
        if(computerWins()==1){
            cout<<endl<<"COMPUTER WON!!!\n";
            break;
        }
        if(isGridFull()==1){
            cout<<endl<<"IT WAS A DRAW\n";
            break;
        }
again:  cout<<endl<<"(Your turn)==>$\t";
        while(!(cin>>turn)){
            cout << "[ERROR] please pick a number from 1 to 9 - a box on the grid which is empty.\n";
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
            cout<<endl<<"(Your turn)==>$\t";
        }
        clearScreen();
        if(grid[turn-1]==empty){
            grid[turn-1] = user;
            displayGrid();
        }else{
            displayGrid();
            cout<<endl<<"[ERROR!] Invalid position on the bord. Try a different one.";
            goto again;
        }if(userWins()==1){
            cout<<endl<<"Congratulations. YOU WON! [If it happened, please report the error to the developer immediately. Thanks.]\n";
            break;
        }if(isGridFull() == 1){
            cout<<endl<<"IT WAS A DRAW\n";
            break;
        }
    }
    return EXIT_SUCCESS;
}





/****
 * a case where all the boxes of the grid are clicked (so to speak) 
 ***/
int isGridFull(){
    for(int i = 0; i < gridSize; i++){
        if((grid[i] != CPU) && (grid[i] != user)) return 0;
    }
return 1;
}

/**
 * all the possible combinations where a user can win the game
 ***/
int userWins(){
    for(int i=0;i<gridSize;i+=3){
        if((grid[i] == grid[i+1]) && (grid[i+1] == grid[i+2]) && (grid[i] == user)) return 1;
    }
    for(int i=0;i<3;i++){
        if((grid[i] == grid[i+3])&&(grid[i+3] == grid[i+6])&&(grid[i] == user)) return 1;
    }
    if((grid[0] == grid[4]) && (grid[4] == grid[8]) && (grid[0] == user)) return 1;
    if((grid[2] == grid[4])&&(grid[4] == grid[6])&&(grid[2] == user)) return 1;
    return 0;
}

/***
 * All the possible combinations where the computer will eventually win 
 */
int computerWins(){
    for(int i=0; i<gridSize; i+=3){
        if((grid[i] == grid[i+1]) && (grid[i+1] == grid[i+2]) && (grid[i]==CPU)) return 1;
    }
    for(int i=0;i<3;i++){
        if((grid[i]==grid[i+3])&&(grid[i+3]==grid[i+6])&&(grid[i]==CPU)) return 1;
    }
    if((grid[0]==grid[4])&&(grid[4]==grid[8])&&(grid[0]==CPU)) return 1;
    if((grid[2]==grid[4])&&(grid[4]==grid[6])&&(grid[2]==CPU)) return 1;
    return 0;
}

/***
 * a nice little display for the grid 
 **/
void displayGrid(){
    cout<< "\n    " << grid[0]<< "\t|   " <<grid[1] <<"\t|   " <<grid[2] <<endl;
    cout<<"-------------------------" <<endl;
    cout << "    "<<grid[3] << "\t|   " <<grid[4] <<"\t|   " <<grid[5] <<endl;
    cout<<"-------------------------"<<endl;
    cout<< "    " <<grid[6] <<"\t|   " << grid[7] <<"\t|   " << grid[8] << endl;
}

/****
 * the crucial part of the un-winable tic tac toe: MIN MAX ALGORITHM. 
 ***/
int minMaxAlgorithm(bool flag){
    int maxValue=-1000,minValue=1000;
    int i,j,value = 1;
    if(computerWins() == 1)
        {return 10;}
    else if(userWins() == 1)
        {return -10;}
    else if(isGridFull()== 1)
        {return 0;}
    int score[9] = {1,1,1,1,1,1,1,1,1};
        for(i=0;i<gridSize;i++){
            if((grid[i] == empty) && (minValue > maxValue)){
                if(flag == true){
                    grid[i] = CPU;
                    value = minMaxAlgorithm(false);
                }else{
                    grid[i] = user;
                    value = minMaxAlgorithm(true);
                }
            grid[i] = empty;
            score[i] = value;
            }
        }
        if(flag == true){
            maxValue = -1000;
            for(j=0;j<9;j++){
                if(score[j] > maxValue && score[j] != 1){
                    maxValue = score[j];
                    pointyIndex = j;
                }
            }
            return maxValue;
        }
        if(flag == false){
            minValue = 1000;
            for(j=0;j<gridSize;j++){
                if(score[j] < minValue && score[j] != 1){
                    minValue = score[j];
                    pointyIndex = j;
                }
            }
            return minValue;
        }
}

/***
 * a nice little display at the start at the program
 **/
void startDisplay(){
    cout << "=============================================\nTIC TAC TOE YOU CAN'T WIN\n=============================================\n";
    cout << "USER ----> (O)\t\t\tCPU ----> (X)\n";
    cout << "Please choose: \n";
    cout << "1 ---> Player\n2 ---> Computer\n";
}

void clearScreen(){
    system("clear");
    /*so that it looks like, we are playing the game on the same page*/
    cout << "=============================================\nTIC TAC TOE YOU CAN'T WIN\n=============================================\n";
    cout << "USER ----> (O)\t\t\tCPU ----> (X)\n\n";
}