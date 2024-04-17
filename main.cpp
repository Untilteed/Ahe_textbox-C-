#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

void area()
{
    int x = 5;
    int y = 3;
    attron(COLOR_PAIR(1));
    for (int i = 0; i < 25; ++i)
    {
        mvprintw(y, x + i, " ");
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

void input()
{
    char input{'0'};
    int count = 0; // Лічильник введених символів
    while (input != '\x1b')
    {
        attron(COLOR_PAIR(2));
        input = getch(); // Отримання наступного введеного символу
        if (input != ERR) // Перевірка, чи введений символ не є помилкою
        {
            if (input == '\x1b') // Перевірка, чи введено символ "Escape"
            {
                attron(COLOR_PAIR(3));
                mvprintw(0, 0, "Ty wyszedles!!!");
                refresh();
                break;
            }
            if (count < 10) // Перевірка кількості введених символів
            {
                printw("%c", input); // Виведення символу на екран
                refresh();
                count++; // Збільшення лічильника введених символів
            }
            if (count == 10) // Перевірка, чи досягнуто ліміту введених символів
            {
                mvprintw(0, 0, "Limit!!!");
                break; // Вихід з циклу, якщо досягнуто ліміту
            }
        }
        attroff(COLOR_PAIR(2));
        refresh();
        this_thread::sleep_for(100ms);
    }
}


int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    area();
    input();

    endwin();
    return 0;
}

