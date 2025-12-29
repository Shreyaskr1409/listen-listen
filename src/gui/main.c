#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../deps/include/raylib.h"

#define CLAY_IMPLEMENTATION
#include "../../deps/clay/clay.h"
#include "../../deps/clay/renderers/raylib/clay_renderer_raylib.c"

bool reinitializeClay = false;

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
    if (errorData.errorType == CLAY_ERROR_TYPE_ELEMENTS_CAPACITY_EXCEEDED) {
        reinitializeClay = true;
        Clay_SetMaxElementCount(Clay_GetMaxElementCount() * 2);
    } else if (errorData.errorType == CLAY_ERROR_TYPE_TEXT_MEASUREMENT_CAPACITY_EXCEEDED) {
        reinitializeClay = true;
        Clay_SetMaxMeasureTextCacheWordCount(Clay_GetMaxMeasureTextCacheWordCount() * 2);
    }
}

int main(int argc, char *argv[]) {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(clayRequiredMemory, malloc(clayRequiredMemory));

    Clay_Initialize(clayMemory, (Clay_Dimensions) {
        (float) GetScreenWidth(),
        (float) GetScreenHeight()
    }, (Clay_ErrorHandler) {
        HandleClayErrors, 0
    });

    Clay_Raylib_Initialize(1024, 768, "Listen-Listen", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

    while (!WindowShouldClose()) {
        // TODO    
        BeginDrawing();
        ClearBackground((Color) {0, 0, 0, 0});
        EndDrawing();
    }

    printf("Hello world");
    return 0;
}
