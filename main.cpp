#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <vector>
#include <conio.h>  // для _kbhit() и _getch() в Windows

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void setRussianLocale() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, "rus");
}

// Функция для проверки нажатия ESC
bool isEscPressed() {
    if (_kbhit()) {  // если клавиша нажата
        int key = _getch();  // получаем код клавиши
        if (key == 27) {  // 27 - это код клавиши ESC
            return true;
        }
    }
    return false;
}

// просто визуализирует волну
class SimpleWave {
private:
    int width, height;
    double timeValue;
    bool running;

public:
    SimpleWave(int w, int h) : width(w), height(h), timeValue(0), running(true) {
        system("cls");
    }

    void draw() {
        // рисует волну
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // волну делает
                double wave = sin(x * 0.1 + timeValue) * 8;

                // надо ли рисовать символ
                if (y == (height/2 + (int)wave)) {
                    cout << "*";
                }
                else if (y == (height/2 + (int)wave + 1) || y == (height/2 + (int)wave - 1)) {
                    cout << ".";
                }
                else {
                    cout << " ";
                }
            }
            cout << "\n";
        }

        // информация
        cout << "SIMPLE WAVE - Press ESC to exit" << endl;

        // время больше делает
        timeValue += 0.1;

        // курсор в начало возвращает
        cout << "\033[" << height + 3 << "A";
    }

    void run() {
        while (running) {
            draw();

            // Проверяем нажатие ESC
            if (isEscPressed()) {
                running = false;
                cout << "\033[" << height + 5 << "B"; // Отодвигаем курсор вниз
                system("cls");
                cout << "Program stopped by user" << endl;
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
};

// делает звездочку летащую
class FlyingStar {
private:
    int width, height;
    double x, y;
    double vx, vy;
    bool running;

public:
    FlyingStar(int w, int h) : width(w), height(h), x(w/2), y(h/2), vx(1), vy(0.5), running(true) {
        system("cls");
    }

    void draw() {
        system("cls");

        // рисует рамку
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        // рисует поле
        for (int row = 0; row < height; row++) {
            cout << "#";
            for (int col = 0; col < width; col++) {
                if ((int)x == col && (int)y == row) {
                    cout << "*";
                } else {
                    cout << " ";
                }
            }
            cout << "#" << endl;
        }

        // нижняя рамка
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        // информация
        cout << "FLYING STAR - Press ESC to exit" << endl;
        cout << "Position: (" << (int)x << ", " << (int)y << ")" << endl;

        // двигает звездочку
        x += vx;
        y += vy;

        // отскок от стен
        if (x >= width - 1 || x <= 0) vx = -vx;
        if (y >= height - 1 || y <= 0) vy = -vy;
    }

    void run() {
        while (running) {
            draw();

            // Проверяем нажатие ESC
            if (isEscPressed()) {
                running = false;
                system("cls");
                cout << "Program stopped by user" << endl;
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
};

// снегопад делает
class Snowfall {
private:
    int width, height;
    vector<int> snowX;
    vector<int> snowY;
    bool running;

public:
    Snowfall(int w, int h) : width(w), height(h), running(true) {
        // 50 снежинок создает
        for (int i = 0; i < 50; i++) {
            snowX.push_back(rand() % width);
            snowY.push_back(rand() % height);
        }
        system("cls");
    }

    void draw() {
        system("cls");

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bool isSnow = false;
                for (int i = 0; i < snowX.size(); i++) {
                    if (snowX[i] == x && snowY[i] == y) {
                        cout << "*";
                        isSnow = true;
                        break;
                    }
                }
                if (!isSnow) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << "SNOWFALL - Press ESC to exit" << endl;
        cout << "Snowflakes: " << snowX.size() << endl;

        for (int i = 0; i < snowX.size(); i++) {
            snowY[i]++;
            if (snowY[i] >= height) {
                snowY[i] = 0;
                snowX[i] = rand() % width;
            }
        }
    }

    void run() {
        while (running) {
            draw();

            // Проверяем нажатие ESC
            if (isEscPressed()) {
                running = false;
                system("cls");
                cout << "Program stopped by user" << endl;
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
};

int main() {
    setRussianLocale();
    int choice;

    cout << "Choose program:" << endl;
    cout << "1 - Simple Wave" << endl;
    cout << "2 - Flying Star" << endl;
    cout << "3 - Snowfall" << endl;
    cout << "Your choice (1, 2 or 3): ";
    cin >> choice;

    if (choice == 1) {
        SimpleWave wave(78, 20);
        wave.run();
    }
    else if (choice == 2) {
        FlyingStar star(50, 20);
        star.run();
    }
    else {
        Snowfall snow(78, 20);
        snow.run();
    }

    cout << "\nPress any key to exit...";
    _getch();  // Ждем нажатия любой клавиши перед выходом

    return 0;
}
