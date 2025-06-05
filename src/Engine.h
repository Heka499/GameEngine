#pragma once
#include "Core/Logger.h"
#include "Core/Math.h"

namespace GameEngine {

class Engine {
private:
    bool isRunning;

public:
    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    void Update(float deltaTime);
    void Render();
};

} // namespace GameEngine