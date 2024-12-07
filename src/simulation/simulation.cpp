#include <simulation/simulation.hpp>

/**
 * @brief Runs the main loop for the simulation.
 *
 * This continues to run until the user closes the window.
 * It is responsible for processing any user input to the window.
 */
void Simulation::Run() {
    // Main loop
    while (!window.ShouldClose()) {
        window.ProcessInput();

        window.Render();
    }
}