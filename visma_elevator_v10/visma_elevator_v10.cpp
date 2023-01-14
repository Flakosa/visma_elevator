// visma_elevator_v10.cpp 

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
//----------------------------------------
class elevator {
//----------------------------------------
private:
    //private variables
    int ele_memory[4] = { 0,0,0,0 }; //using for saving buttons press
    int actual_position = 1; //saving actual position of elevator
    int mark = 1;   //using for elevator render like kursor position
    //------------------------------------
    //function for elevator drawing took position for knowing where to draw elevator and door to know if door should be open or not
    void skic(int position, bool door) {
        system("CLS"); 
        //setting the cursor to render the elevator based on its desired position
        if (position == 4) mark = 1;
        else if (position == 3) mark = 5;
        else if (position == 2) mark = 9;
        else mark = 13;
        //logic of rendering
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 9; j++) {
                if (i == 0 || i == 18 || j == 8)cout << "H";
                else if ((j == 0 || j == 1 || j == 2) && (i == 1 || i == 5 || i == 9 || i == 13 || i == 17)) cout << "H";
                else if ((j == 6 && (i == mark + 1 || i == mark + 2 || i == mark + 3)) || ((i == mark || i == mark + 4) && (j == 3 || j == 4 || j == 5 || j == 6)) || (i == mark + 1 && j == 3))cout << "X";
                else if (door == true && (j == 3 && (i == mark+2 || i == mark+3)))cout << "|";
                else cout << " ";
            }
            cout << endl; //ending a line after finishing drawing in it
        }
    }
    //------------------------------------
    //function for determining which direction the elevator should go
    //for cases 1 and 4 there is no need to determine which way to go 
    void elevator_move(int stop_position) {
        if (actual_position != stop_position)
        {
            switch (actual_position) {
            case 1:
                count_up(1, stop_position); //call function for moving the lift upwards
                actual_position = stop_position; //the actual position will change based on the desired position
                break;
            case 2:
                if (2 > stop_position) count_down(2, stop_position); //condition for determining the direction of the lift
                else count_up(2, stop_position);
                actual_position = stop_position;
                break;
            case 3:
                if (3 > stop_position) count_down(3, stop_position);
                else count_up(3, stop_position);
                actual_position = stop_position;
                break;
            case 4:
                count_down(4, stop_position);
                actual_position = stop_position;
                break;
            }
        }
        //if the desired and actual positions match, the elevator will only open the door
        else skic(actual_position, false);
    }
    //------------------------------------
    //function to move the lift down
    void count_down(int start, int stop) {
        system("CLS"); //removing the previous output
        for (int i = start * 10; i >= stop * 10; i--) {
            Sleep(2); //only for slow down output to see if everything works fine 
            if (i == 10) skic(1, true); 
            else if (i == 20)  skic(2, true);
            else if (i == 30)  skic(3, true);
            else if (i == 40)  skic(4, true);
        }
        //when the elevator stops it opens the corresponding door
        if (stop == 1) skic(1, false);
        if (stop == 2) skic(2, false);
        if (stop == 3) skic(3, false);
        if (stop == 4) skic(4, false);
    }
    //------------------------------------
    void count_up(int start, int stop) {
        system("CLS");
        for (int i = start * 10; i <= stop * 10; i++) {
            Sleep(2);
            if (i == 10) skic(1, true);
            else if (i == 20)  skic(2, true);
            else if (i == 30)  skic(3, true);
            else if (i == 40)  skic(4, true);
        }
        if (stop == 1) skic(1, false);
        if (stop == 2) skic(2, false);
        if (stop == 3) skic(3, false);
        if (stop == 4) skic(4, false);
    }
//----------------------------------------
public:
    //------------------------------------
    //rendering of the elevator at program start
    void begining_skic() {
        skic(1, true);
    }
    //------------------------------------
    //button logic for elevator movement
    void elevator_memory(int button) {
        //conversion from decimal ascii coding to appropriate floors
        if (button == 49) button = 1;
        else if (button == 50) button = 2;
        else if (button == 51) button = 3;
        else if (button == 52) button = 4;
        elevator_move(button);
    }
};

int main()
{
    elevator ele;
    ele.begining_skic(); //render elevator
    int kbhit=0;    //variable for saving what was clicked
    bool error_control = false; //using during error to mamke sure that error is showing only one time
    while (true) {
        kbhit = _getch();
        if (kbhit == 49 || kbhit == 50 || kbhit == 51 || kbhit == 52) {
            error_control = false; //reset error control 
            ele.elevator_memory(kbhit); //start elevator
        }
        //break program if user click 'q'
        else if (kbhit == 113) break;
        else {
            if (error_control == false) {
                error_control = true;
                //error message
                cout << "Press 1 for floor 1. \n Press 2 for floor 2. \n Press 3 for floor 3. \n Press 4 for floor 4. \n Press q for exit.";
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

