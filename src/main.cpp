#include <iostream>
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include "moves.h"
#include "pieces/check.h"

using namespace std;

bool whiteKingMoved = false;
bool whiteRookLeftMoved = false;
bool whiteRookRightMoved = false;
bool blackKingMoved = false;
bool blackRookLeftMoved = false;
bool blackRookRightMoved = false;
bool whiteTurn = true;

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
    pieceTextures["wp"] = LoadTexture("assets/images/wp.png");
    pieceTextures["wr"] = LoadTexture("assets/images/wr.png");
    pieceTextures["wn"] = LoadTexture("assets/images/wn.png");
    pieceTextures["wb"] = LoadTexture("assets/images/wb.png");
    pieceTextures["wq"] = LoadTexture("assets/images/wq.png");
    pieceTextures["wk"] = LoadTexture("assets/images/wk.png");

    pieceTextures["bp"] = LoadTexture("assets/images/bp.png");
    pieceTextures["br"] = LoadTexture("assets/images/br.png");
    pieceTextures["bn"] = LoadTexture("assets/images/bn.png");
    pieceTextures["bb"] = LoadTexture("assets/images/bb.png");
    pieceTextures["bq"] = LoadTexture("assets/images/bq.png");
    pieceTextures["bk"] = LoadTexture("assets/images/bk.png");

    // Draw the board
    while(!WindowShouldClose()){

        bool inCheck = isKingInCheck(board, whiteTurn);
        int kingRow = -1;
        int kingCol = -1;
        string kingCode = whiteTurn ? "wk" : "bk";
        for(int r = 0; r < 8; r++){
            for(int c = 0; c < 8; c++){
                if(board[r][c] == kingCode){
                    kingRow = r;
                    kingCol = c;
                }
            }
        }

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
                            if((whiteTurn && piece[0] == 'w') || (!whiteTurn && piece[0] == 'b')){
                                availableMoves = getMoves(row, col, piece, board, enPassantRow, enPassantCol);
                                selectedRow = row;
                                selectedCol = col;
                            }
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

                            // Promotion
                            if(movingPiece[1] == 'p'){
                                if((movingPiece[0] == 'w' && row == 0) || (movingPiece[0] == 'b' && row == 7)){
                                    board[row][col] = movingPiece[0] == 'w' ? "wq" : "bq";
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
                        whiteTurn = !whiteTurn;
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
                Color squareColor = ((row + col) % 2) ? dark : light;

                DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, squareColor);

                if(inCheck && row == kingRow && col == kingCol){
                    DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, Fade(RED, 0.5f));
                }

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
        for(const auto &m : availableMoves){
            DrawRectangle(m.col * squareSize, m.row * squareSize, squareSize, squareSize, Fade(GREEN, 0.5f));
        }
        DrawText(whiteTurn ? "White's Turn" : "Black's Turn", 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

}
