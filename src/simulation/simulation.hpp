#pragma once

#include <rendering/window/window.hpp>

class Simulation {
    private:
        Window window{WIDTH, HEIGHT, "Solar System Simulation"};
    public:
        static const int WIDTH = 800;
        static const int HEIGHT = 800;

        void Run();
};