/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "rlgl.h"
#include <stdio.h>

//
#include <stdarg.h>
#include <string.h>
//

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

//Definicion de niveles de verbosidad
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

//Funcion para convertir el nivel de verbosidad a una cadena
const char* LogLevelToString(LogLevel level) {
	switch (level) {
	case LOG_DEBUG: return "DEBUG";
	case LOG_INFO: return "INFO";
	case LOG_WARN: return "WARN";
	case LOG_ERROR: return "ERROR";
	default: return "UNKNOWN";
	}
}

//Implementacion de la funcion DebugLog
void DebugLog(LogLevel level, const char* moduleTag, const char* format, ...) {
	va_list args;
	va_start(args, format);

	//Imprimir el nivel de verbosidad y el tag del modulo
	fprintf(stderr, "[%s] [%s] ", LogLevelToString(level), moduleTag);

    //Imprimir el mensaje formateado
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");

	va_end(args);

    fflush(stderr);  // Forzar la salida inmediata
}


void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    // Set desired texture to be enabled while drawing following vertex data
    rlSetTexture(texture.id);

    // Vertex data transformation can be defined with the commented lines,
    // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
    //rlPushMatrix();
        // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
        //rlTranslatef(2.0f, 0.0f, 0.0f);
        //rlRotatef(45, 0, 1, 0);
        //rlScalef(2.0f, 2.0f, 2.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    // Back Face
    rlNormal3f(0.0f, 0.0f, -1.0f);     // Normal Pointing Away From Viewer
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    // Top Face
    rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    // Bottom Face
    rlNormal3f(0.0f, -1.0f, 0.0f);     // Normal Pointing Down
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    // Right face
    rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    // Left Face
    rlNormal3f(-1.0f, 0.0f, 0.0f);    // Normal Pointing Left
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlEnd();
    //rlPopMatrix();

    rlSetTexture(0);
}

int main (int argc, char** argv)
{
    //Uso de DebugLog
    printf("Antes de DebugLog\n");
    DebugLog(LOG_INFO, "Main", "Iniciando la aplicacion con %d argumentos", argc);
    printf("Después de DebugLog\n");

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    //Leer argumentos de CLI
    int resX = 640;
    int resY = 480;
    bool wantsfullScreen = false;

    //Ruta de Modelo 3D
	//const char* modelPath = "Book.obj"; //Ruta por defecto

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            //std::cout << "arg " << i << argv[i] << endl;
            //Mostrar argumentos provistos
            fprintf(stderr, "arg %i : %s \n", i, argv[i]);
            if (strcmp(argv[i], "-resx") == 0) {
                resX = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-resy") == 0) {
                resY = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-fullscreen") == 0) {
                wantsfullScreen = true;
            }

			////Carga de modelo
			//if (strcmp(argv[i], "-model") == 0) {
			//	modelPath = argv[i + 1];
			//}
        }
    }

	// Create the window and OpenGL context
	InitWindow(resX, resY, "Hello Raylib");
    if (wantsfullScreen) ToggleFullscreen();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture cubeTex = LoadTexture("Tile.png");

	////Modelo 3D
	//Model model = LoadModel(modelPath);
	//Texture2D texture = LoadTexture("Tile.png");
	//model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	
	//Camera
	Camera3D camera = { 0 };
	camera.position = (Vector3){ 4,0,2 };
	camera.target = (Vector3){ 0,0,0 };
	camera.up = (Vector3){ 0,1,0 };
	camera.fovy = 45;
	camera.projection = CAMERA_PERSPECTIVE;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateCamera(&camera, CAMERA_FREE);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(LIGHTGRAY);

		// draw some text using the default font
		//DrawText("Hello Raylib", 200,200,20,WHITE);

		BeginMode3D(camera);
		//DrawCube((Vector3) { 0, 0, 0 }, 1, 1, 1, RED);
        DrawCubeTexture(cubeTex, (Vector3) { 0, 0, 0 }, 2, 2, 2, WHITE);

        //Dibuja el modelo y la posicion
		//DrawModel(model, (Vector3) { 0, 0, 0 }, 1, WHITE);


		DrawGrid(20, 1);

		EndMode3D();

		// draw our texture to the screen
		//DrawTexture(wabbit, 400, 200, WHITE);

		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

    //Carga de modelo y textura
	//UnloadModel(model);
	//UnloadTexture(texture);
     
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}


