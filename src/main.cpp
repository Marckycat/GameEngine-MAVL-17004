/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <chrono>

#include "raylib.h"
#include "rlgl.h"
#include <stdio.h>
#include <iostream>
//#include <fstream>

#include "GameObject.h"
#include "MemoryManager.h"
#include "AudioManager.h"
#include "LabelComponent.h"
#include "ConfigManager.h"
#include "LogManager.h"

#include <lua.hpp>
//
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ini.h>
#include <time.h>

#define AVATAR_URL "https://avatars.githubusercontent.com/u/116173416"
#define AVATAR_FILE "avatar.png"
//

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>

extern "C" {
#include "md5.h"
}

//Variables globales para Raylib
Color brushColor = WHITE;

//Funciones expuestas a Lua
int Clear(lua_State* L) {
	int r = (int)lua_tonumber(L, 1);
	int g = (int)lua_tonumber(L, 2);
	int b = (int)lua_tonumber(L, 3);
    ClearBackground(Color{ static_cast<unsigned char>(r), 
        static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255 });
	return 0;
}

int SetBrushColor(lua_State* L) {
    int r = (int)lua_tonumber(L, 1);
    int g = (int)lua_tonumber(L, 2);
    int b = (int)lua_tonumber(L, 3);
    brushColor = (Color{ static_cast<unsigned char>(r),
        static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255 });
    return 0;
}

int DrawCircle(lua_State* L) {
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	int radius = (float)lua_tonumber(L, 3);
	DrawCircle((int)x, (int)y, radius, brushColor);
	return 0;
}

int DrawRect(lua_State* L) {
	int x = (float)lua_tonumber(L, 1);
	int y = (float)lua_tonumber(L, 2);
	int width = (float)lua_tonumber(L, 3);
	int height = (float)lua_tonumber(L, 4);
	DrawRectangle((int)x, (int)y, (int)width, (int)height, brushColor);
	return 0;
}

int DrawLine(lua_State* L) {
	int x1 = (float)lua_tonumber(L, 1);
	int y1 = (float)lua_tonumber(L, 2);
	int x2 = (float)lua_tonumber(L, 3);
	int y2 = (float)lua_tonumber(L, 4);
	DrawLine((int)x1, (int)y1, (int)x2, (int)y2, brushColor);
	return 0;
}

//Biblioteca de funciones para Lua
int lua_mymodule(lua_State* L) {
	static const luaL_Reg myModule[] = {
		{"Clear", Clear},
		{"SetBrushColor", SetBrushColor},
		{"DrawCircle", DrawCircle},
		{"DrawRect", DrawRect},
		{"DrawLine", DrawLine},
		{NULL, NULL}
	};
    luaL_newlib(L, myModule);
	return 1;
}

//Ejecuta la funcion Draw() de Lua
void luaDraw(lua_State* L, float dt) {
	lua_getglobal(L, "Draw");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, dt);
        if (lua_pcall(L, 1, 0, 0) != 0) {
            std::cout << "Error en Draw(): " << lua_tostring(L, 1) << std::endl;
        }
    }
}

void DownloadAvatar() {
    char command[512];
    snprintf(command, sizeof(command), "curl -s -o %s %s", AVATAR_FILE, AVATAR_URL);
    int result = system(command);
    if (result != 0) {
        printf("Error downloading avatar.\n");
    }
}

//Definicion de niveles de verbosidad
enum LogLevel {
    L_DEBUG,
    L_INFO,
    L_WARN,
    L_ERROR
};

//Funcion para convertir el nivel de verbosidad a una cadena 
const char* LogLevelToString(LogLevel level) {
	switch (level) {
	case L_DEBUG: return "DEBUG";
	case L_INFO: return "INFO";
	case L_WARN: return "WARN";
	case L_ERROR: return "ERROR";
	default: return "UNKNOWN";
	}
}

