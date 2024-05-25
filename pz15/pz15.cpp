#include <iostream>

using namespace std;

int main()
{
    const float STEP = 0.3, EIGHT = 8.0, THREE = 3.0;
    float x = 0.2;
    float ln8, tempX, lnX;

    for (int i = 0; i < 5; i++) {
        float y;
        cout << "X(" << i + 1 << ") = " << x << endl;
        __asm {
            finit                   // Ініціалізуємо стан FPU
            fld x                   // Завантажуємо x у стек
            fmul st(0), st(0)       // x^2
            fld1                    // Завантажуємо 1 у стек
            fadd st(0), st(1)       // Додаємо 1 зі стеку до квадрата x
            fstp tempX              // Зберігаємо результат у змінну tempX
            fld1                    // Завантажуємо 1 у стек
            fld EIGHT               // Завантажуємо eight = 8 у стек
            fyl2x                   // Обчислюємо y * log2(x), тобто ln(8)
            fstp ln8                // Зберігаємо ln(8) у змінну ln8
            fld1                    // Завантажуємо 1 у стек
            fld tempX               // Завантажуємо tempX у стек
            fyl2x                   // Обчислюємо y * log2(x), тобто ln(tempX)
            fstp lnX                // Зберігаємо ln(tempX) у змінну lnX
            fld lnX                 // Завантажуємо ln(tempX) у стек
            fld ln8                 // Завантажуємо ln(8) у стек
            fdiv                    // Ділимо ln(lnX) на ln(8)
            fld THREE               // Завантажуємо three = 3 у стек
            fmul                    // Множимо результат log8(lnX) на 3
            fstp y                  // Зберігаємо результат у змінну y
        };
        cout << "Y(" << i + 1 << ") = " << y << endl;
        x += STEP;
        cout << endl;
    }
}

