#include "raylib.h"
#include "rlImGui.h"	
#include "imgui.h"

#include "GameLife.h"

#if defined(_WIN32)           
#define NOGDI             
#define NOUSER            
#endif

#if defined(_WIN32)
#include <Windows.h> 
#endif

#if defined(_WIN32)           
#undef near
#undef far
#endif

int main(void)
{

    InitWindow(1600, 900, "Game of Life - Cellular Automation");
    SetTargetFPS(60); 
    rlImGuiSetup(true);

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    GameOfLife MainGame(screenHeight, screenHeight, (screenWidth - screenHeight) / 2 , 15);

    int RandomSetNumber = 250;

    while (!WindowShouldClose())    
    {
        // --- Input ---
        
        //  Random set button - R
        if (IsKeyReleased(KEY_R))
        {
            MainGame.SetRandomCells(RandomSetNumber);
        }
        // Running button - SPACE
        if (IsKeyReleased(KEY_SPACE))
        {
            MainGame.isRunning = !MainGame.isRunning;
        }
        //  Clear map button - C
        if (IsKeyReleased(KEY_C))
        {
            MainGame.ResetMap();
        }

        // Update
        MainGame.Update(GetTime());
        
        
        // Draw
        BeginDrawing();
            
            //  Main draw
            ClearBackground(RAYWHITE);

            MainGame.Draw();

            DrawText("Game of Life", 25, 20, 40, BLACK);
            DrawTextEx(GetFontDefault(), TextFormat("Cells: %d", MainGame.AliveCellsCount()), {25, 75}, 30, 2.0f, BLACK);
            DrawText("Space - Start/Stop", 25, 125, 20, GRAY);
            DrawText("R - Random set", 25, 150, 20, GRAY);
            DrawText("C - Clear map", 25, 175, 20, GRAY);
            DrawText("ESC - Exit", 25, 200, 20, GRAY);

            //  Imgui draw
            rlImGuiBegin();
            
            ImGui::Begin("Setting");
                ImGui::Text("Settings Tools");
                ImGui::SliderFloat("Speed Delay", &MainGame.SimDelay, 0.0f, 5.0f);
                ImGui::InputInt("Random Cells", &RandomSetNumber);
            ImGui::End();

            rlImGuiEnd();

        EndDrawing();


    }

    rlImGuiShutdown();
    CloseWindow();        

    return 0;
}

#if defined(_WIN32)   
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow)
{
    main();

    return 0;
}
#endif