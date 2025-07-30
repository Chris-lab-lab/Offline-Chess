#include <iostream>
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include "moves.h"

using namespace std;

int main () {
    const int screenWIDTH = 600;
    const int screenHEIGHT = 600;
    const int rows = 8;
    const int cols = 8;
    const int squareSize = screenWIDTH/cols;

    vector<Move> availableMoves;
    int selectedRow = -1;
    int selectedCol = -1;

    int enPassantRow = -1;
    int enPassantCol = -1;

    bool whiteKingMoved = false;
    bool whiteRookLeftMoved = false;
    bool whiteRookRightMoved = false;
    bool blackKingMoved = false;
    bool blackRookLeftMoved = false;
    bool blackRookRightMoved = false;

    InitWindow(screenWIDTH, screenHEIGHT, "Chess");
    SetTargetFPS(60);

    // BOARD state
    string board[8][8] = {
        {"br", "bn", "bb", "bq", "bk", "bb", "bn", "br"},
        {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
        {"wr", "wn", "wb", "wq", "wk", "wb", "wn", "wr"}
    };

    // Load texture
    map<string, Texture2D> pieceTextures;
    pieceTextures["wp"] = LoadTexture("images/wp.png");
    pieceTextures["wr"] = LoadTexture("images/wr.png");
    pieceTextures["wn"] = LoadTexture("images/wn.png");
    pieceTextures["wb"] = LoadTexture("images/wb.png");
    pieceTextures["wq"] = LoadTexture("images/wq.png");
    pieceTextures["wk"] = LoadTexture("images/wk.png");

    pieceTextures["bp"] = LoadTexture("images/bp.png");
    pieceTextures["br"] = LoadTexture("images/br.png");
    pieceTextures["bn"] = LoadTexture("images/bn.png");
    pieceTextures["bb"] = LoadTexture("images/bb.png");
    pieceTextures["bq"] = LoadTexture("images/bq.png");
    pieceTextures["bk"] = LoadTexture("images/bk.png");

    // Draw the board
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Check available moves and move
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 mousePos = GetMousePosition();
            int col = mousePos.x / squareSize;
            int row = mousePos.y / squareSize;

            if(row >= 0 && row < 8 && col >= 0 && col < 8){
                if(selectedRow == -1 && selectedCol == -1){
                    string piece = board[row][col];
                    if(!piece.empty()){
                        availableMoves = getMoves(row, col, piece, board, enPassantRow, enPassantCol);
                        selectedRow = row;
                        selectedCol = col;
                    }
                }
                else{
                    bool moveMade = false;
                    for(const auto &m : availableMoves){
                        if(m.row == row && m.col == col){
                            string movingPiece = board[selectedRow][selectedCol];
                            board[row][col] = movingPiece;
                            board[selectedRow][selectedCol] = "";

                            if(movingPiece[1] == 'p'){
                                if(row == enPassantRow && col == enPassantCol){
                                    if(movingPiece[0] == 'w'){
                                        board[row + 1][col] = "";
                                    }
                                    else if(movingPiece[0] == 'b'){
                                        board[row - 1][col] = "";
                                    }
                                }
                            }

                            // En Passant
                            if(movingPiece[1] == 'p'){
                                if(movingPiece[0] == 'w' && selectedRow == 6 && row == 4){
                                    enPassantRow = 5;
                                    enPassantCol = col;
                                }
                                if(movingPiece[0] == 'b' && selectedRow == 1 && row == 3){
                                    enPassantRow = 2;
                                    enPassantCol = col;
                                }
                            }

                            // Castling
                            if(movingPiece == "wk" && abs(col - selectedCol) == 2){
                                if(col == 6){
                                    board[7][5] = board[7][7];
                                    board[7][7] = "";
                                }
                                else if(col == 2){
                                    board[7][3] = board[7][0];
                                    board[7][0] = "";
                                }
                            }
                            else if(movingPiece == "bk" && abs(col - selectedCol) == 2){
                                if(col == 6){
                                    board[0][5] = board[0][7];
                                    board[0][7] = "";
                                }
                                else if(col == 2){
                                    board[0][3] = board[0][0];
                                    board[0][0] = "";
                                }
                            }

                            if(movingPiece == "wk") whiteKingMoved = true;
                            if(movingPiece == "bk") blackKingMoved = true;
                            if(movingPiece == "wr" && selectedRow == 7 && selectedCol == 0) whiteRookLeftMoved = true;
                            if(movingPiece == "wr" && selectedRow == 7 && selectedCol == 7) whiteRookRightMoved = true;
                            if(movingPiece == "br" && selectedRow == 0 && selectedCol == 0) blackRookLeftMoved = true;
                            if(movingPiece == "br" && selectedRow == 0 && selectedCol == 7) blackRookRightMoved = true;
                            
                            moveMade = true;
                            break;
                        }
                    }
                    availableMoves.clear();

                    // Clear en passant if it is not moved
                    if(!(board[row][col][1] == 'p' && ((board[row][col][0] == 'w' && selectedRow == 6 && row == 4) || (board[row][col][0] == 'b' && selectedRow == 1 && row == 3)))){
                        enPassantRow = -1;
                        enPassantCol = -1;
                    }

                    if(moveMade){
                        selectedRow = -1;
                        selectedCol = -1;
                    }
                    else{
                        selectedRow = -1;
                        selectedCol = -1;
                    }
                }
            }
        }

        
        for(int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                Color light = { 240, 217, 181, 255 };
                Color dark  = { 181, 136, 99, 255 };
                Color squareColor = ((row + col) % 2) ? light : dark;
                DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, squareColor);

                string pieceCode = board[row][col];
                if(pieceCode != ""){
                    Texture2D tex = pieceTextures[pieceCode];
                    float scale = squareSize / (float)tex.width;

                    float texWidth = tex.width * scale;
                    float texHeight = tex.height * scale;

                    float x = col * squareSize + (squareSize - texWidth) / 2.0f;
                    float y = row * squareSize + (squareSize - texHeight) / 2.0f;
                    
                    DrawTextureEx(tex, {x, y}, 0.0f, scale, WHITE);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

}