//Implementacion de la funcion DebugLog y que escribe el archivo
void DebugLog(LogLevel level, const char* moduleTag, const char* format, ...) {
	va_list args;
	va_start(args, format);

    //Obtener la hora actual
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    //Abrir el archivo de log en modo "append"
	FILE* logFile = fopen("log.txt", "a");
    if (!logFile) {
		fprintf(stderr, "[ERROR] [DebugLog] No se pudo abrir el archivo de log\n");
        return;
    }

    // Formatear la hora
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);

    // Imprimir en stderr
    fprintf(stderr, "[%s] [%s] [%s] ", timeStr, LogLevelToString(level), moduleTag);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    // Escribir en el archivo de log
    fprintf(logFile, "[%s] [%s] [%s] ", timeStr, LogLevelToString(level), moduleTag);
    vfprintf(logFile, format, args);
    fprintf(logFile, "\n");

	////Imprimir el nivel de verbosidad y el tag del modulo 
	//fprintf(stderr, "[%s] [%s] ", LogLevelToString(level), moduleTag);

 //   //Imprimir el mensaje formateado
	//vfprintf(stderr, format, args);
	//fprintf(stderr, "\n");

    //Cerrar el archivo
	fclose(logFile);

	va_end(args);
    fflush(stderr);  // Forzar la salida inmediata
}

typedef struct {
	int resX;
	int resY;
	bool fullscreen;
	//const char* modelPath;
} Config;;

int IniHandler(void* user, const char* section, const char* name, const char* value) {
    Config* config = (Config*)user;

    if (strcmp(name, "resX") == 0) config->resX = atoi(value);
    else if (strcmp(name, "resY") == 0) config->resY = atoi(value);
    else if (strcmp(name, "fullscreen") == 0) config->fullscreen = atoi(value);

    return 1;
}

