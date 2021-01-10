#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {


    // Main loop
    unique_ptr<OthelloMove> m;
    auto board = std::make_shared<OthelloBoard>();
    string userInput;
    // Print the game board using the OthelloView object
    OthelloView v(board);
    vector<unique_ptr<OthelloMove>> pMoves;
    do {
        cout << v << endl;
        pMoves = board->GetPossibleMoves();
        cout << "Possible moves:" << endl;
        if (string(*pMoves[0]) == "(-1,-1)") {
            cout << "pass";
        }
        else
        {
            for (auto& move : pMoves) {
                cout << *move << " ";
            }
        }
        cout << endl;
        cout << "Enter a command: " << endl;
        getline(cin, userInput);
        stringstream coordPoint(userInput.substr(5));
        string coord = "";
        coordPoint >> coord;
        if (userInput.substr(0, 4) == "move") {
            if (coord == "pass") {
                m = make_unique<OthelloMove>(OthelloMove(BoardPosition(-1, -1)));
                board->ApplyMove(std::move(m));
                continue;
            }
            bool validMove = false;
            for (auto& move : pMoves) {
                if (coord == string(*move)) {
                    validMove = true;
                    break;
                }
            }
            if (validMove) {
                m = v.ParseMove(coord);
                board->ApplyMove(std::move(m));
            }
            else {
                cout << "Not a valid move" << endl;
            }
        }
        // undo n
        else if (userInput.substr(0, 4) == "undo")
        {
           stringstream undoAmount(userInput.substr(5));
           int amount = 0;
           undoAmount >> amount;
           int counter = 0;
           while (counter < amount )
           {
               board->UndoLastMove();
               counter++;
           }
        }
        // showValue
        else if (userInput == "showValue")
        {
            cout << "Value: " << board->GetValue() << endl;
        }
        // showHistory
        else if (userInput == "showHistory")
        {
            auto &movesPlayed = board->GetMoveHistory();
            auto currentPlayer = board->GetCurrentPlayer();
            int player = int(currentPlayer);
            for (auto itr = movesPlayed.rbegin(); itr != movesPlayed.rend(); itr++) {
                if (player == -1)
                {
                    cout << "Black: " << *(*itr) << endl;
                }
                else if (player == 1)
                {
                    cout << "White: " << *(*itr) << endl;
                }
                player = player * -1;
            }
        }
        // quit
        else if (userInput == "quit")
        {
            break;
        }
    } while ( !board->isFinished() ); // you may want to change the condition
    if (board->isFinished())
    {
        auto winner = board->GetCurrentPlayer();
        int player = int(winner);
        if (player == 1)
        {
            cout << "Black Wins!" << endl;
        }
        else
        {
            cout << "White Wins!" << endl;
        }
    }
}