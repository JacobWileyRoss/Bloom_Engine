
#include "Core/include/Core.h"

int main() {
    Core engine;

    engine.Initialize();
    engine.MainLoop();
    engine.Shutdown();

    return 0;
}