void LoadConfig(Config* config, const char* filename) {
    if (ini_parse(filename, IniHandler, config) < 0) {
        DebugLog(L_WARN, "Config", "Archivo %s no encontrado, usando valores por defecto.");
    }
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

int main (int argc, char** argv) {
    //Prueba de md5
    char* input = "hola mundo";
    uint8_t result[16];
    md5String(input, result);
    for (int i = 0; i < 16; i++) {
        printf("%02x", result[i]);
    }
    char hash[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)result[i]);
    }
    puts("");
    std::cout << hash << std::endl;

    //Pruebas del Component
    auto now = std::chrono::system_clock::now();
    auto nowc = std::chrono::system_clock::to_time_t(now);
    char msg[100];
    sprintf(msg, "Super Engine de Marco, %s", ctime(&nowc));
    LOGI(msg, "main");

    //Uso de DebugLog
    DebugLog(L_INFO, "Main", "Iniciando la aplicacion con %d argumentos", argc);
    DebugLog(L_ERROR, "Render", "No se pudo cargar la textura: %s", "Tile.png");

    // Descargar la imagen si no existe
    FILE* file = fopen(AVATAR_FILE, "r");
    if (!file) {
        DownloadAvatar();
    }
    else {
        fclose(file);
    }

	Config config = { 640, 480, false };
	LoadConfig(&config, "config.ini");

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    //Leer argumentos de CLI
    /*int resX = 640;
    int resY = 480;
    bool wantsfullScreen = false;*/

    //Ruta de Modelo 3D
	//const char* modelPath = "Book.obj"; //Ruta por defecto

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            //std::cout << "arg " << i << argv[i] << endl;
            //Mostrar argumentos provistos
            fprintf(stderr, "arg %i : %s \n", i, argv[i]);
            if (strcmp(argv[i], "-resx") == 0) {
				config.resX = atoi(argv[i + 1]);
                //resX = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-resy") == 0) {
                config.resY = atoi(argv[i + 1]);
                //resY = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-fullscreen") == 0) {
                config.fullscreen = true;
                //wantsfullScreen = true;
            }

			////Carga de modelo
			//if (strcmp(argv[i], "-model") == 0) {
			//	modelPath = argv[i + 1];
			//}
        }
    }

	// Create the window and OpenGL context
	//InitWindow(resX, resY, "Hello Raylib");
    InitWindow(config.resX, config.resY, "Hello Raylib");

    //Incializar Lua
	lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_requiref(L, "SimpleDraw", lua_mymodule, 1);
    lua_pop(L, 1);

    if (luaL_dofile(L, "main.lua")) {
        std::cout << "Error en Draw(): " << lua_tostring(L, -1) << std::endl;
    }

    //Prueba de GameObject
    /*GameObject* myObj = new GameObject();
    myObj->init();
    myObj->setVelocity({ 100, 100 });
    GameObject* otro = new GameObject();
    otro->init({ 100,100 }, { 1,1 }, BLUE);*/
    //para iterar en todos los objetos
    std::vector<GameObject*> gameObjects;

    //GameObject* k = GameObject::Spawn({ 200,200 }, { 1,1 }, "coso");
    for (int i = 0; i < 10; i++) {
        GameObject* k = GameObject::Spawn({ 5.f * i, 5.f * i }, { 100, 5.f * i }, "coso");
        k->enabled = i % 2 == 0;
        gameObjects.push_back(k);

    }
    MemoryManager::getInstance()->alloc(800 * 1024 * 1024);

    //if (wantsfullScreen) ToggleFullscreen();
    if (config.fullscreen) ToggleFullscreen();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	//Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture cubeTex = LoadTexture("Tile.png");
    //Texture cubeT = LoadTexture("Skeleton.png");

    //Textura del avatar
    Image avatar = LoadImage(AVATAR_FILE);
    Texture2D avatarTexture = LoadTextureFromImage(avatar);
    UnloadImage(avatar);

	////Modelo 3D
	//Model model = LoadModel(modelPath);
	//Texture2D texture = LoadTexture("Tile.png");
	//model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	
	//Camera
	Camera3D camera = { 0 };
	camera.position = { 4,0,2 };
	camera.target = { 0,0,0 };
	camera.up = { 0,1,0 };
	camera.fovy = 45;
	camera.projection = CAMERA_PERSPECTIVE;

    //
    GameObject* go = new GameObject();
    ptrComponent newComp = std::make_shared<LabelComponent>();
    go->AddComponent(newComp);

    std::vector<GameObject*> gameobjects;
    for (int i = 0; i < 100; i++) {
        GameObject* go = new GameObject();
        ptrComponent newComp = std::make_shared<LabelComponent>();
        go->AddComponent(newComp);
        gameobjects.push_back(go);
    }


    //AudioManager::getInstance()->LoadBackgroundMusic("PowerfulMario.mp3");
    AudioManager::getInstance()->LoadBackgroundMusic("Slider.mp3");
    AudioManager::getInstance()->PlayBGM();
    /*InitAudioDevice();
    Music m = LoadMusicStream("PowerfulMario.mp3");
    PlayMusicStream(m);*/

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
        AudioManager::getInstance()->Update();

        //UpdateMusicStream(m);
        UpdateCamera(&camera, CAMERA_FREE);

        //Update our game Objects
		for (int i = 0; i < gameObjects.size(); i++) {
            if(gameObjects[i]->enabled)
                gameObjects[i]->update();
		}
        
        for (auto& go : gameobjects) {
            go->Update(GetFrameTime());
        }

		// drawing
		BeginDrawing();

        for (auto& go : gameobjects) {
            go->Draw(GetFrameTime());
        }
        
        // Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(RAYWHITE);

		// draw some text using the default font
		DrawText("Configuracion Cargada", 200,200,20,DARKGRAY);

		BeginMode3D(camera);
		//DrawCube((Vector3) { 0, 0, 0 }, 1, 1, 1, RED);
        DrawCubeTexture(cubeTex, { 0, 0, 0 }, 2, 2, 2, WHITE);
        //DrawCubeTexture(cubeT, { 0, 0, 0 }, 2, 2, 2, WHITE);

        //Dibuja el modelo y la posicion
		//DrawModel(model, (Vector3) { 0, 0, 0 }, 1, WHITE);
        
        // Dibujar la marca de agua en la esquina inferior derecha
        DrawTexture(avatarTexture, GetScreenWidth() - avatarTexture.width - 10, GetScreenHeight() - avatarTexture.height - 10, WHITE);

		DrawGrid(20, 1);

		EndMode3D();

		// draw our texture to the screen
		//DrawTexture(wabbit, 400, 200, WHITE);

		//Actualizar los GameObjects
        //myObj->draw();
        //otro->draw();
        //Update our GameObjects
        for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->draw();
        }

		//Llamar la funcion Draw() de Lua
        luaDraw(L, GetFrameTime()); 

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	//UnloadTexture(wabbit);
    
    //Carga de modelo y textura
	//UnloadModel(model);
	//UnloadTexture(texture);
     
    //Carga del avatar
    UnloadTexture(avatarTexture);
     
    //Cerrar Lua
	lua_close(L);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}


