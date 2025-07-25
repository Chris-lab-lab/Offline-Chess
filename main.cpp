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
                        availableMoves = getMoves(row, col, piece, board);
                        selectedRow = row;
                        selectedCol = col;
                    }
                }
                else{
                    bool moveMade = false;
                    for(const Move &m : availableMoves){
                        if(m.row == row && m.col == col){
                            board[row][col] = board[selectedRow][selectedCol];
                            board[selectedRow][selectedCol] = "";
                            moveMade = true;
                            break;
                        }
                    }
                    availableMoves.clear();
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
