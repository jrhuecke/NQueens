#include "queen.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdint>
#include <stack>

using namespace std;

//Used to keep track of the state of the board at the
//current node in the stack recursion
class BoardState {
  public:
    vector<class Queen> queen_states;
    int board_size;
    bool compatible(int, int);
    int next_col();
    int working_index;
};

//checks if the inputted coords would conflict with any
//of the queens already placed
bool BoardState::compatible(int col, int row) {
  bool conflicts = false;
  //iterates through the vector of queens checking if it conflicts with
  //any of them one at a time
  for (uint32_t i = 0; i < queen_states.size() && conflicts == false; i++) {
     if (queen_states[i].attackable(col, row)){
       conflicts = true;
     }    
  }
  return !conflicts;
}

//returns the next column that needs a queen placed in it
int BoardState::next_col() {
  int next_col = 1;
  //going through every column
  for (int i = 1; i < board_size + 1; i++) {
    bool conflicts = false;
    //checking if column is already in use
    for (size_t j = 0; j < queen_states.size(); j++) {
      next_col = i;
      //if column is in use then keeps running
      if (queen_states[j].col == i) {
        conflicts = true;
      }
    }
    //stops running if an open col was found
    if (!conflicts) {
      break;
    }
  }
  return next_col;
}

int main(int argc, char *argv[]) {
  //Checking for correct num of command line arguments
  if (argc != 3) {
    cout << "Invalid number of command line arguments.\n";
    return 0;
  }
  
  //opening provided in/out files
  ifstream infile(argv[1]);
  ofstream outfile(argv[2]);
  //initializing stuff for use in the big while loop
  string input;
  vector<int> positions;
  int num;
  size_t size;
  vector<class Queen> queens; 
  bool noSol;
  
  
  //reads input file line at a time
  while (getline(infile, input)){
    //extracts all the ints from the line and stores in vector
    stringstream in(input);
    while (in >> num) {
      positions.push_back(num);
    }
    
    //saves the size of the nxn board
    size = positions[0];
    
    //put the position coords into Queen classes and 
    //stores all the Queen classes in a vector
    Queen queen; 
    for (uint32_t i = 1; i < positions.size(); i = i + 2) {
      queen.col = positions[i];
      queen.row = positions[i + 1];
      queens.push_back(queen);
    }
    
    //check to see if the inputed queens are compatible
    noSol = false;
    for (uint32_t i = 0; i < queens.size() && noSol == false; i++) {
      for (uint32_t j = i + 1; j < queens.size() && noSol == false; j++) {
        if (queens[i].attackable(queens[j].col, queens[j].row)){
          noSol = true;
        }
      }
    }
    
    //if they were not compatible then "No solution"
    if (noSol) {
      outfile << "No solution\n";
      queens.clear();
      positions.clear();
      continue;
    } 
    
    //creating stack of board states and pushing
    //the initial board state
    stack<class BoardState> placements;
    BoardState current, temp;
    current.queen_states = queens;
    current.board_size = size;
    placements.push(current);
    Queen test_queen;
    int test_col;   
    bool solution_found = false;
    
    //simulating recursion using a stack to find solution 
    while (!placements.empty()) {
      current = placements.top();
      placements.pop();
      //checking the top of the stack to see if solution was found
      if (current.queen_states.size() == size) {
        solution_found = true;
        break;
      }
      //finding what col needs filling next
      temp = current;
      test_col = temp.next_col();
      //finding every possible position for the queen in that col
      //and pushing the board state if it were to be used
      for (size_t l = 1; l < size + 1; l++) {
        temp = current;
        if (temp.compatible(test_col, l)) {
          test_queen.col = test_col;
          test_queen.row = l;
          temp.queen_states.push_back(test_queen);
          placements.push(temp);
        }
      }    
    }
    
    //outputs the solution in the corrrect order
    if (solution_found) {
      //for each col
      for (size_t m = 1; m < current.queen_states.size() + 1; m++) {
        //finds the queen in that col
        for (size_t n = 0; n < current.queen_states.size(); n++) {
           //m typecasted to int to remove warning
           if (current.queen_states[n].col == (int)m) {
              //and output their coords
              outfile << current.queen_states[n].col << " " <<current.queen_states[n].row << " ";
           }
        }
      }
      outfile << endl;
    } else {
      outfile << "No solution\n";
    }
    
    //clearing stack/vectors for next input
    while (!placements.empty()) {
      placements.pop();
    }
    queens.clear();
    positions.clear();
  }
  
  
  
  infile.close();
  outfile.close();
  return 0;
}