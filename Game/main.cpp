#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Field.h"
#include "Constant.h"
#include "FieldVisualizer.h"
#include "GameControl.h"
#include <mutex>
std::mutex windowMutex;

struct SafeWidnowSFML
{
    std::mutex windowMutex;
    sf::RenderWindow& window;
    bool pollEvent(sf::Event& event)
    {
        std::lock_guard<std::mutex> lock(windowMutex);
        return window.pollEvent(event);
    }
    bool pollEvent(sf::Event& event, int32_t i)
    {
        std::lock_guard<std::mutex> lock(windowMutex);
        std::cout << i << std::endl;
        return window.pollEvent(event);
    }
    SafeWidnowSFML(sf::RenderWindow& window) : window(window)
    {}
    bool isOpen()
    {
        std::lock_guard<std::mutex> lock(windowMutex);
        return window.isOpen();
    }
};


void EventDetection(SafeWidnowSFML& Win, GameControl& controller)
{
    sf::RenderWindow& window = Win.window;
        sf::Event event;
        while (Win.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                // Обработка нажатия клавиши
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Обработка нажатия кнопки мыши
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int32_t mouseX = event.mouseButton.x;
                    int32_t mouseY = event.mouseButton.y;

                    int32_t n = mouseY / CELL_SIZE;
                    int32_t m = mouseX / CELL_SIZE;

                    controller.GetStateCell(n, m);
                }
            }

        }
}
void CommandCin(GameControl& controller)
{
    std::string str;
    int32_t n = 0;
    int32_t m = 0;
    int32_t state = 0;
    while (true)
    {
        std::cin >> str;
        if (str == "set")
        {
            std::cin >> n >> m >> state;
            controller.SetState(n, m, state);
        }
        if (str == "clean")
        {
            controller.Clean();
        }
        if (str == "mix")
        {
            controller.Mix();
        }
        if (str == "runOne")
        {
            controller.runCycle();
        }
        if (str == "run")
        {
            controller.runPeriodic();
        }
        if (str == "runt")
        {
            
            [&controller]() {
                float_t period;
                std::cin >> period;
                controller.runPeriodic(period);
            }();
        }
        
    }
}




int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_WIDTH), "Cellular Automaton");
    SafeWidnowSFML Win(window);

    int32_t rows = window.getSize().y / CELL_SIZE;
    int32_t cols = window.getSize().x / CELL_SIZE;

    CellularAutomata cellularAuto(rows,cols);
    ViewCellularAuto viewCell(window);
    GameControl controller(cellularAuto, viewCell);

    controller.InitCells();
    
   // std::thread eventThread(EventDetection, std::ref(Win));
    std::thread commandThread(CommandCin, std::ref(controller));
    commandThread.detach();

   
    while (Win.isOpen())
    {
      
        sf::Event event; 
        EventDetection(Win, controller);
        while (Win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
       std::this_thread::sleep_for(std::chrono::duration<double>(0.001));
       controller.rendelAuto();
    }
 
    return 0;
}