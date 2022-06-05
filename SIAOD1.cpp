#include <iostream> //Для построчного ввода
#include <random> //Для псевдорандомных генераторов
#include <string> //Для построчного ввода
#include <vector> //Для вектора
#define CURSOR_HOME printf("\x1B[H") //Для передвижения курсора отсюдава
#define GOTO_LINE_CHAR(line, charr) printf("\x1B[%d;%dH", line, charr)
#define GOTO_CHAR(line) printf("\x1B[%dG", line)
#define UP_LINES(i) printf("\x1B[%dA", i)
#define DOWN_LINES(i) printf("\x1B[%dB", i)
#define RIGHT_CHARS(i) printf("\x1B[%dC", i)
#define LEFT_CHARS(i) printf("\x1B[%dD", i) //Досюдава
#define ERASE_CURRENT_LINE printf("\x1B[2K") //Стирает настоящую строчку
#define CLE0AR_SCREEN printf("\x1B[2J") //Чистит экран
#define RESET_TEXT_FORMATTING printf("\x1B[0m") //Отменяет любое форматирование текста
#define PRINT_CHAR(s) printf("%c", s[0]) //Печатает первый символ данной строки
#define HW printf("═") //Для построения коробочек интерфейса отсюдава
#define VW printf("║")
#define MW printf("╬")
#define NL printf("\n")
#define TRC printf("╗")
#define TLC printf("╔")
#define BRC printf("╝")
#define BLC printf("╚")
#define TMW printf("╦")
#define BMW printf("╩")
#define RMW printf("╣")
#define LMW printf("╠") //Досюдава
using namespace std;
wstring input(L""); int inpn(0);//Для ввода
const int maxstatic(10); int *dynamicos; vector<int> vectoras;
/*ver0.3*/ //Функция для определения цифрового корня //Если число 0, то его цифровой корень тоже 0. В противном случае ответ = 9 в случае остаток = 0 или ответ = остаток от деления
short digroot(long long a)
{
    return (a == 0) ? 0 : (a % 9 == 0) ? 9 : (a > 0) ? a % 9 : -a % 9;
}
int randi(int a, int z) //Генератор псевдослучайных целых чисел отсюдава
{
    random_device rd;
    mt19937_64 mt(rd());
    uniform_int_distribution<int> range(a, z); /*int for ints, real for floats*/
    return range(mt);
} //Досюдава
long double randld(long double a, long double z) //Генератор псевдослучайных нецелых чисел отсюдава
{
    random_device rd;
    mt19937_64 mt(rd());
    uniform_real_distribution<long double> range(a, z); /*int for ints, real for floats*/
    return range(mt);
} //Досюдава
void clearscreen()
{
    int e(50); while (e) { DOWN_LINES(1); ERASE_CURRENT_LINE; --e; } e = 100;
    while (e) { UP_LINES(1); ERASE_CURRENT_LINE; --e; }
}
void personal()
{
    TLC; for (short e(0); e < 50; ++e) { HW; } TRC; NL;
    VW; printf("Согласно персональному варианту 7, удовлетворяющие"); VW; NL;
    VW; printf("условию элементы(УУЭ) имеют цифровой корень 7."); GOTO_CHAR(52); VW; NL;
    BLC; for (short e(0); e < 50; ++e) { HW; } BRC; NL;
}
bool okinput(wstring input)
{
    bool minus(false);
    for (short c(0); c < input.size(); ++c)
    {
        if (input[c] == '-') { if (minus) { return false; } minus = true; }
        else if ((isalpha(input[c])) || (!isalpha(input[c]) && !isdigit(input[c]))) { return false; }
    }
    return true;
}
short staticuno(int arr[], int filled)
{
    if (filled == 0) { return -2; }
    for (int index(0); index < filled; ++index)
    {
        if (digroot(arr[index]) == 7) { return index; }
    }
    return -1;
}
short staticdos(int *arr, int maxels, int &filled, int insertion)
{
    if (filled == 0) { return -1; }
    bool found(false);
    if (filled == maxels) { return -2; }
    else
    {
        for (int e(0); e < filled; ++e)
        {
            if (digroot(arr[e]) == 7)
            {
                for (int o(maxels - 1); o > e; --o) { arr[o] = arr[o - 1]; }
                arr[e] = insertion;
                ++filled; return 1;
            }
        }
    }
    return 0;
}
short statictres(int *arr, int maxels, int &filled)
{
    if (filled == 0) { return -1; }
    bool found(false);
    for (int e(0); e < filled; ++e)
    {
        if (digroot(arr[e]) == 7)
        {
            for (int o(e); o < maxels - 1; ++o)
            {
                arr[o] = arr[o + 1];
            }
            --e; --filled; found = true;
        }
    }
    return (found) ? 1 : 0;
}
short dynamicuno(int *arr, int filled)
{
    if (filled == 0) { return -2; }
    for (int index(0); index < filled; ++index)
    {
        if (digroot(arr[index]) == 7) { return index; }
    }
    return -1;
}
short dynamicdos(int*& arr, int &filled, int insertion)
{
    if (filled == 0) { return -1; }
    bool found(false);
    for (int e(0); e < filled; ++e)
    {
        if (digroot(arr[e]) == 7)
        {
            arr = (int*)realloc(arr, (filled + 1) * sizeof(int));
            for (int o(filled); o > e; --o) { arr[o] = arr[o - 1]; }
            arr[e] = insertion;
            ++filled; return 1;
        }
    }
    return 0;
}
short dynamictres(int*& arr, int &filled)
{
    if (filled == 0) { return -1; }
    bool found(false);
    for (int e(0); e < filled; ++e)
    {
        if (digroot(arr[e]) == 7)
        {
            for (int o(e); o < filled; ++o)
            {
                arr[o] = arr[o + 1];
            }
            --e; --filled; found = true;
            arr = (int*)realloc(arr, (filled) * sizeof(int));
        }
    }
    return (found) ? 1 : 0;
}
short vectoruno(vector<int> vec, int filled)
{
    if (filled == 0) { return -2; }
    for (int index(0); index < filled; ++index)
    {
        if (digroot(vec[index]) == 7) { return index; }
    }
    return -1;
}
short vectordos(vector<int>& vec, int &filled, int insertion)
{
    if (filled == 0) { return -1; }
    bool found(false);
    for (int e(0); e < filled; ++e)
    {
        if (digroot(vec[e]) == 7)
        {
            vec.insert(vec.begin() + e, insertion);
            ++filled; return 1;
        }
    }
    return 0;
}
short vectortres(vector<int>& vec, int &filled)
{
    if (filled == 0) { return -1; }
    bool found(false);
    for (int e(0); e < filled; ++e)
    {
        if (digroot(vec[e]) == 7)
        {
            for (int o(e); o < filled - 1; ++o)
            {
                vec[o] = vec[o + 1];
            }
            --e; --filled; found = true; vectoras.erase(vectoras.end() - 1);
        }
    }
    return (found) ? 1 : 0;
}
/*template <typename T> ver0.1 Позапрошлая версия функции для первой практической
T digroot(T n)
{
    while (n > 9)
    {
        T t(0);
        while (n)
        {
            t += n % 10;
            n /= 10;
        }
        n = t;
    }
    return n;
}
template <typename T> ver0.2 Прошлая версия функции для первой практической
T digroot(T n)
{
    if (!n)
    {
        return n;
    }
    for (T e(9); e; --e)
    {
        if ((n - e) % 9)
        {
            continue;
        }
        return e;
    }
}*/
//short getsize(int array[]) //TODO otsudava
//{
//    short res(0); for (auto lol : array) { ++res; }
//} //Dosudava
int main()
{
    setlocale(LC_ALL, "Russian_Russia.65001"); int cassio(0), insertion(0); bool showarr(false), breaker(false), erase(false), insert(false), detect(false);
    string whatarr[]{ "Статический массив", "Динамический массив", "Вектор", "Ни с чем, закройся" },
        whatdo[]{ "Найти индекс первого УУЭ", "Вставить новый элемент перед 'единственным' УУЭ", "Удалить все УУЭ", "Заполнить автоматически", "Заполнить вручную", "Показать массив", "Вернуться в предыдущее меню" };
    const int fsize(4), ssize(7);
    while (true)
    {
        int filled(0);
        CURSOR_HOME; clearscreen(); personal();
        printf("С чем работать желаем?"); NL;
        for (short e(0); e < fsize; ++e)
        {
            if (e == 0)
            {
                TLC;
                for (short o(0); o < 3; ++o)
                {
                    HW;
                }
                TMW;
                for (short o(0); o < 19; ++o)
                {
                    HW;
                }
                TRC;
                NL;
            }
            VW; printf(" %d ", e + 1); VW;
            printf("%s", whatarr[e].c_str()); GOTO_CHAR(25); VW; NL; //53
            if (e == fsize - 1)
            {
                BLC;
                for (short o(0); o < 3; ++o)
                {
                    HW;
                }
                BMW;
                for (short o(0); o < 19; ++o)
                {
                    HW;
                }
                BRC;
                NL;
            }
            else
            {
                LMW; for (short o(0); o < 3; ++o) { HW; }
                MW; for (short o(0); o < 19; ++o) { HW; }
                RMW; NL;
            }
        }
        while (true)
        {
            printf(">");
            getline(wcin, input);
            inpn = wcstoll(input.c_str(), NULL, 10);
            ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
            cassio = inpn;
            if (inpn > 0 && inpn <= 4) { break; }
        }
        switch (cassio)
        {
        case (1): //Static
        {
            int staticos[maxstatic]{ 0 };
            while (true)
            {
                if (breaker) { breaker = false; break; }
                CURSOR_HOME; clearscreen(); personal(); //Рисуем меню отсюдава
                printf("%s: Что желаете сделать?\n", whatarr[cassio - 1].c_str());
                for (short e(0); e < ssize; ++e)
                {
                    if (e == 0)
                    {
                        TLC;
                        for (short o(0); o < 3; ++o)
                        {
                            HW;
                        }
                        TMW;
                        for (short o(0); o < 47; ++o)
                        {
                            HW;
                        }
                        TRC;
                        NL;
                    }
                    VW; printf(" %d ", e + 1); VW;
                    printf("%s", whatdo[e].c_str()); GOTO_CHAR(53); VW; NL; //53
                    if (e == ssize - 1)
                    {
                        BLC;
                        for (short o(0); o < 3; ++o)
                        {
                            HW;
                        }
                        BMW;
                        for (short o(0); o < 47; ++o)
                        {
                            HW;
                        }
                        BRC;
                        NL;
                    }
                    else
                    {
                        LMW; for (short o(0); o < 3; ++o) { HW; }
                        MW; for (short o(0); o < 47; ++o) { HW; }
                        RMW; NL;
                    }
                } //Досюдава
                if (erase)
                {
                    erase = false;
                    switch (statictres(staticos, maxstatic, filled))
                    {
                    case (1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элементы были найдены и удалены."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (0):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элементы не были найдены."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                else if (insert)
                {
                    insert = false;
                    switch (staticdos(staticos, maxstatic, filled, insertion))
                    {
                    case (1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Вставка прошла успешно."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (0):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элемент не был найден."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-2):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Нет места для вставки."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                else if (detect)
                {
                    detect = false;
                    switch (staticuno(staticos, filled))
                    {
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элемент не был найден."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-2):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    default:
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("УУЭ имеет индекс %d.", staticuno(staticos, filled)); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                if (showarr) { DOWN_LINES(2); printf("Массив: "); for (int e(0); e < filled; ++e) { printf("%d", staticos[e]); if (e != filled - 1) { printf(", "); } } showarr = false; UP_LINES(2); GOTO_CHAR(1); }
                while (true)
                {
                    printf(">");
                    getline(wcin, input);
                    inpn = wcstoll(input.c_str(), NULL, 10);
                    ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                    if (inpn > 0 && inpn <= 7) { break; }
                }
                switch (inpn)
                {
                case (1):
                {
                    detect = true;
                    break;
                }
                case (2):
                {
                    insert = true;
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Введите вставляемое значение."); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (okinput(input)) { break; }
                    }
                    insertion = inpn;
                    break;
                }
                case (3):
                {
                    erase = true;
                    break;
                }
                case (4):
                {
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Сколько значений заполнить?"); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (inpn > 0 && inpn <= maxstatic) { break; }
                    }
                    int temp(inpn); if (temp > filled) { filled = temp; }
                    for (short e(0); e < temp; ++e)
                    {
                        staticos[e] = randi(0, 1000);
                    }
                    break;
                }
                case (5):
                {
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Сколько значений вводите?"); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (inpn > 0 && inpn <= maxstatic) { break; }
                    }
                    int temp(inpn); if (temp > filled) { filled = temp; }
                    for (short e(1); e <= temp; ++e)
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; GOTO_CHAR(1); printf("Введите %d элемент", e); UP_LINES(2); GOTO_CHAR(1);
                        while (true)
                        {
                            printf(">");
                            getline(wcin, input);
                            inpn = wcstoll(input.c_str(), NULL, 10);
                            ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                            if (okinput(input)) { break; }
                        }
                        staticos[e - 1] = inpn;
                        DOWN_LINES(3); GOTO_CHAR(1); for (int tomp(0); tomp <= e - 1; ++tomp) { printf("%d", staticos[tomp]); if (tomp != e - 1) { printf(", "); } } UP_LINES(3);
                    }
                    break;
                }
                case (6):
                {
                    showarr = true; break;
                }
                case (7):
                {
                    breaker = true;
                }
                }
            }
            break;
        }
        case (2): //Dynamic
        {
            while (true)
            {
                if (breaker) { breaker = false; break; }
                CURSOR_HOME; clearscreen(); personal(); //Рисуем меню отсюдава
                printf("%s: Что желаете сделать?\n", whatarr[cassio - 1].c_str());
                for (short e(0); e < ssize; ++e)
                {
                    if (e == 0)
                    {
                        TLC;
                        for (short o(0); o < 3; ++o)
                        {
                            HW;
                        }
                        TMW;
                        for (short o(0); o < 47; ++o)
                        {
                            HW;
                        }
                        TRC;
                        NL;
                    }
                    VW; printf(" %d ", e + 1); VW;
                    printf("%s", whatdo[e].c_str()); GOTO_CHAR(53); VW; NL; //53
                    if (e == ssize - 1)
                    {
                        BLC;
                        for (short o(0); o < 3; ++o)
                        {
                            HW;
                        }
                        BMW;
                        for (short o(0); o < 47; ++o)
                        {
                            HW;
                        }
                        BRC;
                        NL;
                    }
                    else
                    {
                        LMW; for (short o(0); o < 3; ++o) { HW; }
                        MW; for (short o(0); o < 47; ++o) { HW; }
                        RMW; NL;
                    }
                } //Досюдава
                if (erase)
                {
                    erase = false;
                    switch (dynamictres(dynamicos, filled))
                    {
                    case (1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элементы были найдены и удалены."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (0):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элементы не были найдены."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                if (insert)
                {
                    insert = false;
                    switch (dynamicdos(dynamicos, filled, insertion))
                    {
                    case (1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Вставка прошла успешно."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (0):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элемент не был найден."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                else if (detect)
                {
                    detect = false;
                    switch (dynamicuno(dynamicos, filled))
                    {
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элемент не был найден."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-2):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    default:
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("УУЭ имеет индекс %d.", dynamicuno(dynamicos, filled)); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                if (showarr) { DOWN_LINES(2); printf("Массив: "); for (int e(0); e < filled; ++e) { printf("%d", dynamicos[e]); if (e != filled - 1) { printf(", "); } } showarr = false; UP_LINES(2); GOTO_CHAR(1); }
                while (true)
                {
                    printf(">");
                    getline(wcin, input);
                    inpn = wcstoll(input.c_str(), NULL, 10);
                    ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                    if (inpn > 0 && inpn <= 7) { break; }
                }
                switch (inpn)
                {
                case (1):
                {
                    detect = true;
                    break;
                }
                case (2):
                {
                    insert = true;
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Введите вставляемое значение."); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (okinput(input)) { break; }
                    }
                    insertion = inpn;
                    break;
                }
                case (3):
                {
                    erase = true;
                    break;
                }
                case (4):
                {
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Сколько значений заполнить?"); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (inpn > 0 && inpn <= 100) { break; }
                    }
                    int temp(inpn); if (temp > filled) { filled = temp; }
                    dynamicos = (int*)realloc(dynamicos, filled * sizeof(int));
                    for (short e(0); e < temp; ++e)
                    {
                        dynamicos[e] = randi(0, 1000);
                    }
                    break;
                }
                case (5):
                {
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Сколько значений вводите?"); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (inpn > 0 && inpn <= 100) { break; }
                    }
                    int temp(inpn); if (temp > filled) { filled = temp; }
                    dynamicos = (int*)realloc(dynamicos, filled * sizeof(int));
                    for (short e(1); e <= temp; ++e)
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; GOTO_CHAR(1); printf("Введите %d элемент", e); UP_LINES(2); GOTO_CHAR(1);
                        while (true)
                        {
                            printf(">");
                            getline(wcin, input);
                            inpn = wcstoll(input.c_str(), NULL, 10);
                            ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                            if (okinput(input)) { break; }
                        }
                        dynamicos[e - 1] = inpn;
                        DOWN_LINES(3); GOTO_CHAR(1); for (int tomp(0); tomp <= e - 1; ++tomp) { printf("%d", dynamicos[tomp]); if (tomp != e - 1) { printf(", "); } } UP_LINES(3);
                    }
                    break;
                }
                case (6):
                {
                    showarr = true; break;
                }
                case (7):
                {
                    breaker = true;
                }
                }
            }
            break;
        }
        case (3): //Досюдава
        {
            while (true)
            {
                if (breaker) { breaker = false; break; }
                CURSOR_HOME; clearscreen(); personal(); //Рисуем меню отсюдава
                printf("%s: Что желаете сделать?\n", whatarr[cassio - 1].c_str());
                for (short e(0); e < ssize; ++e)
                {
                    if (e == 0)
                    {
                        TLC;
                        for (short o(0); o < 3; ++o)
                        {
                            HW;
                        }
                        TMW;
                        for (short o(0); o < 47; ++o)
                        {
                            HW;
                        }
                        TRC;
                        NL;
                    }
                    VW; printf(" %d ", e + 1); VW;
                    printf("%s", whatdo[e].c_str()); GOTO_CHAR(53); VW; NL; //53
                    if (e == ssize - 1)
                    {
                        BLC;
                        for (short o(0); o < 3; ++o)
                        {
                            HW;
                        }
                        BMW;
                        for (short o(0); o < 47; ++o)
                        {
                            HW;
                        }
                        BRC;
                        NL;
                    }
                    else
                    {
                        LMW; for (short o(0); o < 3; ++o) { HW; }
                        MW; for (short o(0); o < 47; ++o) { HW; }
                        RMW; NL;
                    }
                } //Досюдава
                if (erase)
                {
                    erase = false;
                    switch (vectortres(vectoras, filled))
                    {
                    case (1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элементы были найдены и удалены."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (0):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элементы не были найдены."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                else if (insert)
                {
                    insert = false;
                    switch (vectordos(vectoras, filled, insertion))
                    {
                    case (1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Вставка прошла успешно."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (0):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элемент не был найден."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                else if (detect)
                {
                    detect = false;
                    switch (vectoruno(vectoras, filled))
                    {
                    case (-1):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Элемент не был найден."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    case (-2):
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Пусто. Для начала введите что-нибудь."); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    default:
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; printf("УУЭ имеет индекс %d.", vectoruno(vectoras, filled)); UP_LINES(2); GOTO_CHAR(1);
                        break;
                    }
                    }
                }
                if (showarr) { DOWN_LINES(2); printf("Массив: "); for (int e(0); e < filled; ++e) { printf("%d", vectoras[e]); if (e != filled - 1) { printf(", "); } } showarr = false; UP_LINES(2); GOTO_CHAR(1); }
                while (true)
                {
                    printf(">");
                    getline(wcin, input);
                    inpn = wcstoll(input.c_str(), NULL, 10);
                    ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                    if (inpn > 0 && inpn <= 7) { break; }
                }
                switch (inpn)
                {
                case (1):
                {
                    detect = true;
                    break;
                }
                case (2):
                {
                    insert = true;
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Введите вставляемое значение."); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (okinput(input)) { break; }
                    }
                    insertion = inpn;
                    break;
                }
                case (3):
                {
                    erase = true;
                    break;
                }
                case (4):
                {
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Сколько значений заполнить?"); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (inpn > 0 && inpn <= 100) { break; }
                    }
                    int temp(inpn); if (temp > filled) { filled = temp; }
                    for (short e(0); e < (vectoras.size() - temp); ++e)
                    {
                        vectoras.insert(vectoras.begin(), 0);
                    }
                    for (short e(0); e < temp; ++e)
                    {
                        vectoras[e] = randi(0, 1000);
                    }
                    break;
                }
                case (5):
                {
                    DOWN_LINES(2); ERASE_CURRENT_LINE; printf("Сколько значений вводите?"); UP_LINES(2); GOTO_CHAR(1);
                    while (true)
                    {
                        printf(">");
                        getline(wcin, input);
                        inpn = wcstoll(input.c_str(), NULL, 10);
                        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                        if (inpn > 0 && inpn <= 100) { break; }
                    }
                    int temp(inpn); if (temp > filled) { filled = temp; }
                    for (short e(0); e < (vectoras.size() - temp); ++e)
                    {
                        vectoras.insert(vectoras.begin(), 0);
                    }
                    for (short e(1); e <= temp; ++e)
                    {
                        DOWN_LINES(2); ERASE_CURRENT_LINE; GOTO_CHAR(1); printf("Введите %d элемент", e); UP_LINES(2); GOTO_CHAR(1);
                        while (true)
                        {
                            printf(">");
                            getline(wcin, input);
                            inpn = wcstoll(input.c_str(), NULL, 10);
                            ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
                            if (okinput(input)) { break; }
                        }
                        vectoras[e - 1] = inpn;
                        DOWN_LINES(3); GOTO_CHAR(1); for (int tomp(0); tomp <= e - 1; ++tomp) { printf("%d", vectoras[tomp]); if (tomp != e - 1) { printf(", "); } } UP_LINES(3);
                    }
                    break;
                }
                case (6):
                {
                    showarr = true; break;
                }
                case (7):
                {
                    breaker = true;
                }
                }
            }
            break;
        }
        case (4):
        {
            CURSOR_HOME; //GRUSTNO отсюдава
            clearscreen();
            printf(R"( `..`-'`'` ` ``.'--`  .`-.- ' .''  -' `   .''' .  '.`  `` - `..''- -'..--  ` `'```.. ``- `. `--`..'.`..``-.- .-.' '-'.' '`-'- . - '`-'`  `''  `-.` '    .-.. . '`.
.. '`  `'..  .   .`'` -' . `'-- '.   `'' `.'   ``  -. -- _=\v77Y[Lxiiix]YYy2jI$$6h0m0bUm88MOOMMOOMMmmp0896hX5X4annt11[i)#<^- ` `  . ''`--`.'.. `  '  ` `.`.. ' '`'
  '..'-`.  .`` `-''.-'` ---`.  ```-   -   _<"(v}TYfje5wpORBggRBQQQWWWWWHBRQWRBHWBgB&YV&QRRWWgQQgHWQHRQBgBQQHHHgWHQgBQBQRBRWQNwy?`--'  '.'. .   .` . -. ` -' '`'-'--
   '  '   .-``'```. . - '..` - ..-`<\YJkwMNBgQBWHHgQBHRNMUSOgHHRWBQWBQgRRRQWHNWWHWQHWOx*i}[Ll{}TYYffyFI3khONgHBBHBWBHRQWBgQHBHBBQDe? '  '.'.'. `    `' ``.'.     ` .
 ' --- `-'. '` `  `....'.`--<L3bgQRHBWRgRHWHHg0asi/)xzZOHQQRHQQ@XIBHRHHQgWHu=|/i]Yfs23P0&QR&@@OOOOMMMOOM&DHgBRBWRBgHRBBHHgWWgBRgBHG{ -   `- '-. .. -'''' -'`````-'
`'' -.'````` . `.  . -. '?oOgHQRBHQQRWHBHNX1v(LsXbBgHRQQQgOZov<raHWBQBRRQWQgHBNO0hh5aeooCZDHggBgWWRBgQgBgRBBBWgRHRHQBBRQHgBgWQWWBWWHOv- ` ' ' `.  '`- - -`'   --'.
  -- .`- '   '.' - '-.\uMBQBHgBWBWRgHQBQQO&gHBQHDVNHO$CTY1TJ5G@WgRWBRHgBgHWWHRRBHQWQ&Mb00bmMOON@D@&&&gQBHHRgHRWWQHRgBBQWRgHBQWQRgWHgRg5~ ` ` '   `-'  -`'' ``''' `
..`.'. ``  -'``'`'-+yMBHBWWgWQQWRWRHgWWgQQHOOphkI`_!-''/Yeq@WQBBgQBQggWQRRWQBQQQ6T/*icc}L11TTT1[77ii/*<<"]JMggHWRRWRgQWRQRWHWHBRRRBgHggOr'- `.`'`'-' . -.' '  ` ` 
`- .- `'. - `   `v0WgQHHHQWgRRWRgWBQfiv{111tztztsyTTxi)vT39RQBBWBWBQWRQBQBQHBWK+ iMgBHWWRQRBWQBBWHBRBgQ@d2*-iSWRgWRgWHWBQBHRgRRgWHQWgRBHNi' '.  '`.-  ' - -`'`.--'
  '.' ---`-'`'.'THWHWBQQQHgWRRRWdj@}>$HQQHRHBRRHHQQg@HWBBRR&RQgRRRRHWBRHWRWWBBv']BQHQWRgBQRQgRRHWgQQHHQBBRBZr-}NBWWRHRgRBgHQBBBHgQWWHgBQHB]. ` '''..-`-''''.. '   
    . - --`' -'>WRHHHQQRQBgWBWO|+E(\OBHRQBWgRRWgBWgWdr+vqHQQBgRQWQBgQQHQRBQWgQ?rQgBHHBggRWRQWBHgHHQWQBRWRHHgBk/!>={C9HBRHHgWBHRWgBWRWHQgggH{   `'  ...-..' --  `..
- . `..-- -''  6QHHgHgBWWQRQBOjmQRgHgHgHBRHgWBHHWBQHQH&(>BBBHQgWBQRBggHHgRQQggDWQHgWROZfcr!' - `   `-- <)7ykMgggQBWHEfGBWWBBWHRggRgHgHQHgBHHN) `  .'''-' .- ..`. '
''- `'  - `'- *gRgHWgBRBRRWHgQgHgWRgHHBQHBHQBRRWQBHBWBW@?QBgQBHHHQHgRWgHRQHQBQBBW@5L<-...`' -< --'`''`` '-' .^iFMQBggRRRHRQBgBQWgRWgBgHWgWWgWNv   -   .'  '.  '.' 
---' `...- - _URgHHWHBWBgHWQBRHgQUCv=<>>+++>*;)\victhRRWOHWgBQHRHWRWRHggRHRRWgQZi`.`'_vt35GDW@`..v:--' -'''`'  '`<sOHBggBQHQWWggHQWHgQWHBQgHBQHSi  `'. `'' .--` - 
.'.  '--  .+1OHBHgHBWRRgRQW&WQOT+'' `,<;(iLT(`.''  '-~[GgWRBRHWggQgRQQgBBQgH@s_-.`<fPQQRHHWgRM.`':` `  `'- reG%zr -!UHRmpONHHRQRHRBgBgQDmPkX#3aJol'.` -   .'- `   
..-- ``-<fqRHO5WBWWHgW@1GgA}NBW4>'-   __++>"!-i/`.--  ..*VMp4XIZDWggHBggWgBO>. -<GHWHB&qeYvr:  ` '  ''-`'`.'*cJT<`"RB@y~ "{IOBQWHgBHgQBR@D&MMAVT^-"* '  ' `  '`.- 
-.`` >aRRQX/<pRBHRBBggMgHQQWQBHRmXVa4joz1}i(+~.` '  '` `-'``'  "MQHRQWBQHg&* -..SZJi+-.' .=LjhO@QHbgWQ@MPaoTv;_`-'-.0B6{N&QRQWBWBRQWQWHggHQRBWWBHWa=7Sx:`'--'  . 
`'`-'vNRDs=\o&QgQQBHBgggBRWRQRWWgHHgBHBRHQBRBRHDp94f]*~' '`.`=15DRHQHWHBHHgR&f+` .'   ^\sE@BWRHRQBO1OBQWRQggBQRQDOGEAMHgBgRHRWQBHgBHWQgBHBRQRHHgWWWHQe(ZOl-  .- .-
.''-xRWXNWHUv}RgBBRgggHgHgq@WggQHgWWQRRRgQHRQWgBRHgQRHWY`-`x&QHBWBBBWRHWRHWWHHgKaYvTe8QBgQgWQHBWRHBHQggQWgQQHQgRHRQRWBRQBQgBBRgWgRQHHgQWWWgRgBRWHQWRgRBkjD%r--' '.
. ..XHitHQR">&RWWggWQRQBQgNvYMQQggHHgRWgQQBBWgBBWRRBBggv.-'tQRHgWRWQRBHRBBggQQBQRWHRRRRRQQWBWWHRHggRHWWgHHQgBBHRgWWWRggBRRRBBQBHggWBWHRRQBHgBHWWQBQRQWQHRNgHy`'   
'  'pniWQQP'egBBgggHRgRWggBBz:YDRRRHRQBBBgRHWHWHWgQQgRW>. `CQggWBRHHHgWHRHWWggHQBWHHQQNhMgWHgQWHRHQRWBBWWWQWQRWggWgQRBWRRgQQRHBBQQBRBHBRRWHWRWgHgWRBWHHQgRWWHP+.``
.'' pi%QRQc;RWBgWHRWWQgRHBQHROTiivTF5MBgHWRRQgRQRRRRQ&s '``pgQgBHBgBQgQQQRWBHRWQBQQBHQQM1;>(v1tF4$5EE8qUEE65ZkUHHWHQHgWgBggHWQWBWgHgRQBRHgHRgBQWQgRHHBHHHQHBgQM:.'
 .''PvoHg@_aQgBQQHgBWBBQHgHHgBBBHQOE3Ycx[owRRggHQBOov~-',cPgWQBQRHRQgRgWQBBQgRPXXkX9bHgBBR&MKKP9$54IFCJu2IZ9MRBgWRgBBQgBRRQQQHBHgHQHBgWWBBWWggRRHHBRHHHQRBHQRBQv'.
- `'$y"WRX hRBWgQgBWRWBWQBRWQHBBHHWQHgRWDUOgBgWGY+  --vZDBHHBRWBHHRgWRWHgRBggT'   `. :}@ggBRQBRBQWBgWWBHRRHWQHHRBWQWQBRQWQRHWBHRRRRRQHgWRQBgWHHQQBWBRBgQgHQQWRWT.-
'.``oh`3HOnv\o&QRWgWWRBgRWHgHRggHQWWHggWBQRHDur  '- T&RQQWWRWHHHRWBWQWHHgBRRgW6oL\<^`.'rDggBQggBHHgWQQHHRQBQBRWggBHgHBWHgHBQRWQRRRQgRBHQWggHBQQHWQgHHBBQRBBHRgR= .
   ` .!X<lOHWHQWgWBRHWQRQgBRWRBRWD#"e0Xs|` '. ,(?'-.>9WgHRQgRQRWBHB8Y?!`-. `'`'`_&RRn  .'MWBHWQR#ZRBHRWgWBBHHQgQHBBWQWRHQRWQBHgQHHRWBBHWgWRgRBHQHWRWHRQBX+WRBq:' `
`.' -'` z&BB@Xsl5QgQRBQQHgBWRRRZL_+iyj) '- >TEWBRE).'.[MBWRRHRgHRRBWOkeVXAm&D/`-`3gp)  ' CRQHgQBC7RQgQWQgQggBWQHgBWQHWQggQWBRHWWHRRHBWHRWHBQQHRHHHQWHQHz 4HW$^-'''
.-''-. `<@RQBRgObHgWRWRHQgRROT;1h@W&F~' `vwQRgRgBBQ%v'  (uhw#x+tBQHWQWRQBQWQB@/`'^~'.. . [RQRBQgZ)RWggRHRBHMWgQBgBQQQBWQRRRQHRRgWgHRQWRQRBQWBWBQHgHHH%">$RMv-.-.'.
`    `..-)DgRBQRQHWBBQWHRROY|wgWRQ3>. ^1OgRRQBBWgBgQW8T<.' .->)1RBBgHWQBgHWQWRRYv[[1zC). |QWBBWWq;RQHHQHgW&IHHWRRQQWQQgWRRBQHWWWBRQHWHRBWgRWHWRBm3%@PudQOf:''--  -
  ` ''- ' iQQHgRWWgQgBRWM1|kRBQBZ+  '1DHRgggRBBQQBQWWWQRMbKOQQBgBBWgBQWBRBWQgHRWWBRgBWY  \BBgQBQD:QgRQgWgQSuQHRHgRHWBRQWBQBgWRWHWRQWWQQBBHWQWgW90@RRHD3\-  -'' .``
.'`-. .    eQBBHHHHgHHWy*ZWQQQM) '.iOQHHQBgHHQWQHRRRWRWHRRWHHQgQHgBBHWWWBWBBRggHWWRBgW[-'"QRRQRWQ.HWRRQRWWfsWBgQBRQBWgHHQQBBgHgQHWgRWBQBgWRWQBHWQRQO}~`-'- `--`. .
.- '-`--.`'=RRHgQQRBgm?JBHgWQn! `>EggWggWQRRWgWQHBBHRHgQRRHHRRRBBBggHHHgBHgBWQWWHBQBRR(  =BQWQBQg~NRQBRBBBifWWRBHRHgQWgWWRQgQggRWBgHHBRHHBQQQHBgWgZ_- -.``.- `` . 
.```' .`''  WHQWRRRR5fDBRBBE;-.'YDWBHHHHQRBWQRgQQWWBRWgHBQRHWQgBgHBHQWQgWHBgHBQQQBRRHQ~ `(BBRWWHB!MHWQBWQQ:JBgQBRgggBgBHRHWQggQQRRRRHWWWQRRgRgQBD]-.-`'`- `  '''  
-` ...  - --RBBHBWBQDHRQBOi-`')dQQQRBWWgRHWBHBWBRBQWWRgBgggBBWRHWBWWQHRgWgRHRRBWBRWWBd'.`zWQRHBHg>pBgHHQHO 4RQQWWggHWRBQWgWHWWWgHRgBHHHHgHQWQWWOr'-'''''   '-'    
.' -'...  '.WWQgWHBBgQB&T'  >$WgWHRHQWHggQWQRRgQWHQggQBQgQgWQRggQgWRQgRRgRQRHRHRBHggRy-  qWRWHggQ+qBQHBBgX-bHBHRgBBgRQWBgQHRRWBgBHRWRWggRgHgQH8< .. - .-  ` -`- ``
'-.-` ` `- ,gHBWgRWRRWC!-`+aHQRRWHggHHQHQHQHQQBBWRQBWQWgRgRBQgHHBWHQWHQHgWHgWWBRgBHQQ+''*HBgWBgQH_ERgBBRRT`&RRRHHHRQQQQHBggBgRHgWWQWQBBWBHHWgb_. ` - ` `''- .` -` 
 ` ..` ` '-.,HRQWQWgWK; `:yDQRQWBQHHBBWHRHWQBRHgBWBQWHQWRBgHQgQWQQHBBgRBHgBQgRRgWgQRW%`'`aBWQRRgWg~%RRgWWW|*WWHQRBgBggWBQRgHBHRHBHBQRRWQRHggB8_ `'` '`   '`.`..' `-
.   .  - ``+HHWBgHBe~'-l&gWgHWgHHQWRHWHBHRHQWWgWgBQRQBQgRHWHHWBRRRWWHHBRHBHgBBRQQBHRi  +WHgQWBWgg!SHBHgQW>zQHRgggQHQRBWHQQRWRWHRRgWHQgQgHQgS^`-    '`` `  -`' - '-
 `'''. ' ' "QBWHgR&~ *PWgBBQgWBBgQQHHQQWBWQWWHRBgHWWWQQQBgQBQWQgWRgHWggWQBRgQBHBBHWO`-.nWBHRHWHQg`0RgRgRD bQHRRWQWQHRRHBBWBRggBHBWgBHgQQgg2'   - -..'`.   - ``.-- 
  .-'  `  ';HHgBHQRDa@gRWHBRHHHBgggQRBBHgBHQWRRgHWBRQBRRWBHQQHgRQRgBHBHWgBBHRgWQQgWT '^DQHQRWRRW@ UWWBgHmrHgQQgQQgWBHQWBRRRBWWHRWQQQQHWBA=.'`.`''' ` .  .'  ``.`''
`'.`'-  .  <HgHRWgHHWgHWRRQQRQHQHWQgQQgRQHHHRHBgBWRWHRBQBRHHWgQRQWRHWHRRHHgRQWBRgHN~  1WRRRgHBBBO`MRgHBQSIBBWHHHHRHWRHQBHgRgWQggRWgRggEi -'``-`` ----`-' `'-.-.---
``'  `.  ' ,RHgHBRBRBRBBWQWHgRWQWRWHgWRWHgWHgWRQQBWRWgQRQWgBRHggWBRHHWHRBQBRWHHWRHj  .mBgWWBHBQHK-DQQHWBOgQQRRWHBWWBBWWQRRWHgRgRHgB&I* .- - '. ' .'   `- .. -.-  .
  -.  `' `-`QBHgWOItOgBBRHO$jyYciv|r<<+!:<+"*inORQQWgHQHgBggBgBWWQWBWWBRQBgWBBWWgQr -vBQgBHgWQRQf=QRQWggHHRQQBBRgWQQWggWgHRWWBBHQE7_- . '.`  '`--  '-`   ---' ' ' 
'' -``.`-' =WRRR[_f@gWBMt= ` .'`:>r"))/?==<-`.. ?XHHggRRRgQgQHgWBRRHgQWWgQBWQWHBW6` .ORWHWRgQWH9>MRHWQgQWBBBRBWQgHHWgHRWBQWgRHSY+'-.`.' .``--. .`'' .` ..'`   ' '-
.`.`  `` - ugQg3^mHHWS\' .<[IdNHWRgRRBWRBRRHOa/  .+TSDRRWBRWQgQBWgBBWggBRQWHHBHQD>  ngHBWHgHHQ6+bBgQQHQWBQHBgBgBWQgggBWWBgQPT< ```-`' ``  ```'-'`   -``.` -'`   `'
..`' .'' -^&gHBT"Te9Di:?CmHHQRRQRBRWaVI#45h&gHQpY_ -.-\fwWQBHQRgQQWBQHRQQWRHRgQN='`iRRRQgHBWWN|8WQWHRgRHHRgQRHWWQHBHgBgg91+'  - .``  `-  `'-'`  . .' ` -- ' `` '``
 .`  '``  tBQBHWBmY,)MgQHHQgRQgHgggH<-'``  .;eWRWRhfi+ ' :lEWBRQgQHHHgRRHgHWRQQi``<DHWgHBHHBQMMWBQBBQHQBBBHgQRgBWQHQRmt+'  .'.`'` ` .-'.-'   -`.` `'-`.  ``   `.-'  
'`-`-``.  OBRRQBQRB&vFmOWWWWHgWHgWWHSX#jytv -'<FWgQQQgMei'``+oNBgWBBBBHHBRHHggY`.'qBWRgHgQWRQgQQRQBRBQBBWQQWgWRWO5tv! -.  ``''` ' .'` -. -- `  ` '. - .-- '`.. -'` 
`' ' - -'+QBRgQHHQBWDZX$50&QHQHgggRQWRHHgHgO}`.`"8gHgQRggMz:` _zQQWQHWgHRgRgBU--`JgRHRBHgWgWHRRQWgQBBRQgWHM52[|, -  .-` '  '' '-`-- -' .-  '-  -`'-   `-`' - `  '' 
    ' '` "ggQBHWRWQggBRBBRWHgRRRRWBgBQgQWWBWgM7.`_8BBRWHWgHDf-`'sgWHHQgWQQRQgC``vHBHBggBQgBBgWWQWWgHq41v" -.`  ..'   .'`-  `.  '  .` .' '- ' ''`--' `` '```...-  `
 '.. -.--^gHgBHHQWQHggBBWWRBgBRBQHBRQRBBgRHQHHROuI@gBWgRQQQHQ7. ^DBggHgHQWgBg8nJOHQBQQWBgggBBRQBmui^ . -.- .  .`- '`''- -.`- .   '---`''`. `` ` - ` ' ' ` `..`  -.
'-``-``  '3WHWWBHBQWWBQQRRRHWQHgQgRHWHHHgHRQHRWHRRgHQQRBQHHRRN:`'VQHp+i@HgRBWHQBggWRgWQQgHRHbJc+.    `   ..   .'   .  - .'- . `.` ...''`'-. . '-`. .'  .-`. `  . -
 ` - '.-  :bggBQWRHgWWRHBWQWWHWHRRRWgQgHQBWRRQRgHRWWWggRWgRgWW4]TkRq~THQWRHHRRQWRBWWQgHHpJ?~  `` '' `.-- '`'.. -. --'.'..   `.  ``--. -'`  -  -  ` ' -. ''..-``.  
- `  `-- .`:hHHQRQRBQRHRQWgRQgHWWRRQBBHQBRQQgRHBQRgHQWWWBRHHWHgQRWa:oWgWQHgRQHRHQRQW0oi^' `    ' '.-  -    ' -'' -   `` ''  .''`-  ' `-     - `-`--'---'- -. '.'  
''  . . '`'`.T@RHBWBHgHWgHHgWHRgWHQWRRQgQggHRgRBWQgRQBWHH6LTJZ9pIr\0RRQQQBBMd6$et["~ .` -` .-''--. '--- '`- .-`  .`.'-.` .` ''-`-.  `-.-  ..'-`'..`--  '`.-```  ..
.- '  ..-     ~o&QBRHQHBWWgQRBQggggQgQBWBgWQgRWHRBWWWWHRWH@P2fsJXMQHO9FT(>` '...  .'.`-. ``- `-'. -. ' .` `'-`.` '-`-- -  `' -..`' . .  '-  ```.' `   ``'`-'   ` .
' .' '`. '.-..-`'\zh@gQWHBWHRBQWgRWWgBRHQgBgHBBRHQHHQBHHBD0E3CtTlvr~  --'  .   -`-`'  .`  . `- '.`'`    `-.  -`'.- -ну ладно...- - . `.-`''`-` .` -''.' ` ...` '`'
'` - .. .--. ` `.`-..+vTIK@gHWBgWBWHHRRBQQWRQHWQBHOP4yv;~. `   '.'`   --`  `-- .-  `   --''   `'`- `- ``-   ' -.'      .'-.    -  '' ' -```-`    . '.`    --'-.`.'
'. -`-'  '`. `--  -'``-``''+?c1tnF2Jnntzzsz1T7v"> ``.' ' - ' .-- -- .-  `  `.' ` `   ` `.-' -  `   `. .-  . -` ` --.`..`.` '`. -- ` `  `.'--  .  ' -'.`'  . ``-- `)");
            return 0; //Досюдава
        }
        }
    }
}//
