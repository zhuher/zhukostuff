#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <map>
#include <unordered_map>
#include <vector>
#define pi acos(-1)
#define CURSOR_HOME printf_s("\x1B[H") //Для передвижения курсора отсюдава
#define GOTO_LINE_CHAR(line, charr) printf_s("\x1B[%d;%dH", line, charr)
#define GOTO_CHAR(line) printf_s("\x1B[%dG", line)
#define UP_LINES(i) printf_s("\x1B[%dA", i)
#define DOWN_LINES(i) printf_s("\x1B[%dB", i)
#define RIGHT_CHARS(i) printf_s("\x1B[%dC", i)
#define LEFT_CHARS(i) printf_s("\x1B[%dD", i) //Досюдава
#define ERASE_CURRENT_LINE printf_s("\x1B[2K") //Стирает настоящую строчку
#define RESET_TEXT_FORMATTING printf_s("\x1B[0m")
using namespace std;
wstring amogus(L""); long long inpn(0);
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼СТРОКИ ДЛЯ ФОРМАТИРОВАНИЯ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
const string reset("\x1b[0m");
const string black("\x1b[0;30m"), red("\x1b[0;31m"), green("\x1b[0;32m"), yellow("\x1b[0;33m"), blue("\x1b[0;34m"), magenta("\x1b[0;35m"), cyan("\x1b[0;36m"), white("\x1b[0;37m");
const string bblack("\x1b[0;90m"), bred("\x1b[0;91m"), bgreen("\x1b[0;92m"), byellow("\x1b[0;93m"), bblue("\x1b[0;94m"), bmagenta("\x1b[0;95m"), bcyan("\x1b[0;96m"), bwhite("\x1b[0;97m");
const string blackbg("\x1b[0;40m"), redbg("\x1b[0;41m"), greenbg("\x1b[0;42m"), yellowbg("\x1b[0;43m"), bluebg("\x1b[0;44m"), magentabg("\x1b[0;45m"), cyanbg("\x1b[0;46m"), whitebg("\x1b[0;47m");
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼СТРОКИ ДЛЯ КОРОБОЧЕК ИНТЕРФЕЙСА▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
const string horw20(u8"════════════════════"), horw80(u8"════════════════════════════════════════════════════════════════════════════════"), horw6(u8"══════"), horw5(u8"═════"), horw(u8"═"), vertw(u8"║"), toprc(u8"╗"), toplc(u8"╔"), botrc(u8"╝"), botlc(u8"╚"), topmw(u8"╦"), botmw(u8"╩"), leftmw(u8"╠"), rightmw(u8"╣"), midw(u8"╬");
//Медленный складыватель двух чисел как строк(fails to acheive precision on large numbers, its only goal)▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
string addos(string a, string b, int precision)
{
    int adot(a.size() - 1), bdot(b.size() - 1), adotsym(0), bdotsym(0), awhole(0), bwhole(0);
    if (adot == -1 && bdot == -1)
    {
        return("0");
    }
    else if (adot == -1 && bdot != -1)
    {
        return(b);
    }
    else if (adot != -1 && bdot == -1)
    {
        return(a);
    }
    else
    {
        for (int i(0); i < a.size(); ++i)
        {
            if (a[i] == '.')
            {
                adot = i;
                continue;
            }
            if (adot != (a.size() - 1))
            {
                ++adotsym;
            }
            else
            {
                ++awhole;
            }
        }
        for (int i(0); i < b.size(); ++i)
        {
            if (b[i] == '.')
            {
                bdot = i;
                continue;
            }
            if (bdot != (b.size() - 1))
            {
                ++bdotsym;
            }
            else
            {
                ++bwhole;
            }
        }
        if (adotsym == 0)
        {
            a += ".";
        }
        if (bdotsym == 0)
        {
            b += ".";
        }
        for (int i(0); i < precision - adotsym; ++i)
        {
            a += "0";
        }
        for (int i(0); i < precision - bdotsym; ++i)
        {
            b += "0";
        }
        string result; int carry(0); int as(a.size() - 1), bs(b.size() - 1);
        while ((as >= 0) && (bs >= 0))
        {
            if (a[as] == '.')
            {
                --as;
                --bs;
                continue;
            }
            int x((a[as] - '0') + (b[bs] - '0') + carry);
            string boo(to_string(x % 10));
            result = boo + result;
            carry = x / 10;
            --as;
            --bs;
        }
        while (as >= 0)
        {
            int x((a[as] - '0') + carry);
            string boo(to_string(x % 10));
            result = boo + result;
            carry = x / 10;
            --as;
        }
        while (bs >= 0)
        {
            int x((b[bs] - '0') + carry);
            string boo(to_string(x % 10));
            result = boo + result;
            carry = x / 10;
            --bs;
        }
        while (carry)
        {
            string boo(to_string(carry % 10));
            result = boo + result;
            carry /= 10;
        }
        if (precision > 0)
        {
            result.insert(max(awhole, bwhole), ".");
        }
        return(result);
    }
}
string addos(void);
//Переводчик числа из 36-СС в 10-СС▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
int based(char cha_cha_cha)
{
    if (cha_cha_cha >= '0' && cha_cha_cha <= '9')
    {
        return((int)(cha_cha_cha - '0'));
    }
    else if (cha_cha_cha >= 'A' && cha_cha_cha <= 'Z')
    {
        return((int)(cha_cha_cha - 'A' + 10));
    }
    else if (cha_cha_cha >= 'a' && cha_cha_cha <= 'z')
    {
        return((int)(cha_cha_cha - 'a' + 10));
    }
    else
    {
        return(-1);
    }
}
int based(void);
//Переводчик арабского числа в 10-СС в его аналог в 36-СС▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
char unbased(int lel)
{
    if (lel >= 0 && lel <= 9)
    {
        return(48 + lel);
    }
    else
    {
        return(lel - 10 + 'A');
    }
}
char unbased(void);
//Переводчик из любой СС между 2 и 36 включительно▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
string basetobase(string num, int basefrom, int baseto)
{
    if (basefrom > 36 || basefrom < 2 || baseto > 36 || baseto < 2)
    {
        return("[сс вне диапазона]");
    }
    bool neg(false);
    if (num[0] == '-')
    {
        neg = true;
        num.erase(0, 1);
    }
    long double numberval(0), fracpart(0); int powa(num.size() - 1), doter(0), dostatochno(0); string result(""); long double intpart(0);
    for (int i(0); i < num.size(); ++i)
    {
        if (num[i] == '.')
        {
            ++doter;
            powa = i;
            if (doter > 1)
            {
                return("[недопустимый ввод]");
            }
        }
        else if ((based(num[i]) > (basefrom - 1)) || (based(num[i]) < 0))
        {
            return("[недопустимый ввод]");
        }
    }
    if (powa == (num.size() - 1))
    {
        for (int i(0); i < num.size(); ++i)
        {
            //stringstream a, b;
            //a << fixed << setprecision(0) << numberval;
            //b << fixed << setprecision(0) << (based(num[i]) * pow(basefrom, (powa - i)));
            //numberval = strtold(addos(a.str(), b.str(), 0).c_str(), NULL);
            numberval += (based(num[i]) * pow(basefrom, (powa - i)));
        }
    }
    else
    {
        for (int i(0); i < num.size(); ++i)
        {
            if (num[i] == '.')
            {
                continue;
            }
            if (i < powa)
            {
                numberval += (based(num[i]) * pow(basefrom, (powa - i - 1)));
            }
            else if (i > powa)
            {
                numberval += (based(num[i]) * pow(basefrom, (powa - i)));
            }
        }
    }
    switch (baseto)
    {
    case (10):
    {
        if (powa == (num.size() - 1))
        {
            return(to_string(numberval));
        }
        else
        {
            stringstream a, b;
            a << fixed << setprecision(53) << numberval;
            return(a.str());
        }
    }
    default:
    {
        fracpart = strtod(("0" + to_string(numberval).substr(to_string(numberval).find("."))).c_str(), NULL);
        if (floor(numberval) != numberval)
        {
            intpart = strtod(to_string(numberval).c_str(), NULL);
        }
        else
        {
            intpart = numberval;
        }
        while ((int)(intpart) != 0)
        {
            result = unbased(fmodl(intpart, baseto)) + result;
            intpart /= baseto;
        }
        if (fracpart != 0)
        {
            result += ".";
            while (fracpart != 0)
            {
                result += unbased((int)(fracpart * baseto));
                fracpart *= baseto;
                fracpart -= (int)(fracpart);
                ++dostatochno;
                if (dostatochno == 20)
                {
                    fracpart = 0;
                }
            }
        }
    }
    }
    if (result[0] == '.')
    {
        result = "0" + result;
    }
    if (neg)
    {
        result = "-" + result;
    }
    return(result);
}
string basetobase(void);
//Генератор случайных вещественных чисел
double nrg(double from, double to)
{
    random_device randev;
    mt19937 mt(randev());
    uniform_real_distribution<double> range(from, to);
    return range(mt);
}
double nrg(void);
//Генератор случайных целых чисел
long long inrg(long long from, long long to)
{
    random_device randev;
    mt19937 mt(randev());
    uniform_int_distribution<long long> range(from, to);
    return range(mt);
}
long long inrg(void);
//Микрокалькулятор ежемесячного платежа
long double fm(long double S, long double n, long double r)
{
    long double kek, resultado;
    kek = 1 + r;
    resultado = (S * r * pow(kek, n)) / (12 * (pow(kek, n) - 1));
    return resultado;
}//S / n / 12 = _, при которой p == 0
long double fm(void);
//Стиратель 5 и 0 из числа
string nofnoz(string num)
{
    string stres; int dot(0), min(0);
    stres.reserve(num.size());
    for (size_t c(0); c < num.size(); ++c) //ololo ++c
    {
        if (num[c] == '.')
        {
            ++dot;
            if (dot > 1)
            {
                return("[некорректный ввод]");
            }
            stres += num[c];
        }
        else if (num[c] == '-')
        {
            ++min;
            if (min > 1)
            {
                return("[некорректный ввод]");
            }
            stres += num[c];
        }
        else if (based(num[c]) > 0 && based(num[c]) != 5)
        {
            stres += num[c];
        }
    }
    if (stres[stres.size() - 1] == '.')
    {
        stres.pop_back();
    }
    if (stres[0] == '.')
    {
        stres = '0' + stres;
    }
    if (stres == "")
    {
        return("[пусто]");
    }
    return(stres);
}
string nofnoz(void);
//Генератор случайных строк
char* rstr(int len = 1, const char* alphabet = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")
{
    char* res = new char[len + 1]; res[len] = '\0';
    while (len) { res[len - 1] = alphabet[inrg(0, strlen(alphabet) - 1) % strlen(alphabet)]; --len; }
    return res;
}
//Говоритель знака числа
void getsign(double amogus_sus)
{
    if (amogus_sus > 0)
    {
        cout << "2. Число определённо положительное.\n";
    }
    else if (amogus_sus < 0)
    {
        cout << "2. Число определённо отрицательное.\n";
    }
    else
    {
        cout << "2. 0 или буква.\n";
    }
}
//Калькулятор треугольника
void triangle()
{
    double o(0), ba(0), ma(0);
    cout << "Ок, сча я выполню абсолютно невероятные вычисления(найду площадь треугольника по его сторонам). Без негатива(но можешь попробовать).\n";
    cout << "Введи длину первой стороны\n";
    while (true)
    {
        printf_s(">");
        getline(wcin, amogus);
        o = wcstoll(amogus.c_str(), NULL, 10);
        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
        amogus = o;
        if (o > 0) { break; }
    }
    cout << "Введи длину второй стороны\n";
    while (true)
    {
        printf_s(">");
        getline(wcin, amogus);
        ba = wcstoll(amogus.c_str(), NULL, 10);
        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
        amogus = ba;
        if (ba > 0) { break; }
    }
    cout << "Введи длину третьей стороны\n";
    while (true)
    {
        printf_s(">");
        getline(wcin, amogus);
        ma = wcstoll(amogus.c_str(), NULL, 10);
        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
        amogus = ma;
        if (ma > 0) { break; }
    }
    if (((o + ba) < ma) || ((o + ma) < ba) || ((ma + ba) < o))
    {
        cout << "\nОк бадди, хорошие стороны ввёл, а теперь перезапускай меня и вводи так, шоб каждые две стороны были в сумме больше третьей.\n";
    }
    else if (((o + ba) == ma) || ((o + ma) == ba) || ((ma + ba) == o))
    {
        cout << "\nПонимаешь, с твоим вводом выходит, что сумма двух отрезков(сторон) равна третьему отрезку(стороне).\n\nОни образуют получаеца две совпадающие одномерные линии без площади.\n";
    }
    else
    {
        stringstream q;
        q.precision(1488);
        q << (o + ba + ma);
        string t(q.str());
        string p(t.substr(t.find(".") + 1));
        int booba(p.size());
        cout << "\nПериметр p треугольника будет " << o + ba + ma << "\n\nЕго площадь находится по формуле sqrt(s * (s - a) * (s - b) * (s - c)), где s - половина p, а значит...\n" << "\nПлощадь равна sqrt(" << (o + ba + ma) / 2 << " * (" << (o + ba + ma) / 2 << " - (" << o << ")) * (" << (o + ba + ma) / 2 << " - (" << ba << ")) * (" << (o + ba + ma) / 2 << " - (" << ma << "))) =>\n" << "\n=> " << sqrt(((o + ba + ma) / 2) * (((o + ba + ma) / 2) - o) * (((o + ba + ma) / 2) - ba) * (((o + ba + ma) / 2) - ma)) << endl;
    }
}
//Калькулятор прямоугольника
void rectalgle()
{
    double o(0), bama(0);
    cout << "\nОк, сча я выполню абсолютно невероятные вычисления(найду площадь прямоугольника по его сторонам a и b). Без негатива тока давай(но можешь попробовать).\n";
    cout << "Введи длину a\n";
    while (true)
    {
        printf_s(">");
        getline(wcin, amogus);
        o = wcstoll(amogus.c_str(), NULL, 10);
        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
        amogus = o;
        if (o > 0) { break; }
    }
    cout << "Теперь введи длину b\n";
    while (true)
    {
        printf_s(">");
        getline(wcin, amogus);
        bama = wcstoll(amogus.c_str(), NULL, 10);
        ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
        amogus = bama;
        if (bama > 0) { break; }
    }
    stringstream q;
    q.precision(1488);
    q << (o * bama);
    string t(q.str());
    string p(t.substr(t.find(".") + 1));
    int booba(p.size());

    cout << "\nПериметр равен " << o + o + bama + bama << "\n\nПлощадь равна " << o * bama << endl;
}
//Калькулятор круга
void circle()
{
    double joemama(0);
    cout << "\nОк, вводи радиус круга, а я тебе скажу его периметр и площадь: ";
    while (true)
    {
        getline(wcin, amogus);
        joemama = wcstod(amogus.c_str(), NULL);
        if (joemama > 0)
        {
            break;
        }
    }
    cout << "\nПериметр круга равен " << 2 * pi * joemama << "\n\nПлощадь круга равна " << pi * joemama * joemama << endl;
}
//Переводчик из римских в арабские
void RoToAr()
{
    bool imposter(false), impostor(false), neg(false); long long bebra(0); int icounter(1), xcounter(1), ccounter(1), mcounter(1), bicounter(0), bxcounter(0), bccounter(0);
    cout << "\nОк, сча я тебе переведу число из римской СС в человеческую(десятичную).\n";
    while (!imposter)
    {
        neg = false;
        cout << "\nЧисло в R-СС: ";
        getline(wcin, amogus);
        if ((amogus == L"N") || (amogus == L"n") || (amogus == L"nulla") || (amogus == L"nihil") || (amogus == L"Nulla") || (amogus == L"Nihil") || (amogus == L"NULLA") || (amogus == L"NIHIL"))
        {
            amogus = L'N';
            break;
        }
        for (int sus(0); sus < amogus.size(); ++sus)
        {
            if (((amogus[sus]) != 'i') && ((amogus[sus]) != 'v') && ((amogus[sus]) != 'x') && ((amogus[sus]) != 'l') && ((amogus[sus]) != 'c') && ((amogus[sus]) != 'd') && ((amogus[sus]) != 'm') && ((amogus[sus]) != 'I') && ((amogus[sus]) != 'V') && ((amogus[sus]) != 'X') && ((amogus[sus]) != 'L') && ((amogus[sus]) != 'C') && ((amogus[sus]) != 'D') && ((amogus[sus]) != 'M') && ((amogus[sus]) != '-'))
            {
                cout << "\nНедопустимый ввод, вводи снова.\n";
                break;
            }
            if (sus == amogus.size() - 1)
            {
                imposter = true;
            }
            switch (amogus[sus])
            {
            case ('-'):
            {
                if (!neg)
                {
                    neg = true;
                    amogus[sus] = ' ';
                    break;
                }
                else
                {
                    neg = false;
                    amogus[sus] = ' ';
                    break;
                }
            }
            case ('M'):
            {
                //cout << 'M';
                break;
            }
            case ('D'):
            {
                if ((amogus[sus + 1] == 'D') || (amogus[sus + 1] == 'M'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('C'):
            {
                if (amogus[sus + 1] == 'C')
                {
                    ++bccounter;
                    if (bccounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((bccounter > 1) && (((amogus[sus + 1]) == 'D') || ((amogus[sus + 1]) == 'M')))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('L'):
            {
                if (((amogus[sus + 1]) == 'L') || ((amogus[sus + 1]) == 'C') || ((amogus[sus + 1]) == 'D') || ((amogus[sus + 1]) == 'M'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('X'):
            {
                if (amogus[sus + 1] == 'X')
                {
                    ++bxcounter;
                    if (bxcounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((bxcounter > 1) && (((amogus[sus + 1]) == 'L') || ((amogus[sus + 1]) == 'C')))
                {
                    impostor = true;
                    break;
                }
                if ((amogus[sus + 1] == 'D') || (amogus[sus + 1] == 'M'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('V'):
            {
                if ((amogus[sus + 1] == 'V') || (amogus[sus + 1] == 'X') || (amogus[sus + 1] == 'L') || (amogus[sus + 1] == 'C') || (amogus[sus + 1] == 'D') || (amogus[sus + 1] == 'M'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('I'):
            {
                if ((amogus[sus + 1]) == 'I')
                {
                    ++bicounter;
                    if (bicounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((bicounter > 1) && (((amogus[sus + 1]) == 'V') || ((amogus[sus + 1]) == 'X')))
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'I') && ((amogus[sus + 1]) != 'V') && ((amogus[sus + 1]) != 'X') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('m'):
            {
                if (amogus[sus + 1] == 'm')
                {
                    ++mcounter;
                    if (mcounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((mcounter > 1) && (((amogus[sus + 1]) == 'V') || ((amogus[sus + 1]) == 'X')))
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != 'v') && ((amogus[sus + 1]) != 'x') && ((amogus[sus + 1]) != 'l') && ((amogus[sus + 1]) != 'c') && ((amogus[sus + 1]) != 'm') && ((amogus[sus + 1]) != 'd') && ((amogus[sus + 1]) != 'V') && ((amogus[sus + 1]) != 'X') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('d'):
            {
                if (amogus[sus + 1] == 'd')
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != 'v') && ((amogus[sus + 1]) != 'x') && ((amogus[sus + 1]) != 'l') && ((amogus[sus + 1]) != 'c') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('c'):
            {
                if (amogus[sus + 1] == 'c')
                {
                    ++ccounter;
                    if (ccounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((ccounter > 1) && (((amogus[sus + 1]) == 'd') || ((amogus[sus + 1]) == 'm')))
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != 'v') && ((amogus[sus + 1]) != 'x') && ((amogus[sus + 1]) != 'l') && ((amogus[sus + 1]) != 'c') && ((amogus[sus + 1]) != 'd') && ((amogus[sus + 1]) != 'm') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('l'):
            {
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != 'v') && ((amogus[sus + 1]) != 'x') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('x'):
            {
                if (amogus[sus + 1] == 'x')
                {
                    ++xcounter;
                    if (xcounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((xcounter > 1) && (((amogus[sus + 1]) == 'l') || ((amogus[sus + 1]) == 'c')))
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != 'v') && ((amogus[sus + 1]) != 'x') && ((amogus[sus + 1]) != 'l') && ((amogus[sus + 1]) != 'c') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('v'):
            {
                if (amogus[sus + 1] == 'v')
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            case ('i'):
            {
                if ((amogus[sus + 1] == 'i'))
                {
                    ++icounter;
                    if (icounter > 3)
                    {
                        impostor = true;
                        break;
                    }
                }
                if ((icounter > 1) && (((amogus[sus + 1]) == 'v') || ((amogus[sus + 1]) == 'x')))
                {
                    impostor = true;
                    break;
                }
                if (((amogus[sus + 1]) != 'i') && ((amogus[sus + 1]) != 'v') && ((amogus[sus + 1]) != 'x') && ((amogus[sus + 1]) != '\0'))
                {
                    impostor = true;
                    break;
                }
                break;
            }
            }
            if (impostor)
            {
                icounter = 1;
                bicounter = 1;
                xcounter = 1;
                bxcounter = 1;
                ccounter = 1;
                bccounter = 1;
                mcounter = 1;
                impostor = false;
                cout << "\nНедопустимый ввод, вводи снова.\n";
                break;
            }
        }
    }
    int M(1000000), D(500000), C(100000), L(50000), X(10000), V(5000), m(1000), d(500), c(100), l(50), x(10), v(5);
    for (int sus(0); sus < amogus.size(); ++sus)
    {
        switch (amogus[sus])
        {
        case('N'):
        {
            break;
        }
        case ('M'):
        {
            bebra += M;
            break;
        }
        case ('D'):
        {
            bebra += D;
            break;
        }
        case ('C'):
        {
            if ((amogus[sus + 1] == 'D') || (amogus[sus + 1] == 'M'))
            {
                bebra -= C;
                break;
            }
            else
            {
                bebra += C;
                break;
            }
        }
        case ('L'):
        {
            bebra += L;
            break;
        }
        case ('X'):
        {
            if ((amogus[sus + 1] == 'L') || (amogus[sus + 1] == 'C'))
            {
                bebra -= X;
                break;
            }
            else
            {
                bebra += X;
                break;
            }
        }
        case ('V'):
        {
            bebra += V;
            break;
        }
        case ('I'):
        {
            bebra -= m;
            break;
        }
        case ('m'):
        {
            if ((amogus[sus + 1] == 'V') || (amogus[sus + 1] == 'X'))
            {
                bebra -= m;
                break;
            }
            else
            {
                bebra += m;
                break;
            }
        }
        case ('d'):
        {
            bebra += d;
            break;
        }
        case ('c'):
        {
            if ((amogus[sus + 1] == 'd') || (amogus[sus + 1] == 'm'))
            {
                bebra -= c;
                break;
            }
            else
            {
                bebra += c;
                break;
            }
        }
        case ('l'):
        {
            bebra += l;
            break;
        }
        case ('x'):
        {
            if ((amogus[sus + 1] == 'l') || (amogus[sus + 1] == 'c'))
            {
                bebra -= x;
                break;
            }
            else
            {
                bebra += x;
                break;
            }
        }
        case ('v'):
        {
            bebra += v;
            break;
        }
        case ('i'):
        {
            if ((amogus[sus + 1] == 'v') || (amogus[sus + 1] == 'x'))
            {
                bebra -= 1;
                break;
            }
            else
            {
                bebra += 1;
                break;
            }
        }
        }
    }
    if (neg)
    {
        neg = false;
        bebra *= -1;
    }
    cout << "\nЧисло в человеческой 10-СС: " << bebra << endl;
    bebra = 0;
    icounter = 1;
    bicounter = 1;
    xcounter = 1;
    bxcounter = 1;
    ccounter = 1;
    bccounter = 1;
    mcounter = 1;
    impostor = false;
    imposter = false;
}
//Переводчик из арабских в римские
void ArToRo()
{
    string resronum; long long amongus(0), nums[]{ 1000000, 900000, 500000, 400000, 100000, 90000, 50000, 40000, 10000, 9000, 5000, 4000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 }; bool neg(false), doconv(true); map <int, string> ronum{ {1000000, "M"}, {900000, "CM"}, {500000, "D"}, {400000, "CD"}, {100000, "C"}, {90000, "XC"}, {50000, "L"}, {40000, "XL"}, {10000, "X"}, {9000, "IX"}, {5000, "V"}, {4000, "IV"}, {1000, "m"}, {900, "cm"}, {500, "d"}, {400, "cd"}, {100, "c"}, {90, "xc"}, {50, "l"}, {40, "xl"}, {10, "x"}, {9, "ix"}, {5, "v"}, {4, "iv"}, {1, "i"} };
    cout << "\nОк, сча будем переводить число из десятичной в римскую.\n";
    doconv = true;
    while (true)
    {
        neg == false;
        amongus = 0;
        amogus = L"";
        cout << "\nЧисло в 10-СС: ";
        getline(wcin, amogus);
        amongus = wcstoll(amogus.c_str(), NULL, 10);
        if (amongus == 0)
        {
            if (!isdigit(amogus[0]))
            {
                cout << "\nЯ вижу ввод как " << string(amogus.begin(), amogus.end()) << ", а потому...\n";
                cout << "\nНекорректный ввод, вводи снова.\n";
            }
            else
            {
                cout << "\nЯ вижу ввод как " << amongus << ", а потому...\n";
                resronum = "N";
                doconv = false;
                break;
            }
        }
        else if (amongus < 0)
        {
            cout << "\nЯ вижу ввод как " << amongus << ", а потому...\n";
            amongus *= -1;
            neg = true;
            break;
        }
        else
        {
            cout << "\nЯ вижу ввод как " << amongus << ", а потому...\n";
            break;
        }
    }
    if (doconv)
    {
        resronum = "";
        for (int num : nums)
        {
            if (amongus >= num)
            {
                while (amongus >= num)
                {
                    resronum += ronum[num];
                    amongus -= num;
                }
            }
        }
        if (neg)
        {
            if (resronum != "")
            {
                resronum.insert(0, 1, '-');
            }
        }
    }
    if (resronum != "")
    {
        cout << "\nЧисло в R-CC: " << resronum << endl;
    }
    else
    {
        cout << "\nЧисло в R-CC: а его нет, ведь было введено число вне диапазона, а я с такими отказываюсь работать" << endl; //
    }
}
//Переводчик целых чисел из 16-СС в 2-СС
string inthextobin(string hexint)
{
    int minus(false);
    string result("");
    for (int sus(hexint.size() - 1); sus >= 0; --sus)
    {
        if (hexint[sus] == '-')
        {
            if (!minus)
            {
                minus = true;
                result = hexint[sus] + result;
            }
            else
            {
                return("[недопустимый ввод]");
            }
        }
        else if (based(hexint[sus]) >= 0 && based(hexint[sus]) <= 15)
        {
            string binum(""); int b(based(hexint[sus]));
            for (int kek(0); kek < 4; ++kek)
            {
                binum = to_string(b % 2) + binum;
                b /= 2;
            }
            result = binum + result;
        }
        else
        {
            return("[недопустимый ввод]");
        }
    }
    if (minus)
    {
        result = '-' + result;
    }
    return(result);
}
string inthextobin(void);
//в другом файле ололололо▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void karnaugh()
{
}
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼тесто▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void kektask()
{
}
//monkey nuts
void nuts()
{
    cout << "Ok, сейчас мы заставим обезьяну бегать по лестнице и разбивать орехи.\n";
    while (true)
    {
        long long amount(0), hardness(0), stair(0), stepsize(2048), prevstair(0);
        cout << "\nВведи кол-во орехов[n>0].";
        while (true)
        {
            cout << "> ";
            getline(wcin, amogus);
            amount = wcstoll(amogus.c_str(), NULL, 10);
            if (amount)
            {
                break;
            }
        }
        cout << "\nТеперь введи прочность[n>=0].";
        bool checking(true);
        while (checking)
        {
            cout << "> ";
            getline(wcin, amogus);
            bool minus(false), dot(false);
            for (int sus(0); sus < amogus.size(); ++sus)
            {
                if (amogus[sus] == '-')
                {
                    if (!minus)
                    {
                        minus = true;
                        amogus[sus] = ' ';
                    }
                }
                if (sus = amogus.size() - 1)
                {
                    hardness = wcstoll(amogus.c_str(), NULL, 10);
                    checking = false;
                    break;
                }
            }
        }
    }
}
//bydlo
void bydlo()
{
    while (true)
    {
        string toguess(""), guess; unsigned chlen(0); /*chislo length*/ vector<unsigned> used; bool haram;
        cout << "Ок, какой длины слово угадывать будешь? [1 - 10]\n";
        while (true)
        {
            cout << "> ";
            getline(wcin, amogus);
            chlen = wcstol(amogus.c_str(), NULL, 10);
            if (chlen >= 1 && chlen <= 10)
            {
                break;
            }
        }
        for (int l(0); l < chlen; ++l)
        {
            if (!l)
            {
                unsigned n(inrg(1, 9));
                toguess += to_string(n);
                used.push_back(n);
            }
            else
            {
                while (true)
                {
                    haram = false;
                    unsigned n(inrg(0, 9));
                    for (unsigned k : used)
                    {
                        if (n == k)
                        {
                            haram = true;
                            break;
                        }
                    }
                    if (!haram)
                    {
                        toguess += to_string(n);
                        used.push_back(n);
                        break;
                    }
                }
            }
        }
        cout << toguess << endl;
        cout << "Ok, тогды начинай угадывать, ведь я уже загадал число.\n";
        while (true)
        {
            cout << "> ";
            getline(wcin, amogus);
            string amagos(string(amogus.begin(), amogus.end()));
            if (amagos == toguess)
            {
                cout << "\nУгадали!";
                break;
            }
            else
            {
                guess = "";
                for (int kek(0); kek < min(amagos.size(), toguess.size()); ++kek)
                {
                    if (amagos[kek] == toguess[kek])
                    {
                        guess += "+";
                    }
                }
                for (int kek(0); kek < toguess.size(); ++kek)
                {
                    for (int lol(0); lol < amagos.size(); ++lol)
                    {
                        if (lol != kek && amagos[lol] == toguess[kek])
                        {
                            guess += "-";
                        }
                    }
                }
                cout << guess << endl;
            }
        }
        cout << "\n\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 1 НОМЕР 1▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H1N1()
{
    system("CLS");
    cout << "Герман" << endl;
}
//ДЗ 1 НОМЕР 2▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H1N2()
{
    system("CLS");
    //deistviya s dvumya chislami
    double a(0), b(0);
    cout << "1. Опааа, сча мы тебе выполним базовые арифметические действия с числами a и b\n\n2. Введи a: ";
    getline(wcin, amogus);
    a = wcstod(amogus.c_str(), NULL);
    cout << "\n3. Введи b: ";
    getline(wcin, amogus);
    b = wcstod(amogus.c_str(), NULL);
    if (a == 0 || b == 0)
    {
        cout << "\n4. a = " << a << ", b = " << b << endl;
        cout << "\n5. Сумма = " << a + b << endl;
        cout << "\n6. Разность a - b = " << a - b << endl;
        cout << "\n7. Разность b - a = " << b - a << endl;
        cout << "\n8. Произведение = " << a * b << endl;
        cout << "\n9. A делить на 0 нельзя" << endl;
    }
    else
    {
        cout << "\n4. a = " << a << ", b = " << b << endl;
        cout << "\n5. Сумма = " << a + b << endl;
        cout << "\n6. Разность a - b = " << a - b << endl;
        cout << "\n7. Разность b - a = " << b - a << endl;
        cout << "\n8. Произведение = " << a * b << endl;
        cout << "\n9. Частное a / b = " << a / b << endl;
        cout << "\n10. Частное b / a = " << b / a << endl;
    }
}
//ДЗ 1 НОМЕР 3▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H1N3()
{
    system("CLS");
    //linear equation solver
    double b, c;
    cout << "1. Опааа, сча мы тебе прорешаем уравнение формата xb + c = 0\n\n2. Введи b: ";
    getline(wcin, amogus);
    b = wcstod(amogus.c_str(), NULL);
    cout << "\n3. Введи c: ";
    getline(wcin, amogus);
    c = wcstod(amogus.c_str(), NULL);
    if (c == 0)
    {
        if (b == 0)
        {
            cout << "\n4. Ты мне ввёл и b и с нулевые, а потому x тут может быть любой." << endl;
        }
        else
        {
            cout << "\n4. Ну т.к. c = 0, a b =/= 0, то x = 0." << endl;
        }
    }
    else if (b == 0)
    {
        if (c == 0)
        {
            cout << "\n4. Ты мне ввёл и b и с нулевые, а потому x тут может быть любой." << endl;
        }
        else
        {
            cout << "\n4. Чел ты... с твоими данными выходит c + bx = " << c << " + 0 = 0..." << endl;
        }
    }
    else
    {
        cout << "x = -c / b = " << -c / b << endl;
    }
}
//ДЗ 1 НОМЕР 4▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H1N4()
{
    system("CLS");
    //quadratic equation solver
    double a, b, c, x1, discriminant, realPart, imaginaryPart;
    cout << "1. Сча я тебе решу уравнение формата ax^2 + bx + c = 0 (квадратичное)." << endl;
    cout << "\n2. Введи a: ";
    getline(wcin, amogus);
    a = wcstod(amogus.c_str(), NULL);
    cout << "\n3. Введи b: ";
    getline(wcin, amogus);
    b = wcstod(amogus.c_str(), NULL);
    cout << "\n4. Введи c: ";
    getline(wcin, amogus);
    c = wcstod(amogus.c_str(), NULL);
    cout << "\n5. a = " << a << ", b = " << b << ", c = " << c << ", т.е. мы имеем: (" << a << ")x^2 + (" << b << ")x + (" << c << ") = 0, а значит..." << endl;
    if (a == 0 && b != 0 && c != 0)
    {
        cout << "\n6. Тут тупа линейное уравнение(формат bx + c = 0), т.е. x = -c / b = " << -c << " / " << b << " = " << -c / b << endl;
    }
    else if ((a > 0 && b == 0 && c < 0) || (a < 0 && b == 0 && c > 0))
    {
        cout << "\n7. Получаеца (" << a << ")x^2 + (" << c << ") = 0, а значит..." << endl;
        cout << "\n8. x1 = корень из (-c / a) = корень из (" << -c << " / " << a << ") = " << sqrt(-c / a) << endl;
        cout << "\n9. x2 = отрицательный корень из (-c / a) = отрицательный корень из (" << -c << " / " << a << ") = " << -sqrt(-c / a) << endl;
    }
    else if ((a > 0 && b == 0 && c > 0) || (a < 0 && b == 0 && c < 0))
    {
        cout << "\n7. Получаеца (" << a << ")x^2 + (" << c << ") = 0, а значит..." << endl;
        cout << "\n8. x мы находим по формуле +/-корень из (-c / a), т.е. тут будут корни отрицательных чисел, а значит комплексные корни..." << endl;
        cout << "\n9. x1 = корень из (-c / a) = корень из (" << c << " / " << a << ") * i = " << sqrt(c / a) << "i." << endl;
        cout << "\n10. x2 = отрицательный корень из (-c / a) = отрицательный корень из (" << c << " / " << a << ") * i = " << -sqrt(c / a) << "i." << endl;
    }
    else if (a != 0 && b != 0 && c == 0)
    {
        cout << "\n7. Ну получаеца (" << a << ")x^2 + (" << b << ")x = 0, преобразуем в x * (" << a << "x + " << b << "), тут у нас произведение равно 0, а значит один из множителей равен 0, а значит..." << endl;
        cout << "\n8. x1 = (-b / a) = (" << -b << " / " << a << ") = " << -b / a << endl;
        cout << "\n9. x2 = 0." << endl;
    }
    else if (a == 0 && b == 0 && c != 0)
    {
        cout << "\n7. Мы имеем 0 + (" << c << ") = 0. Этож шиза, решения нет тупа." << endl;
    }
    else if ((a == 0 && b != 0 && c == 0) || (a != 0 && b == 0 && c == 0))
    {
        cout << "\n7. Тут получаеца x * " << b << " = 0, следовательно один из множетелей равен 0, а значит х = 0." << endl;
    }
    else if (a == 0 && b == 0 && c == 0)
    {
        cout << "\n7. Ну тут мы получаем выражение 0x^2 + 0x + 0 = 0, которое будет истинно для всех значений x." << endl;
    }
    else
    {
        discriminant = b * b - 4 * a * c;
        if (discriminant > 0)
        {
            cout << "\n7. Корни реальны и разные." << endl;
            cout << "\n8. x1 = " << ((-b + sqrt(discriminant)) / (2 * a)) << endl;
            cout << "\n9. x2 = " << ((-b - sqrt(discriminant)) / (2 * a)) << endl;
        }
        else if (discriminant == 0)
        {
            cout << "\n7. Корни равны и реальны." << endl;
            x1 = -b / 2 * a;
            cout << "\n8. x1 = x2 = " << x1 << endl;
        }
        else
        {
            realPart = -b / (2 * a);
            imaginaryPart = sqrt(-discriminant) / (2 * a);
            cout << "\n7. Корни - разные комплексные числа." << endl;
            cout << "\n8. x1 = " << realPart << " + " << imaginaryPart << "i" << endl;
            cout << "\n9. x2 = " << realPart << " - " << imaginaryPart << "i" << endl;
        }
    }
}
//ДЗ 1 НОМЕР 5▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H1N5()
{
    system("CLS");
    //svetlo detector
    wstring timeofday, shtori, lampstate;
    const wstring YES = L"yes";
    const wstring NO = L"no";
    cout << "1. Сча мы определим, светло у тя в комнате или нет. \n\n2. На следующие вопросы отвечай только 'yes'(что значит 'да') или 'no'(что значит 'нет')\n\n3. На улице день?" << endl;
    getline(wcin, timeofday);
    wcout << timeofday << endl;
    cout << "\n4. Шторы раздвинуты?" << endl;
    getline(wcin, shtori);
    cout << "\n5. Лампа включена?" << endl;
    getline(wcin, lampstate);
    if ((timeofday == YES || shtori == YES) || lampstate == YES)
    {
        cout << "\n6. Светло!" << endl;
    }
    else if (timeofday == NO && lampstate == NO)
    {
        cout << "\n6. Тьма..." << endl;
    }
    else
    {
        cout << "\n6. Че ты мне написал то емае, яж сказал тебе формат ответов, а ты мне бред на минимум один вопрос написал. Потролить тебе охота? Ну так иди тролить кого-то другого." << endl;
    }
}
//ДЗ 2 НОМЕР 1▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H2N1()
{
    system("CLS");
    double br, sr, h, l, di, s, r1, r2;
    cout << "1. Введи первый радиус усеченного конуса: ";
    getline(wcin, amogus);
    r1 = wcstod(amogus.c_str(), NULL);
    cout << "\n2. Введи второй радиус усеченного конуса: ";
    getline(wcin, amogus);
    r2 = wcstod(amogus.c_str(), NULL);
    cout << "\n3. Введи высоту усеченного конуса: ";
    getline(wcin, amogus);
    h = wcstod(amogus.c_str(), NULL);
    if (r1 > r2 && r1 > 0 && r2 > 0 && h > 0)
    {
        br = r1;
        sr = r2;
        di = br - sr;
        l = sqrt(di * di + h * h);
        cout << "\n4. Объём примерно равен " << pi * h * (sr * sr + br * br + sr * br) / 3 << "\n\n5. Площадь полной поверхности примерно равна " << pi * (sr + br) * l + pi * sr * sr + pi * br * br << endl;
    }
    if (r1 < r2 && r1 > 0 && r2 > 0 && h > 0)
    {
        br = r2;
        sr = r1;
        di = br - sr;
        l = sqrt(di * di + h * h);
        cout << "\n4. Объём примерно равен " << pi * h * (sr * sr + br * br + sr * br) / 3 << "\n\n5. Площадь полной поверхности примерно равна " << pi * (sr + br) * l + pi * sr * sr + pi * br * br << endl;
    }
    if ((r1 == 0 && r2 > 0) || (r1 > 0 && r2 == 0) && h > 0)
    {
        s = r1 + r2;
        l = sqrt(s * s + h * h);
        cout << "\n4. Ну ты мне обычный конус дал получаеца. Задание не в этом заключается, конечно, но, так и быть, решу и это. \n\n5. Полная поверхность примерно равна " << (pi * s * s + pi * s * l) << "\n\n6. Объём будет примерно равен " << pi * s * s * h / 3 << endl;
    }
    else if (h == 0 && r1 == 0 && r2 == 0)
    {
        cout << "\n4. Точка!" << endl;
    }
    else if (h < 0)
    {
        cout << "\n4. Негативную высоту не принимаю." << endl;
    }
    else if (r1 == 0 && r2 == 0 && h > 0)
    {
        cout << "\n4. Одномерная линия получаеца." << endl;
    }
    else if (r1 < 0 || r2 < 0 && h > 0)
    {
        cout << "\n4. Негативный радиус не принимаю." << endl;
    }
    else if (r1 == r2 && h > 0)
    {
        cout << "\n4. Ты мне дал цилиндр. Решать не буду. \n\nНу ладно, решу. \n\n5. Объём примерно равен " << pi * r1 * r1 * h << "\n\n6. Площадь полной поверхности примерно равна " << 2 * pi * r1 * r1 + 2 * pi * r1 * h << endl;
    }
    else if (h == 0 && r1 > r2 && r1 > 0 && r2 > 0)
    {
        cout << "\n4. Кольцо. Объема нет, но площадь будет примерно равна " << pi * (r1 * r1 - r2 * r2) * 2 << endl;
    }
    else if (h == 0 && r1 < r2 && r1 > 0 && r2 > 0)
    {
        cout << "\n4. Кольцо. Объема нет, но площадь будет примерно равна " << pi * (r2 * r2 - r1 * r1) * 2 << endl;
    }
    else if (h == 0 && r1 == 0 && r2 > 0)
    {
        cout << "\n4. Круг. Объёма нет, а площадь примерно равна " << pi * r2 * r2 * 2 << endl;
    }
    else if (h == 0 && r2 == 0 && r1 > 0)
    {
        cout << "\n4. Круг. Объёма нет, а площадь примерно равна " << pi * r1 * r1 * 2 << endl;
    }
    else if (h == 0 && r1 == r2)
    {
        cout << "\n4. Бесконечно тонкое двумерное кольцо. 0 площади, 0 объёма." << endl;
    }
}
//ДЗ 2 НОМЕР 2▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H2N2()
{
    system("CLS");
    double a, x;
    cout << "1. Сча я те найду w. \n\n2. При модуле x меньшем единицы(|x| < 1) w равно произведению a на натуральный логарифм модуля x(w = a * ln|x|).\n\n3. При x большем или равным единице(x >= 1) w равно корню разности а и квадрата x(w = sqrt(a - x * x)).\n\n4. Для начала введи a: ";
    getline(wcin, amogus);
    a = wcstod(amogus.c_str(), NULL);
    cout << "\n5. Теперь введи x: ";
    getline(wcin, amogus);
    x = wcstod(amogus.c_str(), NULL);
    if (abs(x) < 1)
    {
        if (a * logl(abs(x)) == -0)
        {
            cout << "\n6. w = 0" << endl;
        }
        else if (x == 0)
        {
            cout << "\n6. Ээээ ну тут выходит натуральный логарифм из нуля, а эт не решить, понимаешь?" << endl;
        }
        else
        {
            cout << "\n6. w = " << a * logl(abs(x)) << endl;
        }
    }
    else
    {
        if ((a - x * x) < 0)
        {
            cout << "\n6. Комплексная w = " << sqrt(x * x - a) << "i." << endl;
        }
        else
        {
            cout << "\n6. w = " << sqrt(a - x * x) << endl;
        }
    }
}
//ДЗ 2 НОМЕР 3▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H2N3()
{
    system("CLS");
    double x, y, b;
    cout << "1. Сча я тебе решу уравнение z = ln(b - y) * sqrt(b - x) для любых x, y, b. \n\n2. Сначала введи x: ";
    getline(wcin, amogus);
    x = wcstod(amogus.c_str(), NULL);
    cout << "\n3. Теперь введи y: ";
    getline(wcin, amogus);
    y = wcstod(amogus.c_str(), NULL);
    cout << "\n4. Теперь введи b: ";
    getline(wcin, amogus);
    b = wcstod(amogus.c_str(), NULL);
    cout << "\n5. x = " << x << ", y = " << y << ", b = " << b << endl;
    if ((logl(b - y) * sqrt(b - x)) == 0)
    {
        cout << "\n6. z = 0." << endl;
    }
    else
    {
        if ((b - y) <= 0)
        {
            cout << "\n6. Сори, натуральный логарифм от отрицательного числа неопределён, это не вычислить." << endl;
        }
        else
        {
            if ((b - x) < 0)
            {
                cout << "\n6. Комплексная z равна " << logl(b - y) * sqrt(x - b) << "i." << endl;
            }
            else
            {
                cout << "\n6. z равна " << logl(b - y) * sqrt(b - x) << endl;
            }
        }
    }
}
//ДЗ 2 НОМЕР 4▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H2N4()
{
    system("CLS");
    double n(0);
    cout << "Cча ты получишь 10 возрастающих натуральных чисел, первое из которых задашь сам. \n\n1 натуральное число = ";
    getline(wcin, amogus);
    n = wcstod(amogus.c_str(), NULL);
    cout << setprecision(5);
    if (floor(n) == n && n > 0)
    {
        if (floor(n) == n && n > 0)
        {
            for (int x(2); x <= 10; ++x)
            {
                n += 1;
                cout << x << " натуральное число = " << n << endl;
            }
        }
    }
    else
    {
        cout << "\nТы не ввёл натуральное число, за что получаешь осуждение и моё закрытие." << endl;
    }
}
//ДЗ 2 НОМЕР 5▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H2N5()
{
    system("CLS");
    double x;
    cout << "Сча я тебе протабулирую функцию y = (x * x - 2 * x + 2) / (x - 1) от x = -4 до x = 4 с шагом в 0.5." << endl;
    cout << toplc + horw80 + topmw + horw80 + toprc + "\n" + vertw + "x                                                                               " + vertw + "y                                                                               " + vertw + "\n" + leftmw + horw80 + midw + horw80 + rightmw << endl;
    for (x = -4; x <= 4; x += 0.5)
    {
        //Корни всегда 1 -2 2
        if ((x - 1) == 0)
        {
            cout << left << vertw << setw(80) << x << setw(1) << vertw << setw(80) << "нет                                                                             " << vertw << endl;
            cout << leftmw + horw80 + midw + horw80 + rightmw << endl;
        }
        else
        {
            cout << left << vertw << setw(80) << x << setw(1) << vertw << setw(80) << (x * x - 2 * x + 2) / (x - 1) << vertw << endl;
            cout << leftmw + horw80 + midw + horw80 + rightmw << endl;
        }
    }
    cout << vertw + "было лень фиксить                                                               " + vertw + "это окно                                                                        " + vertw + "\n" + botlc + horw80 + botmw + horw80 + botrc << endl;
}
//ДЗ 3 НОМЕР 1▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H3N1()
{
    system("CLS");
    double S, p, r, kek, n;
    cout << "1. Сча мы тебе вычислим месячную выплату m по формуле m = (S * r * (1 + r)^n) / (12 * ((1 + r)^n - 1)), при известных сумме S рублей, проценте p и кол-ву лет n, где r = p / 100. \n\n2. Для начала введи сумму займа S(положительную): ";
    while (true)
    {
        getline(wcin, amogus);
        S = wcstod(amogus.c_str(), NULL);
        if (S > 0)
        {
            break;
        }
    }
    cout << "\n3. Теперь введи процент p: ";
    getline(wcin, amogus);
    p = wcstod(amogus.c_str(), NULL);
    cout << "\n4. И наконец кол-во лет n(положительное): ";
    while (true)
    {
        getline(wcin, amogus);
        n = wcstod(amogus.c_str(), NULL);
        if (n > 0)
        {
            break;
        }
    }
    r = p / 100;
    kek = 1 + r;
    stringstream q;
    q.precision(1488);
    q << r;
    string t(q.str());
    string g(t.substr(t.find(".") + 1));
    int booba(g.size());

    if ((12 * ((pow(kek, n) - 1))) != 0)
    {
        cout << "\n5. Тааак падажжи... Значит взяли кредит суммой " << S << " рублей под " << p << "% на " << n << " лет... Значит m = " << (S * r * pow(kek, n)) / (12 * ((pow(kek, n) - 1))) << endl;
    }
    else if (p <= -100)
    {
        cout << "\n5. Ну т.к. кредит теряет 100% от своего размера, то m = 0..." << endl;
    }
    else
    {
        cout << "\n5. Ээээ ну тут в формуле деление на 0 выходит, поэтому ээээээ..." << endl;
    }
}
//ДЗ 3 НОМЕР 2▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H3N2() //по какой-то причине не работает при подключённой <windows.h>
{
    system("CLS");
    long double S(0), m(0), n(0), r(0), mayb(0), negpos(0), step(1); bool breaker(false); int counter(0);
    cout << "1. Ок сча мы тебе резню будем устраивать(находить процент по данным cумме S, времени n и месячным выплатам m). \n\n2. Сначала введи S(положительную): ";
    while (true)
    {
        getline(wcin, amogus);
        S = wcstod(amogus.c_str(), NULL);
        if (S > 0)
        {
            break;
        }
    }
    cout << "\n3. Теперь вводи кол-во лет n(положительное): ";
    while (true)
    {
        getline(wcin, amogus);
        n = wcstod(amogus.c_str(), NULL);
        if (n > 0)
        {
            break;
        }
    }
    cout << "\n4. И наконец месячные выплаты m(не-негативные, если нецифру введёш то 0 будет): ";
    while (true)
    {
        getline(wcin, amogus);
        m = wcstod(amogus.c_str(), NULL);
        if (m >= 0)
        {
            break;
        }
    }
    if (m == 0)
    {
        cout << "\n5. Предполагаю, что процент равен -100(да)." << endl;
    }
    else if (negpos < m) //18446744073709551615
    {
        while (breaker == false)
        {
            if (fm(S, n, r + step * 10) < m)
            {
                //cout << "commence enbigment" << endl;
                step *= 10;
            }
            else if (fm(S, n, r + step) > m)
            {
                //cout << "commence normal ensmollment" << endl;
                step /= 10;
            }
            else if ((fm(S, n, r) == NAN) || (fm(S, n, r) != mayb))
            {
                //cout << "commence ensmollment" << endl;
                step /= 10;
            }
            else
            {
                if (fm(S, n, r) == fm(S, n, r + step))
                {
                    //cout << "Fixируем прибыль..." << endl;
                    r += step * 10;
                }
                else
                {
                    //cout << "микроFixируем прибыль..." << endl;
                    r += step;
                }
            }
            mayb = fm(S, n, r);
            //cout << fm(S, n, 1) << endl;
            //cout << setprecision(530) << r << " " << mayb << " " << m << " " << step << endl;
            counter += 1;
            if (fm(S, n, r + step) < m)
            {
                if ((fm(S, n, r + step)) == (fm(S, n, r)))
                {
                    //cout << "lel" << endl;
                    if (fm(S, n, r + step) == (1e+300 * 1e+300))
                    {
                        cout << "\n5. Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. На " << counter << "ой итерации я понял, что введены были какие-то кринжачные данные и ближе к проценту я не подойду...\n\n7. Конечная итерация(r, подбор, ввод, шаг): " << r << " " << mayb << " " << m << " " << step << "\n\n8. Самый близкий ежемесячный процент равен " << round(r * 100) << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")" << endl;
                        break;
                    }
                    step *= 10;
                }
                //cout << "commence smellbebrament..." << endl;
                r += step;
            }
            else if ((fm(S, n, r) == (1e+300 * 1e+300)) || ((fm(S, n, r) != fm(S, n, r)) && (step < 1.192092896e-07F))) //1.192092896e-07F
            {
                cout << "\n5. Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. На " << counter << "ой итерации я понял, что введены были какие-то кринжачные данные и ближе к проценту я не подойду...\n\n7. Конечная итерация(r, подбор, ввод, шаг): " << r << " " << mayb << " " << m << " " << step << "\n\n8. Самый близкий ежемесячный процент равен " << round(r * 100) << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")" << endl;
                break;
            }
            else if ((max(abs(mayb), abs(m))) - (min(abs(mayb), abs(m))) < 2.2204460492503131e-016) //2.2204460492503131e-016
            {
                cout << "\n5. Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. Ежемесячный процент равен " << round(r * 100) << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")\n\n7. Остановился на " << counter << "ой итерации." << endl;
                break;
            }
            if ((fm(S, n, r + step) == fm(S, n, r)) && (step < 2.2204460492503131e-016))
            {
                cout << "\n5. Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. Ежемесячный процент равен " << round(r * 100) << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")\n\n7. Остановился на " << counter << "ой итерации." << endl;
                break;
            }
        }
    }
    else if (negpos > m)
    {
        while (breaker == false)
        {
            if (r < -1)
            {
                cout << "\n5. 5На " << counter << "ой итерации я понял, что q очень близка к -100." << endl;
                break;
            }
            else if (fm(S, n, r - step * 10) > m)
            {
                step *= 10;
            }
            else if (fm(S, n, r - step) < m)
            {
                step /= 10;
            }
            else
            {
                r -= step;
            }
            mayb = fm(S, n, r);
            //cout << setprecision(530) << r << " " << mayb << " " << m << " " << step << endl;
            counter += 1;
            if (((max(mayb, m)) - (min(mayb, m))) < 0.00004)
            {
                if (round(r * 100) == -0)
                {
                    cout << "\n5. 1Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. Ежемесячный процент равен " << round(r * 100) * -1 << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")\n\n7. Остановился на " << counter << "ой итерации." << endl;
                    break;
                }
                else
                {
                    cout << "\n5. 0Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. Ежемесячный процент равен " << round(r * 100) << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")\n\n7. Остановился на " << counter << "ой итерации." << endl;
                    break;
                }
            }
            else if (fm(S, n, r - step) > m)
            {
                if ((fm(S, n, r - step)) == (fm(S, n, r)))
                {
                    if (round(r * 100) == -0) //numeric_limits<long double>::max_digits10 == 53
                    {
                        cout << "\n5. 4Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. Ежемесячный процент равен " << round(r * 100) * -1 << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")\n\n7. Остановился на " << counter << "ой итерации." << endl;
                        break;
                    }
                    else
                    {
                        cout << "\n5. 3Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. Ежемесячный процент равен " << round(r * 100) << "(" << r * 100 << ")\n\n" << S << " VS " << round(m * 12 * n) << "(" << m * 12 * n << ") VS " << round(mayb * 12 * n) << "(" << mayb * 12 * n << ")\n\n7. Остановился на " << counter << "ой итерации." << endl;
                        break;
                    }
                }
                r -= step;
            }
            else if (fm(S, n, r) != fm(S, n, r))
            {
                cout << "\n5. 2Конечная итерация(r, подбор, ввод, шаг): " << endl << endl << r << endl << endl << mayb << endl << endl << "СРАВНИВАЕТСЯ С" << endl << endl << m << endl << endl << step << "\n\n6. За (" << counter << ") итераций я понял, что ты решил меня потроллить маленькой n..." << endl;
                break;
            }
        }
    }
    else if (negpos == m)//12000000 1 1000000.00000000004 || 12000000 1 999999.99999999995
    {
        cout << "\n5. С моей точки зрения(округляющей...) ты ввёл число, равное S / n / 12, => процент = 0." /*<< negpos << " " << m */ << endl;
    }
    //cout << "че" << endl;
}
//ДЗ 3 НОМЕР 3▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H3N3()
{
    system("CLS");
    wstring filename(L""), filetext(L""); string filetextbutnotwide("");
    cout << "\n1. Введи название файла с пробелами или без (из букв тока латинские и без :<\"|*/>? пж): ";
    //wcin.ignore();
    getline(wcin, filename);
    cout << "\n2. Введи текст или введи 0 для случайного текста из букв, чисел и символов по умолчанию(тут тоже если буквы то латинские окда?): ";
    //wcin.clear();
    getline(wcin, filetext);
    filename += L".txt";
    if (filetext == L"0")
    {
        wfstream filew;
        filew.open(filename, wios::out);
        if (!filew)
        {
            cout << "\n3. Слит, не смог даже файл для записи открыть..." << endl;
            return;
        }
        int howlong;
        cout << "\n3. Задай обязательно положительную длину случайного текста(не рекомендую больше миллиона): ";
        while (true)
        {
            getline(wcin, amogus);
            howlong = wcstod(amogus.c_str(), NULL);
            if (howlong > 0)
            {
                break;
            }
        }
        filetextbutnotwide = rstr(howlong);
        filew << wstring(filetextbutnotwide.begin(), filetextbutnotwide.end());
        filew.close();
        cout << "\n4. Записали, закрыли, открываем, читаем:\n\n";
        wfstream fileo;
        fileo.open(filename, wios::in);
        wchar_t sus;
        while (fileo.get(sus))
        {
            wcout << sus;
        }
        cout << "\n\n5. И снова, не закрывая файл:\n" << endl;
        fileo.clear();
        fileo.seekg(0, wios::beg);
        while (fileo.get(sus))
        {
            wcout << sus;
        }
        fileo.close();
        cout << "\n\n6. Файл закрыт и будет удалён после закрытия задания. Введи что угодно чтоб выйти из программы: ";
        getline(wcin, amogus);
        _wremove(filename.c_str());
    }
    else
    {
        wfstream filew;
        filew.open(filename, wios::out);
        if (!filew)
        {
            cout << "\n3. Слит, не смог даже файл для записи открыть..." << endl;
            return;
        }
        filew << filetext;
        filew.close();
        cout << "\n3. Записали, закрыли, открываем, читаем:\n\n";
        wfstream fileo;
        fileo.open(filename, wios::in);
        wchar_t sus;
        while (fileo.get(sus))
        {
            wcout << sus;
        }
        cout << "\n\n4. И снова, не закрывая файл:\n" << endl;
        fileo.clear();
        fileo.seekg(0, wios::beg);
        while (fileo.get(sus))
        {
            wcout << sus;
        }
        fileo.close();
        cout << "\n\n5. Файл закрыт и будет удалён после закрытия задания. Введи что угодно чтоб выйти из программы: ";
        getline(wcin, amogus);
        _wremove(filename.c_str());
    }
}
//ДЗ 3 НОМЕР 4▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H3N4() //Кроме написания отрицательных(дробных) чисел превращает точку перед числом в целую часть числа, как и первый 0 в числе без точки(но приоритет у точки, поэтому из строки 0001337 делает 0.001337, из строки .0001337 делает 0.0001337)
{ //В теории превратит строку -07492.05830.0.05492AXZET-01424EZEZEZ63824.5839BEBRA.01234 в строку -0.7492 0.05830 0.0 0.05492 -0.1424 63824.5839 0.01234
    system("CLS");
    int cringlen(0);
    ofstream lel("lmao_bottom_text.txt");
    cout << "Сча создам файл с текстом и выну оттуда все числа.\n\nОтветь на след. вопрос латинской y, или дам тебе классическую неприятную строку\n\n(-.-.0000979870.0908907.9090780-.-.-.-09870890.--.-.0-.090.-.0-0.0.0.00001-0-0.1)\n\nСгенерировать кринжа? [y]: ";
    getline(wcin, amogus);
    if (amogus == L"y")
    {
        cout << "\nВведи положительную длину кринжа(больше миллиона не стоит)\n";
        while (true)
        {
            printf_s(">");
            getline(wcin, amogus);
            inpn = wcstoll(amogus.c_str(), NULL, 10);
            ERASE_CURRENT_LINE; UP_LINES(1); ERASE_CURRENT_LINE;
            amogus = inpn;
            if (inpn > 0) { break; }
        }
        lel << rstr(cringlen, "123456789.-.-.-.-.-.-.-.-.-");
    }
    else
    {
        lel << "-.-.0000979870.0908907.9090780-.-.-.-09870890.--.-.0-.090.-.0-0.0.0.00001-0-0.1" << endl;
    }
    lel.close();
    wifstream balls("lmao_bottom_text.txt");
    wstringstream bofa;//миллиард одз на 31 
    bofa << balls.rdbuf();
    wstring toproc = bofa.str(), filtered(L"");//произвольный доступ через фстрим дважды полностью не закрывая файл выцепить из него всю информацию, запись в середину, и прочая, прочая, прочая 33
    int radixer(0), counter(0), zerominus(0);
    for (int i(0); i < toproc.size(); ++i)
    {
        if (isdigit(toproc[i]) && isdigit(toproc[i + 1]))
        {
            if (toproc[i] == L'0')
            {
                if (counter == 0)
                {
                    filtered += toproc[i];
                    filtered += L'.';
                    ++radixer;
                }
                else
                {
                    filtered += toproc[i];
                }
            }
            else
            {
                filtered += toproc[i];
            }
            ++counter;
        }
        else if (isdigit(toproc[i]) && !isdigit(toproc[i + 1]))
        {
            if (toproc[i + 1] == L'.')
            {
                if (radixer == 0)
                {
                    filtered += toproc[i];
                }
                else
                {
                    filtered += toproc[i];
                    filtered += L' ';
                }
            }
            else
            {
                filtered += toproc[i];
                filtered += L' ';
            }
            ++counter;
        }
        else if (toproc[i] == L'-' && isdigit(toproc[i + 1]))
        {
            counter = 0;
            radixer = 0;
            filtered += ' ';
            filtered += toproc[i];
        }
        else if (toproc[i] == L'.' && isdigit(toproc[i + 1]))
        {
            if (radixer == 0)
            {
                if (counter == 0)
                {
                    filtered += L'0';
                    filtered += toproc[i];
                    ++counter;
                    ++counter;
                }
                else
                {
                    filtered += toproc[i];
                    ++counter;
                    ++counter;
                }
            }
            else
            {
                filtered += L'0';
                filtered += toproc[i];
                ++counter;
                ++counter;
            }
        }
        else if (!isdigit(toproc[i]))
        {
            radixer = 0;
            counter = 0;
        }
    }
    for (int i(1); i < filtered.size(); ++i)
    {
        if (isspace(filtered[i - 1]) && isspace(filtered[i]))
        {
            filtered.erase((i - 1), 1);
        }
    }
    for (int i(0); i < filtered.size(); ++i)
    {
        if (filtered[i] == L'-' && filtered[i + 1] == L'0')
        {
            for (int z(i + 1); z < filtered.size(); ++z)
            {
                if (filtered[z] == L' ' && zerominus == 0)
                {
                    cout << "1";
                    filtered.erase(i, 1);
                    break;
                }
                else if (filtered[z] == L' ' && zerominus != 0)
                {
                    cout << "2";
                    zerominus = 0;
                    break;
                }
                else if (isgreater(filtered[z], L'0'))
                {
                    ++zerominus;
                }
            }
        }
    }
    wcout << "\n1. Символы файла: \n\n" << toproc << endl;
    wcout << "\n2. Числа файла: \n\n" << filtered << endl;
    balls.close();
    cout << "\n3. Файл закрыт и будет удалён после закрытия программы. Введи что угодно шоб программа закрылась: ";//deez nuts
    getline(wcin, amogus);
    remove("lmao_bottom_text.txt");
}
//ДЗ 3 НОМЕР 5▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H3N5()
{
    system("CLS");
    string tosort(""), letters("");
    char swap; int sortlen(0);
    //tosort = "zZxXyYwWbBjJcCsSaAdD@#$%^&4300";
    //OR//
    cout << "Введи длину (только положительную) строки для сортировки: ";
    while (true)
    {
        getline(wcin, amogus);
        sortlen = wcstod(amogus.c_str(), NULL);
        if (sortlen > 0)
        {
            break;
        }
    }
    //tosort = rstr(sortlen);
    tosort = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzazzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzazzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    cout << "\n1. Было: \n\n" << tosort << endl;
    for (int i(0); i != tosort.size(); ++i)
    {
        if (isalpha(tosort[i]))
        {
            letters += tosort[i];
        }
    }
    for (int i(0); i < letters.size(); ++i)
    {
        for (int c(i + 1); c != letters.size(); ++c)
        {
            int s(tolower(letters[i]) - tolower(letters[c]));
            if (s == 0)
            {
                s = letters[i] - letters[c];
            }
            if (s > 0)
            {
                swap = letters[i];
                letters[i] = letters[c];
                letters[c] = swap;
                //cout << letters << endl;
            }
        }
    }
    cout << "\n3. Стало: \n\n" << letters << endl;
}
//ДЗ 4 НОМЕР 1▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N1()
{
    system("CLS");
    string filename("lmao_top_number.txt"); double num(0), sum(0), from(0), to(0); char sus;
    cout << "1. Сча я создам файл, запишу туда 10 чисел, закрою его, затем прочитаю его.\n\n2. Генерирую...\n";
    fstream lebruh;
    lebruh.open(filename, ios::out);
    cout << "\nВведи минимум для генерации чисел: ";
    getline(wcin, amogus);
    from = wcstod(amogus.c_str(), NULL);
    cout << "\nТеперь введи максимум для генерации чисел(вперёд не продвинешься пока не введёшь больше минимума): ";
    cout << endl << from << endl;
    while (true)
    {
        getline(wcin, amogus);
        to = wcstod(amogus.c_str(), NULL);
        cout << to << endl;
        if (to > from)
        {
            break;
        }
    }
    stringstream q;
    q.precision(1488);
    num = nrg(from, to);
    q << num;
    cout << num << endl;
    string t(q.str());
    string p(t.substr(t.find(".") + 1));
    int booba(p.size());
    lebruh << fixed << showpoint << setprecision(booba);

    cout << "\nТочность: " << booba << endl;
    for (int kek(0); kek < 10; ++kek)
    {
        lebruh << nrg(from, to) << " ";
    }
    lebruh << '\n';
    lebruh.close();
    fstream elbruh;
    elbruh.open(filename, ios::in);
    cout << "\n3. Записали, закрыли, открываем, читаем... Файл гласит: \n\n";
    while (elbruh.get(sus))
    {
        cout << sus;
    }
    cout << "\nВычисляем: \n\n";
    elbruh.clear();
    elbruh.seekg(0, ios::beg);
    while (elbruh >> num)
    {
        cout << sum << " + " << num << " = ";
        sum += num;
        cout << sum << endl;
    }
    elbruh.close();
    cout << "\n4. Сумма чисел: " << sum << "\n\nФайл закрыт и будет удалён после закрытия задачи. Введи что угодно чтобы закрыть меня: ";
    getline(wcin, amogus);
    remove("lmao_top_number.txt");
}
//ДЗ 4 НОМЕР 2▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N2()
{
    system("CLS");
    double boof(0);
    cout << "1. Я - ясновидящая программа. Дай мне ввод, а я тебе скажу знак первого в нём числа.\n";
    while (true)
    {
        cout << "\nВведи число: ";
        getline(wcin, amogus);
        boof = wcstod(amogus.c_str(), NULL);
        getsign(boof);
        cout << "\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 4 НОМЕР 3▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N3()
{
    system("CLS");
    int obama(0);
    cout << "Тебе найти площадь кого?\n";
    while (true)
    {
        cout << "\nПрямоугольник[1]; Треугольник[2]; Круг[3]; ";
        while (true)
        {
            getline(wcin, amogus);
            obama = wcstod(amogus.c_str(), NULL);
            if (obama == 1 || obama == 2 || obama == 3)
            {
                break;
            }
        }
        if (obama == 1)
        {
            rectalgle();
        }
        if (obama == 2)
        {
            triangle();
        }
        if (obama == 3)
        {
            circle();
        }
        cout << "\nЕщё найти? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;;
        }
    }
}
//ДЗ 4 НОМЕР 4▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N4()
{
    system("CLS");
    cout << "Нарисовать тебе 'Былую Славу' 1912г.? [y]: ";
    getline(wcin, amogus);
    if (amogus != L"y")
    {
        return;
    }
#ifdef _WINDOWS_
    cout << "\nТут мог быть красивый флаг..." << endl;
    return;
#else
    while (true)
    {
        system("CLS");
        for (int a(1); a < 7; ++a)
        {
            if (a % 2 != 0) //★ \u2605
            {
                cout << bluebg << u8" ✶ ✶ ✶ ✶ ✶ ✶ ✶ ✶ " << reset;
                cout << red;
                for (int e(0); e < 31; ++e)
                {
                    cout << u8"█";
                }
                cout << reset << "\n";
            }
            else
            {
                cout << bluebg << u8" ✶ ✶ ✶ ✶ ✶ ✶ ✶ ✶ ";
                for (int e(0); e < 31; ++e)
                {
                    cout << u8"█";
                }
                cout << reset << "\n";
            }
        }
        for (int b(1); b < 8; ++b)
        {
            if (b % 2 != 0)
            {
                cout << red;
                for (int e(0); e < 48; ++e)
                {
                    cout << u8"█";
                }
                cout << reset << "\n";
            }
            else
            {
                for (int e(0); e < 48; ++e)
                {
                    cout << u8"█";
                }
                cout << "\n";
            }
        }
        cout << "\nЕщё нарисовать? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
#endif
}
//ДЗ 4 НОМЕР 5▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N5()
{
    system("CLS");
    int n = 80;
    for (int i = n / 3; i >= -n / 3; --i)
    {
        for (int j = -n; j <= n; ++j)
        {
            if (i == 0 && j == 0)
            {
                cout << "0";
            }
            else if (i == (int)(sin(j * 0.1) * 10))
            {
                cout << u8"•";
            }
            else if (i == 0 && j == n)
            {
                cout << "x";
            }
            else if (i == 0 && j == n - 1)
            {
                cout << ">";
            }
            else if (i == n / 3 && j == 0)
            {
                cout << "y";
            }
            else if (i == n / 3 - 1 && j == 0)
            {
                cout << "^";
            }
            else if ((j == 0 && i == 9) || (j == 0 && i == -9) || (j == (int)(((pi * 10) / 2) + 1) && i == 0) || (j == -(int)(((pi * 10) / 2) + 1) && i == 0))
            {
                cout << u8"+";
            }
            else if ((j == 2 && i == 9) || (j == 2 && i == -9))
            {
                cout << "1";
            }
            else if ((i == 0) || (j == 1 && i == -9) || (j == (int)(((pi * 10) / 2) + 1) && i == -2) || (j == -(int)(((pi * 10) / 2) + 1) && i == -2) || (j == -(int)(((pi * 10) / 2) + 2) && i == -1))
            {
                cout << u8"-";
            }
            else if (j == 0)
            {
                cout << u8"|";
            }
            else if ((j == (int)(((pi * 10) / 2) + 1) && i == -1) || (j == -(int)(((pi * 10) / 2) + 1) && i == -1))
            {
                cout << "п";
            }
            else if ((j == (int)(((pi * 10) / 2) + 1) && i == -3) || (j == -(int)(((pi * 10) / 2) + 1) && i == -3))
            {
                cout << "2";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}
//ДЗ 4 НОМЕР 6▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N6()//
{
    system("CLS");
    int obama(0);
    cout << "Тебе перевести из человеческой в римскую или наоборот?\n\nПРИ ПЕРЕВОДЕ РИМ => ЧЕЛ:\n\nПереведу число такой длины, какой ты сможешь ввести.\nТ.к. черточку над цифрой не ввести, верхний регистр умножаю в тысячу раз. Допустимые римские цифры в любом регистре: n(0), i(1), v(5), x(10), l(50), c(100), d(500), m(1000);\nБольше трёх одинаковых цифр подряд вводить низзя(кроме M).\nОтнимать(писать слева) маленькую цифру можно только от двух ближайших бОльших цифр(Ii от Vv & Xx, но не от Ll+, например) и не более одного раза(низзя IIX).\nНеравные целой степени десятки числа(Vv, Ll, Dd) нельзя отнимать и повторять подряд.\nN может быть только сама по себе, единственная во вводе.\nДопустимо любое кол-во минусов перед числом(каждый меняет знак на противоположный, перед N минусы ставить низзя);\n\nПРИ ПЕРЕВОДЕ ЧЕЛ => РИМ:\n\nДиапазон переводимых чисел (-9223372036854775807; 9223372036854775807), диапазон рекомендованных для ввода чисел (-2147483647; 2147483647)\nЕсли хочешь, чтоб диапазон рекомендованных вводов был шире, то, пж, подскажи способ в римской системе счисления писать цифры больше миллиона(M).\nКак-никак, несколько черточек(умножений на тысячу) над цифрой не попишешь, а с максимальной цифрой M даже 2147483647 будет состоять из более чем двух тысяч цифр M, \nведь M в числе примерно столько, сколько в нём тысяч...\nМогу, конечно, и число 2147483647000 перевести... и даже 9223372036854775807 начать переводить(но не закончить).\nПеред числом допустим только один минус.\n";
    while (true)
    {
        cout << "\nЧел => Рим [1], Рим => Чел [2] ";
        while (true)
        {
            getline(wcin, amogus);
            obama = wcstod(amogus.c_str(), NULL);
            if (obama == 1 || obama == 2 || obama == 3)
            {
                break;
            }
        }
        if (obama == 1)
        {
            ArToRo();
        }
        if (obama == 2)
        {
            RoToAr();
        }
        cout << "\nЕщё перевести? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 4 НОМЕР 7▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N7()
{
    system("CLS");
    long long m(0), i(0), c(0), s;
    cout << "Ок, сча тебе сгенерирую псевдослучайное число абсолютно гениальным алгоритмом по формуле \ns(i + 1) = (m * s(i) + i) mod c, где m, i, c - целые числа, которые ты сча мне задашь.\n";
    while (true)
    {
        s = 0;
        cout << "\nВведи m: ";
        getline(wcin, amogus);
        m = wcstoll(amogus.c_str(), NULL, 10);
        cout << "\nВведи i: ";
        getline(wcin, amogus);
        i = wcstoll(amogus.c_str(), NULL, 10);
        cout << "\nВведи c: ";
        getline(wcin, amogus);
        c = wcstoll(amogus.c_str(), NULL, 10);
        for (long long le(1); le <= i; ++le)
        {
            s = (m * s + (le - 1)) % c;
        }
        cout << "\nРезультат: " << s << "\n\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 4 НОМЕР 8▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N8()
{
    system("CLS");
    int rm(0), mudem(0), cm(0), classique(0), maxprofitrader(0), minprofitrader(0), maxtaxtrader(0), mintaxtrader(0);
    double minprofit(1e+300 * 1e+300), maxprofit(1e+300 * 1e+300 * -1), sumofprofit(0), mintax(1e+300 * 1e+300), maxtax(1e+300 * 1e+300 * -1), sumoftax(0), allbux(0);
    vector<vector<double>> wares(0, vector<double>(0)), pricestaxes(0, vector<double>(0));
    cout << "Сам введёшь значения[1], или тебе всё подставить[2]? ";
    while (true)
    {
        getline(wcin, amogus);
        classique = wcstod(amogus.c_str(), NULL);
        if (classique == 1)
        {
            cout << "\nОк, вводи кол-во(положительное целое число) продавцов(стандартно 3): ";
            while (true)
            {
                getline(wcin, amogus);
                rm = wcstod(amogus.c_str(), NULL);
                if (rm > 0)
                {
                    break;
                }
            }
            cout << "\nОк, вводи кол-во(положительное целое число) товаров(стандартно 4): ";
            while (true)
            {
                getline(wcin, amogus);
                mudem = wcstod(amogus.c_str(), NULL);
                if (mudem > 0)
                {
                    break;
                }
            }
            cout << "\nОк, вводи кол-во(положительное целое число) денежных величин на товар(стандартно и минимум 2; 1 всегда цена, 2 всегда комиссионные): ";
            while (true)
            {
                getline(wcin, amogus);
                cm = wcstod(amogus.c_str(), NULL);
                if (cm >= 2)
                {
                    break;
                }
            }
            vector<double> warevector(mudem, 0);
            for (int war(1); war <= rm; ++war)
            {
                wares.push_back(warevector);
            }
            vector<double> taxesvector(cm, 0);
            for (int tax(1); tax <= mudem; ++tax)
            {
                pricestaxes.push_back(taxesvector);
            }
            for (int fag(0); fag < rm; ++fag)
            {
                for (int got(0); got < mudem; ++got)
                {
                    cout << "Продавец " << fag + 1 << " - введи кол-во товара " << got + 1 << ": ";
                    getline(wcin, amogus);
                    wares[fag][got] = wcstod(amogus.c_str(), NULL);
                }
            }
            for (int fag(0); fag < mudem; ++fag)
            {
                for (int got(0); got < cm; ++got)
                {
                    cout << "Товар " << fag + 1 << " - введи величину " << got + 1 << ": ";
                    getline(wcin, amogus);
                    pricestaxes[fag][got] = wcstod(amogus.c_str(), NULL);
                }
            }
            break;
        }
        else if (classique == 2)
        {
            rm = 3;
            mudem = 4;
            cm = 2;
            wares.push_back({ 5, 2, 0, 10 });
            wares.push_back({ 3, 5, 2, 5 });
            wares.push_back({ 20, 0, 0, 0 });
            pricestaxes.push_back({ 1.2, 0.5 });
            pricestaxes.push_back({ 2.8, 0.4 });
            pricestaxes.push_back({ 5, 1 });
            pricestaxes.push_back({ 2, 1.5 });
            break;
        }
    }
    vector<vector<double>> multos(rm, vector<double>(cm + 1));
    for (int row(0); row < rm; ++row)
    {
        for (int col(0); col < cm; ++col)
        {
            for (int muda(0); muda < mudem; ++muda)
            {
                multos[row][col + 1] += wares[row][muda] * pricestaxes[muda][col];
            }
        }
        for (int row(0); row < rm; ++row)
        {
            multos[row][0] = row + 1;
        }
    }
    cout.unsetf(ios_base::fixed);
    cout << noshowpoint << setprecision(4);
    cout << toplc;
    for (int amongus(0); amongus < cm; ++amongus)
    {
        cout << horw6 << horw << horw << horw << topmw;
    }
    cout << horw6 << horw << horw << horw << toprc << endl;
    cout << vertw << "Продавец " << vertw << "Общ Стоим" << vertw << "Комиссия ";
    for (int amongus(0); amongus < cm - 2; ++amongus)
    {
        cout << vertw << "         ";
    }
    cout << vertw << endl;
    cout << leftmw;
    for (int amongus(0); amongus < cm; ++amongus)
    {
        cout << horw6 << horw << horw << horw << midw;
    }
    cout << horw6 << horw << horw << horw << rightmw << endl;
    for (int row(0); row < rm; ++row)
    {
        cout << vertw;
        for (int col(0); col <= cm; ++col)
        {
            cout << setw(9) << left << multos[row][col];
            cout << vertw;
            if (col == cm)
            {
                cout << endl;
            }
        }
        if (row < (rm - 1))
        {
            cout << leftmw;
            for (int amongus(0); amongus < cm; ++amongus)
            {
                cout << horw6 << horw << horw << horw << midw;
            }
            cout << horw6 << horw << horw << horw << rightmw << endl;
        }
        else
        {
            cout << botlc;
            for (int amongus(0); amongus < cm; ++amongus)
            {
                cout << horw6 << horw << horw << horw << botmw;
            }
            cout << horw6 << horw << horw << horw << botrc;
        }
    }
    for (int row(0); row < rm; ++row)
    {
        sumofprofit += (multos[row][1] - multos[row][2]);
        sumoftax += multos[row][2];
        allbux += multos[row][1];
        if ((multos[row][1] - multos[row][2]) < minprofit)
        {
            minprofit = multos[row][1] - multos[row][2];
            minprofitrader = multos[row][0];
        }
        if ((multos[row][1] - multos[row][2]) > maxprofit)
        {
            maxprofit = multos[row][1] - multos[row][2];
            maxprofitrader = multos[row][0];
        }
        if (multos[row][2] < mintax)
        {
            mintax = multos[row][2];
            mintaxtrader = multos[row][0];
        }
        if (multos[row][2] > maxtax)
        {
            maxtax = multos[row][2];
            maxtaxtrader = multos[row][0];
        }
    }
    cout << "\n1)Больше всех получил продавец " << maxprofitrader << ", заработавший " << maxprofit << ", а меньше всего - продавец " << minprofitrader << ", заработавший " << minprofit << ".\n";
    cout << "\n2)Больше всех комиссионных собрал продавец " << maxtaxtrader << ", собравший " << maxtax << ", а меньше всего - продавец " << mintaxtrader << ", собравший " << mintax << ".\n";
    cout << "\n3)Общая сумма выручки за все товары составляет " << sumofprofit << ".\n";
    cout << "\n4)Общая сумма собранных всеми продавцами комиссионных составляет " << sumoftax << ".\n";
    cout << "\n5)Через руки продавцов в общей сумме прошло " << allbux << " денег.\n";
}
//ДЗ 4 НОМЕР 9▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H4N9()
{
    system("CLS"); int basefrom, baseto, dotcount; bool proverka; string bebra;
    cout << fixed << showpoint << setprecision(18) << "Ок, сча переведу число из базы в базу.\n";
    while (true)
    {
        cout << "\nИз какой базы переводим? [2-36]: ";
        while (true)
        {
            basefrom = 0;
            getline(wcin, amogus);
            basefrom = wcstol(amogus.c_str(), NULL, 10);
            if (basefrom >= 2 && basefrom <= 36)
            {
                break;
            }
        }
        cout << "\nВ какую базу переводим? [2-36]: ";
        while (true)
        {
            baseto = 0;
            getline(wcin, amogus);
            baseto = wcstol(amogus.c_str(), NULL, 10);
            if (baseto >= 2 && baseto <= 36)
            {
                break;
            }
        }
        proverka = true;
        cout << "\nОк, вводи число в " << basefrom << "-СС [0...." << unbased(basefrom - 1) << "]: ";
        while (proverka)
        {
            dotcount = 0;
            getline(wcin, amogus);
            for (int i(0); i < amogus.size(); ++i)
            {
                if (amogus[i] == '.')
                {
                    ++dotcount;
                    if (dotcount > 1)
                    {
                        cout << "Недопустимый ввод, перевводи: ";
                        break;
                    }
                }
                if (((based(amogus[i]) < 0) && (amogus[i] != '.')) || (based(amogus[i]) > (basefrom - 1)))
                {
                    cout << "Недопустимый ввод, перевводи: ";
                    break;
                }
                if (i == (amogus.size() - 1))
                {
                    proverka = false;
                }
            }
        }
        string bebra = string(amogus.begin(), amogus.end());
        cout << "\nOк, число в " << baseto << "-СС: " << basetobase(bebra, basefrom, baseto) << "\n\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 5 НОМЕР 1▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H5N1()
{
    long long a(0), b(0), maxdel(0), minum(0), maxnum(0), maxel(0); int wae(0);
    cout << "Ок, сча я найду тебе наибольший общий делитель двух чисел, которые ты сам введёшь.\n";
    while (true)
    {
        cout << "\nВведи первое число[!0]: ";
        while (true)
        {
            getline(wcin, amogus);
            a = wcstoll(amogus.c_str(), NULL, 10);
            if (a != 0)
            {
                break;
            }
        }
        a = llabs(a);
        cout << "\nОк, теперь второе число[!0]: ";
        while (true)
        {
            getline(wcin, amogus);
            b = wcstoll(amogus.c_str(), NULL, 10);
            if (b != 0)
            {
                break;
            }
        }
        b = llabs(b);
        cout << "\nОк, тебе делением[1] или вычитанием[2]?: ";
        while (true)
        {
            getline(wcin, amogus);
            wae = wcstoll(amogus.c_str(), NULL, 10);
            if (wae > 0)
            {
                break;
            }
        }
        switch (wae)
        {
        case(1):
        {
            while (a != 0 && b != 0)
            {
                long long e = a;
                a = b;
                b = (e % b);
            }
            maxdel = max(a, b);
            break;
        }
        case(2):
        {
            while (a != b)
            {
                if (a > b)
                {
                    a -= b;
                }
                if (a < b)
                {
                    b -= a;
                }
            }
            maxdel = a;
        }
        }
        cout << "\nНОД: " << maxdel << "\n\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }

}
//ДЗ 5 НОМЕР 2▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H5N2()
{
    cout << "Ок, сча найду тебе все простые числа от 2 до заданного числа.\n";
    long long n(0);
    while (true)
    {
        cout << "\nВведи число, до которого искать[1 < n <= 999999]: ";
        while (true)
        {
            getline(wcin, amogus);
            n = wcstoll(amogus.c_str(), NULL, 10);
            if (n > 1 && n <= 999999)
            {
                break;
            }
        }
        vector<bool> nums(n, true); string res("");
        for (long long i(2); i <= sqrt(n); ++i)
        {
            if (nums[i])
            {
                for (long long c = i * i; c < n; c += i)
                {
                    nums[c] = false;
                }
            }
        }
        for (long long i(2); i < n; ++i)
        {
            if (nums[i])
            {
                res = res + to_string(i) + " ";
            }
        }
        cout << res << endl;
        cout << "\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 5 НОМЕР 3▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H5N3() //тут несколько заданий из 5.3 + одно задание из 5.4
{
    while (true)
    {
        system("CLS");
        fstream le; string f("bebra bobra babra bibra.txt");
        le.open(f, ios_base::out);
        le << rstr(10000);
        le << " \n\nHello, hello? Uh, I wanted to record a message for you to help you get settled in on your first night. Um, I actually worked in that office before you. I'm finishing up my last week now, as a matter of fact. So, I know it can be a bit overwhelming, but I'm here to tell you there's nothing to worry about. Uh, you'll do fine. So, let's just focus on getting you through your first week. Okay?\n\nUh, let's see, first there's an introductory greeting from the company that I'm supposed to read. Uh, it's kind of a legal thing, you know. Um, 'Welcome to Freddy Fazbear's Pizza. A magical place for kids and grown-ups alike, where fantasy and fun come to life. Fazbear Entertainment is not responsible for damage to property or person. Upon discovering that damage or death has occurred, a missing person report will be filed within 90 days, or as soon property and premises have been thoroughly cleaned and bleached, and the carpets have been replaced.'\n\nBlah blah blah, now that might sound bad, I know, but there's really nothing to worry about. Uh, the animatronic characters here do get a bit quirky at night, but do I blame them? No. If I were forced to sing those same stupid songs for twenty years and I never got a bath? I'd probably be a bit irritable at night too. So, remember, these characters hold a special place in the hearts of children and we need to show them a little respect, right? Okay.\n\nSo, just be aware, the characters do tend to wander a bit. Uh, they're left in some kind of free roaming mode at night. Uh...Something about their servos locking up if they get turned off for too long. Uh, they used to be allowed to walk around during the day too. But then there was The Bite of '87. Yeah. I-It's amazing that the human body can live without the frontal lobe, you know? Uh, now concerning your safety, the only real risk to you as a night watchman here, if any, is the fact that these characters, uh, if they happen to see you after hours probably won't recognize you as a person. They'll p-most likely see you as a metal endoskeleton without its costume on. Now since that's against the rules here at Freddy Fazbear's Pizza, they'll probably try to...forcefully stuff you inside a Freddy Fazbear suit. Um, now, that wouldn't be so bad if the suits themselves weren't filled with crossbeams, wires, and animatronic devices, especially around the facial area. So, you could imagine how having your head forcefully pressed inside one of those could cause a bit of discomfort...and death. Uh, the only parts of you that would likely see the light of day again would be your eyeballs and teeth when they pop out the front of the mask, heh.\n\nY-Yeah, they don't tell you these things when you sign up. But hey, first day should be a breeze. I'll chat with you tomorrow. Uh, check those cameras, and remember to close the doors only if absolutely necessary. Gotta conserve power. Alright, good night. \n\n" << endl;
        cout << "Введи микротекст, который я добавлю в файл[из букв тока латинские пж]: ";
        getline(wcin, amogus);
        le << "\n" << string(amogus.begin(), amogus.end()) << "\n";
        le.close();
        fstream el;
        el.open(f, ios_base::in);
        stringstream lol;
        lol << el.rdbuf();
        string wlongest(""), wshortest(""), curword(""); map<char, pair<int, long double>> stats; int oftenest(0), rarestest(99999999), curlen(0), minlen(99999999), maxlen(0), lul(lol.str().size());  char oftestchar('\n'), rarestchar('\n');
        for (char c : lol.str())
        {
            ++stats[c].first;
            wcout << c;
            if (c != ' ' && c != '\n')
            {
                curword += c;
                ++curlen;
            }
            else
            {
                if (curlen > maxlen)
                {
                    wlongest = curword;
                    maxlen = curlen;
                }
                if (curlen < minlen && curlen > 0)
                {
                    wshortest = curword;
                    minlen = curlen;
                }
                curword = "";
                curlen = 0;
            }
        }
        for (const pair<char, pair<int, long double>>& ligma : stats)
        {
            long double lal(ligma.second.first);
            long double kek(lal / lul);
            stats[ligma.first].second = kek;
            if (ligma.second.first > oftenest && ligma.first != ' ' && ligma.first != '\n')
            {
                oftenest = ligma.second.first;
                oftestchar = ligma.first;
            }
            if (ligma.second.first < rarestest && ligma.first != ' ' && ligma.first != '\n')
            {
                rarestest = ligma.second.first;
                rarestchar = ligma.first;
            }
        }
        cout << "\nЧаще всего(" << oftenest << " раз) встречается символ '" << oftestchar << "';\n\nРеже всего(" << rarestest << " раз) встречается символ '" << rarestchar << "';\n";
        cout << "\nСамое длинное(" << maxlen;
        if (maxlen % 10 == 1)
        {
            cout << " символ";
        }
        else if (maxlen % 10 > 1 && maxlen % 10 < 5)
        {
            cout << " символа";
        }
        else
        {
            cout << " символов";
        }
        cout << ") слово: '" << wlongest << "'; \n\nСамое короткое(" << minlen;
        if (minlen % 10 == 1)
        {
            cout << " символ";
        }
        else if (minlen % 10 > 1 && minlen % 10 < 5)
        {
            cout << " символа";
        }
        else
        {
            cout << " символов";
        }
        cout << ") слово: '" << wshortest << "'\n";
        char c;
        cout << "\nВведи строку, а я скажу тебе, сколько раз встречались в тексте её символы: ";
        getline(wcin, amogus);
        for (int i(0); i < amogus.size(); ++i)
        {
            char c(amogus[i]);
            if (stats.count(c) == 1 && c != '\n')
            {
                cout << "\nСимвол '" << c << "' встречается " << stats[c].first;
                if (stats[c].first % 10 > 1 && stats[c].first % 10 < 5)
                {
                    cout << " раза с частотой " << stats[c].second << endl;
                }
                else
                {
                    cout << " раз с частотой " << stats[c].second << endl;
                }
            }
            else
            {
                cout << "\nСимвол '" << c << "' не встречался...\n";
            }
        }
        el.close();
        cout << "\nЕщё буш? [y]: ";
        getline(wcin, amogus);
        remove(f.c_str());
        if (amogus != L"y")
        {
            break;
        }
    }
}
//ДЗ 5 НОМЕР 4▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H5N4() //тут номер 32 из задания 5.4, в задании выше ещё выполнено задание 36 отсюда же
{
    cout << "Ок, сча тебе удалю из любого числа все '5' и '0'.\n";
    while (true)
    {
        cout << "\nВведи число или 0 чтоб закончить:";
        getline(wcin, amogus);
        if (amogus == L"0")
        {
            break;
        }
        cout << "\nЧисло без '5' и '0': " << nofnoz(string(amogus.begin(), amogus.end())) << endl;
    }
}
//ДЗ 5 НОМЕР 5▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void H5N5() //тут задания 15 и 16 из 5.5
{
    while (true)
    {
        system("CLS");
        int izi;
        cout << "Тебе перевести файл с десятичными числами в другую СС[1] или файл с шестнадцатеричной в любую другую СС[2]? Или выйти[3]?: ";
        while (true)
        {
            getline(wcin, amogus);
            izi = (wcstol(amogus.c_str(), NULL, 10));
            if (izi == 1 || izi == 2 || izi == 3)
            {
                break;
            }
        }
        switch (izi)
        {
        case(1):
        {
            string fn1("decimals.txt"), fn2("conversenoads.txt"), numbah; long long howmany(0), towhat(0); long double from(0), to(0);
            fstream decs;
            decs.open(fn1, ios_base::out);
            cout << "\nОк, сколько десятичных чисел записать в файл? [>0]: ";
            while (true)
            {
                getline(wcin, amogus);
                howmany = wcstoll(amogus.c_str(), NULL, 10);
                if (howmany > 0)
                {
                    break;
                }
            }
            cout << "\nОк, а диапазон для генерации какой? \n\nВведи минимум: для генерации: ";
            getline(wcin, amogus);
            from = wcstold(amogus.c_str(), NULL);
            cout << "\nОк, теперь максимум [обязательно больше минимума]: ";
            while (true)
            {
                getline(wcin, amogus);
                to = wcstold(amogus.c_str(), NULL);
                if (to > from)
                {
                    break;
                }
            }
            for (size_t kek(0); kek < howmany; ++kek)
            {
                stringstream num;
                num << setprecision(50) << nrg(from, to);
                decs << num.str() << endl;
                cout << num.str() << endl;
            }
            decs.close();
            cout << "\nОк, в какую СС переводим все числа в файле и пишем во второй файл? [2<=n<=36]: ";
            while (true)
            {
                getline(wcin, amogus);
                towhat = wcstoll(amogus.c_str(), NULL, 10);
                if (towhat >= 2 && towhat <= 36)
                {
                    break;
                }
            }
            fstream ffromr, fto;
            ffromr.open(fn1, ios_base::in);
            fto.open(fn2, ios_base::out);
            while (ffromr >> numbah)
            {
                fto << basetobase(numbah, 10, towhat) << endl;
                cout << basetobase(numbah, 10, towhat) << endl;
            }
            fto.close();
            ffromr.close();
            cout << "\nУдаляем файлы? [выбора нет]: ";
            getline(wcin, amogus);
            remove(fn1.c_str());
            remove(fn2.c_str());
            break;
        }
        case (2):
        {
            string fn1("first.txt"), fn2("second.txt"), numbah; long long howmany(0), towhat(0), from(0), to(0);
            fstream decs;
            decs.open(fn1, ios_base::out);
            cout << "\nОк, сколько чисел в 16-СС записать в файл? [>0]: ";
            while (true)
            {
                getline(wcin, amogus);
                howmany = wcstoll(amogus.c_str(), NULL, 10);
                if (howmany > 0)
                {
                    break;
                }
            }
            cout << "\nОк, а диапазон для генерации какой? \n\nВведи минимум: для генерации(в 10-СС)[-9223372036854775807<=n<=9223372036854775806]: ";
            while (true)
            {
                getline(wcin, amogus);
                from = wcstoll(amogus.c_str(), NULL, 10);
                if (from < 9223372036854775807)
                {
                    break;
                }
            }
            cout << "\nОк, теперь максимум [обязательно больше минимума]: ";
            while (true)
            {
                getline(wcin, amogus);
                to = wcstoll(amogus.c_str(), NULL, 10);
                if (to > from)
                {
                    break;
                }
            }
            for (size_t kek(0); kek < howmany; ++kek)
            {
                stringstream num;
                num << setprecision(50) << inrg(from, to);
                decs << basetobase(num.str(), 10, 16) << endl;
                cout << basetobase(num.str(), 10, 16) << endl;
            }
            decs.close();
            cout << "\nОк, в какую СС переводим все числа в файле и пишем во второй файл? [2<=n<=36]: ";
            while (true)
            {
                getline(wcin, amogus);
                towhat = wcstoll(amogus.c_str(), NULL, 10);
                if (towhat >= 2 && towhat <= 36)
                {
                    break;
                }
            }
            fstream ffromr, fto;
            ffromr.open(fn1, ios_base::in);
            fto.open(fn2, ios_base::out);
            while (ffromr >> numbah)
            {
                fto << basetobase(numbah, 16, towhat) << endl;
                cout << basetobase(numbah, 16, towhat) << endl;
            }
            fto.close();
            ffromr.close();
            cout << "\nУдаляем файлы? [выбора нет]: ";
            getline(wcin, amogus);
            remove(fn1.c_str());
            remove(fn2.c_str());
            break;
        }
        case (3):
        {
            return;
        }
        }
    }
}
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼да▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
void trololo()
{

    cout << R"(' .-''``  . ``. .-   . -``-  '.-  ```-  ` `'  . '-`' .' ''- '..----  `-  ` '-   --.` . -' .. .. . .`.`'  `'  ' '. -' '---`'  . -`-.`'' . . . . - `.  ' -   '  ` -``-' -` '--`
  -` ` -`.`.-.-..  ' -  . -.      `'`   .'.`'.`' '``---.' - -'` `' '`.` ''  '  `---`' ` ..   .. - - --''  '  '  '`. `'. ``-- `-  .-`-  `  `.. '.    -' .' `-`- . `.-`'    ``'
`'- -'-   `. `' -''--...  -`..'`.  ` .'''- :~<=?\\\vivvvviiiviiviivviviviiiivivvvivi(?\((?|;r+>^^!^^^~:'`''`--.`.--.  .`.' . -    -   ''''' - '- -  ''.' '.'  `   .'   ..  .-
``'.-`` ' ``.`  ''`'..-`  '  .` ---.` ~v2h&BWQgWBHBgWQHWQgQQRBQRWQBBNO%ZuytftfFyzsyzfsstyfCIX56MN&&DBR&&OqdKd0wXa2otY[i?+:''.--   -.    --`-'.- '.- - -   .`' -' '` ---.` '. 
.-.` `.`- .- ``'` .-.  .  .  -'`-. ~v5NQHBgHgBBWRRWRQgQWgQWBB&dIsc{Ty2ZdmDRgHBBBgHQQBRgR@DOKpw53ojjFsfzf1]}Y1yzszszyFFuuJCT=^!^:^!_!`-.-'' -.--'`-.  -``....''`    -..`  ` . 
`'``   `.  '`.  .  .---``  `'.--.^sOWWgRgHBQgRBWRQgRHBgB@UF}i[zXUHRgHHWHHWRQWQWQWgD&D@RQBBBHRRRWHBWQBHQBgHHHgHBRB&@NDDggRWQHWRBQHQR&MU8au7;!'`' `. ` '.-- .. --`. ''..'`` ' '
.-  .`` ..'.   '  .'`  `.-'  .-:y@QQWBQQRgBgWWggQggH@hfv(1kOBgWHR&NM$aVfyyTYtstztftfszffs1c1yzI35bM@&NBHBgHWQBHgWQQBWWRWg@&NMOO8PZ44VVVa%&R&EJv,   .'-.`.`'.'`'.'   `''.' '' 
'`-''. -. - --'-  ..- . ''-.`.}MRBBQBQgQRBBWQWBHQOncvzk&HRWWOXs1]YzVXpMM@QHBHWBQRWBBgBHHBHHgg&OUwaannCyzyJuJouoJooyyfsyfszto2Fe#XAqUmG0Pji{OBgHNKF\_'-` .'``  -'  -- `'  -`  
'``-` `.`. ''' '. - - `.' ` <XBBWHRHHBBRRHBQRBdf7TZ&BRWNws][zZMNRRBg&MMMdKSA%$ZXk$5ZhEdO@RBgWWBBggWHQQBBWRHgQgBHWQQQWBWRQWQRHRWgWWHWgRRRgHWHHQRWRHWNZL! -``.. .- . `   ' '`-'
-.-'`''. ' -. '`.-'   `-.` /MHBgBWWRBRRHRRW%s1CORHRgwzv7IK@RDG#yT]TzsCa#akhPKq0K00S%kYXd&BHWWBRHggRWHWBggBBRWgBQWggBW@NOMOp$33Ia4V6OgRQQWWBWHBRRHWWgBR&kv_.- -'`..-.    .- ``
 `-'`'`.  .``. --...-` `-'vNRWBQWBgBHHQWKsY#NRRBHhTvyUHBOa1iTzkONQRBBWgBRgQRBWBWWWWgR3rj&HRHWHHRRHWQRQgRHgBgRWMuT1Y1ffyne#k$PmKqG6ezL}uUHgWWgBggWQQQRBBBWMl .- ` `-.'''`  .. 
 `- `- ` ```. -.'..' -.'-TRgWBRWQgWWBD#TeMgQWROyvzbRH0yvcaOWgBgWgQgWHHWRHBHBHHWBQQgHRHO/x@RQQQWQBQgRRQBBWWBRgB&M&ggBHHRgBBHRBQggWQBBBNkY|1bgWgHBQBBgBRRgHHWe`.`-'- `` .     -
``- ' `  `-- '  '    --`yRWHBBWRWHRQRMNgRRBWU[/e@QD3|[Z&HRHBBgHRBRQgQBgBRgBggQHWWHBHHRQ@rZBRgBgRQgWHRQHRBgHHHHRBWd[MHgRQQQWHWBWWRBHgRHWHR$(cOggWHWRBQQQQgBRBL' `  '--' `-''`-
' ..'  - .`'     '`' .'zRgHggHHBRHgWQBRRgHOYv9BBDC/fMHBBgRHQHRHHRWHgQgWBQQRgRRWgRQHBHHWg$tRWBQRWQHWQgWRWBHWQgRQBO<uWgggWgQQBHBWBWWQQQgHHgRHYr&gRRRWgBgBHRHQgo '- ''-`` ` - -.
-  ` ``. -`.. -  '.-- tWQWBgRBRgBgRBBQQWgghMBHR5i#NHQWBRgWWQBWO8%5eoJu2CFoVZUORWHHWQgBWWWGHBQQBgWHHggRHBHHWBQRBQe]gWgQQBHRRRQWHHQRWgRBgWQRgg18HBQRggHBWQgQBBM~- --`'..' . .`.
 .''.- .'   '.  . `- CWRWRHRBWQgHQWWRHHQHRBRHHR@HgWBQgBMetv"~:-.-' '. ''' `.` ,;{jGQHHBBHBBWHHRQgRHWgRWBQWBRQQWHndWgBgRQgHHHRWWWHQBQRgQRQHWRggRgHRRBWQQWgRRQHi-   ..-' .-   `
 '.' ' . `` .  . - !$QgHBWgHQgQRBHQBgBRWWRRgQQRRRRWBE1+.  `' .`. `-`'` .`"[i=:- `' +{k@QHRBQQBgRgBRgHHQQQRRWgRBgqOBHBQBHRWDMdAhwwAAA6qMWBHRHggRQQRgBHRBgQBRWWDr.-`'.`.- . '. 
'.. -'-.' `  -'---iMgWRBgWBRRRRBWQRHRWBBHgWQgWWQW@a; -' .`-.-. `  `. .  'ABHHgOZT;'`` :(5@RgggQWRgBHRQgRWWWWgWRWRQBBRwfv*..  -`    -. '~(2OHHRBgWHBRHRBQWWgQWB@c' --`- `  . .
. `-` ' `  `    '!1tysFkhMQWBHgQHHWgBBQW&0SP6&QQd=` -\aw3" -  `-    ``-`+b&QBgBRgH&3i!'-.^t&BRHWgWRRgHRRQWBBRWQBW&Iv~'- ' '. -  +;+:.` ` `_T@gBBBBQHgHBHBBQHBHgBw)' ` --'-  `
 .  ` - ' - '!vYvT]1zfytoe$6dDRgHHBWRNy:-?3OHWQDr` ._=>-.- -' . '..` '. `  `riF6NWQgQ&z^  -"ORgRgBQWBQRHRHQBH&p3c~. ` .-. -`..- ' -- '`. . <bgdx\ivvxYYtzzzztaqHWR0[. '-`.`- 
 -'``'   .`?5uczehKO@QWBRBWBQWWgQRWWHRBgMqwOEwWg8L_^:_:^=iLyt2Ce3#4J2tlv=_`-`.. !/T38Me+ --<OQWRRBQBHBHQ5(r>^.--. '-..-` ' .-' _,::;/vi1fjP&gHQBRgWQRgBRggQg@UY"u&gBMT `- `-'
- - '  ' \%2;aHHgHgHH&EsYi=**r;;(v1fa9&HQHRhnORHQgHBDgHRWQHWQQBgE7rvdgWHBW&6n};^`. `..'--:vKQHQRBHBgBgQW&I/,`''  ''.'~"iTnnZmKM&BQQWWBgRggRBRQBgHHRRRHQWHQW@DHg&f=lSNHO(-'  .
  '--  <XM({@gBQBQQZi:`.` -' _~^  - .',|Y5OQWWBRBHBWBgQHBBRgHO#\`-.*GRWBgWQQgRgNPs?^ ..*COBgBBQQgWWBBBRRgQBDwv-' `<uGDHggBQHHgQRBBWHHRgggBWBQQHgWHBHgHWHRQg5T)}CMRmz*TDRv `--
-'. ' [@O+nHRgQHRZ=' `!iz40mOD&&Md#c+ .   '<\1IA@&QRgQRRDq4Y=: . +oNHgWHgRQWQgHWgHB&8eqWgQQBRHQgHQHBQQHWRBHBHW\ .-AWWQHQWRgQRBgBBRBHWQRRBRgRRBBOZJ1YT1TfF4%DgB0z~aWQDli&0`' .
'` `,XBH1}RWWBQD[..`,sNQgWQQgB&eSHQWQMXy|<-` '.' ,*ri/;<:.-   !l$DRWQRWWgBgQWgRBgWRgQgQQRHBBWRQRBQgRRHWgBWBRRWT .'XRBHWWHggWBBBgHQBHgHBBQHRBP1>-`-  -   ``.-)ZHR9<DgBHc}g_- `
.-'!9gWRc5BHHBN/ ''?MRRBBgHHRN;- oQWHWBHBgOP#Y})<+__ ''_~>*LCh&BHQWWHWBWWRHRWQWHQQQQRHgRBWBHQHHBWQQRRRRBQRgRgHJ --igQBWQBQRWHHRWHw><;cVqOXT>''' "s#ZE6531/^'-`3RB)eHgH@^@?.' 
'  4QgQQ?MBWHgY  .iDgRBHHBBBBT... \#&gHQWWRgWWRHRQN&MOMN@QWWWRgRBBgHHHWWgBgQBWBggHRBWRHQBHBRgBHgHQHHQggWBWgQRBb:``-v%HRQgHHWRgQHBOv '''. -''`-.yHBWRBRgRgQNKaXDQg2TBggg*OL-`.
.. WHHgH)OBQRO'`.?NRQgQWBWHNy``''-`.~vCUDRWQgQRWBQWBgHBWQWBQWQQQHBHRWHBBHBgBNNBWRRQWD@D&WQHBQHRgRQgQgRHBWBRWWWHb?`  .>YP@BggggBHWWHm37v=<>>++)ZgQQ5izRHRRQBgQgHWWwiHRQg-D)` .
  `WRgRBvKHgBX '.VBHHQWDKV{<  ''+":'` ''<i2UNBBBQQHWQHHWBWRHggQBQBgHggRHgBHQ3vBR6cr+~,,^>c&RRHWBRBgBgBgQBBgBgBRBRqY=!-'-<1PBBgWRWWBHHBgRQgWQgRHRBN!  ZQggWBWQBWWBfiHgW#*R~`'`
   UQBHQ]eRRQA'..zRH%1|:` -` - ,@B@O4Y=   .._\1$ORHgRQQHRQBRBBgO09ZXZ4VuJJyYi4N]''. ~;\vY$gWRBHRHRHBWgQHBHgQQgRRHHRW&Y```- "oNRBWWQBgBWHBHHQgWQRHZ'`-=@WggHgHWQ6()OHBN>j4.- `
-- cHBHQsyBQR@!.'~MW3x(r=;;^. `.jBHgWHBOZT*'` '..>vsXORWBgBQgQ0oaX5Z5EGOM&@BQgU`'`=8DBQQBBRgRRQWBWRWgQHgBWHRgQBHgHHBgD<`- - ',YORgRBgQQWQgBRgBHWgv. '`<5BggQBOciABHQQL+0^' `.
  `.XHRB8+QRBWj ` vgRBHRRgg&y  -,hWBBggBWHW&Z}>` -`  '~)T#wNQQBRWHBQQgWBQBWRWRS` `vHRWgqi?++!+<*?7o0gBHHQgRgHRWgWgBRDv --. '  >>i48@BgWggHWgWWWgP!'   `,0gBggW&QRgOu\xh>-  `'
-` -_%RHgrjQHQRx  -ZHWgRRHgQgi  `!t@BQRQHgWHHHD$>' ..`  ..-_>iYahOHgWQBHgRgWWgO<  .i8BQY`   ,!!,_~+?OBQgRggQRRRRWgBX+.. ^Lyii9BB&S2}/{4NWWgQWQgh+''`.-'`lRHQRHMI[?La@m> .'.- 
. `  _kHWO*f&RgBu!'IHQBRWgQQBx--.--:T5DWHQggHQBQ8.` <Z2Y?*' `.-'. ,"}f58@RQggHWw)  .;&H&ffq@&WWWWQgBgRWWgBO@HBBHDVr'`->JDHHBQBWRBQRWRMItOWWBQ9v. ` ~" '-'&BDF1zZMWggq<`'.... 
.` '  'TDWRu=]kDQRgRRggQRQgBRMi''- -' ^|yh&QRQWWO  -?@BQgHWUXf}(+.- .-'`-<i1oZ0RBMo1SBWHQHQRBRQQHBQBgHRWH}.-?Tfi: .`<4@gHRgQHgBQHBBBBQWQWD61< -  . `1<'  XHRgQBgBgWU< .`. '``
`-''`  `<3gHQquvizKBQQQHgWHggHR5< -. .'.`':(s6@RO:`  v&QQHHBRWgWQN9ezvr,-` -` `'>?TsXS@gQHgHWBBWBBHHQQQWW$) `- . .|#NBQHHQBRRQWHHQWRQ&wy|^`'`` +Y  ''.  -1QHBHWWWRN*.--'--  -
  - `. ..-<Y$HgWW@E0gRgWHQWHBgHBNl'-- >/^'' .  =(- -`'<aWWRWRHQBHWHgHBgQO$v .-.`   .. '_*|lT2$6U&HQRRQQWRRBN8wXk9MWRBgBWHHgQggQNE31i>'.`' '``'`iRn'`.`. '[gHgQQQHR1---.'-.- '
   '.-'' - ''-?Y6QWWBBBQHgQHBWHQgHZ~'-.T@O#Y; ` ...`'  .=oOWHHBBRQBHgRHgWWa--`>C2t]v\<~-  -`- '--'^+;()vYTtzsoFVVVa#aVofz11v/;`- .' .  <[39u.- \&gv'.' `'|HHWgBHHQ_   `..'`` 
--'. .' '-'`. (8OQQWRQHgRQgWQQWWRHQO( ..*qWgWDVi`'  ` ```` ;/]zZq@WRgRHHRD)-- eWgQWggWBMU%es}i+'`.'   .`'. '... .  '-.- `-'..-` `.```;dWRHWR^` :@gM,- `' <@HRBBBBM..`- - '   
' .. '-''`--'- `TNRWHgHWWgRRWBgHgRBRWt``'^zHBQBRA_-'' '. `-  .   _/T3m@BRk`- "NBWgQHBHQWHgRQWgH8r '`+$S%54nFfTx)_ .''+i1yCVwdKMMS\. ./NBBRgg:' 'KHg? ` ` +NWBRHWBm. ` -' ' '.
''- .''''- `.`` .<%gWRgQQBBgHWQWQRHQQBK; '-=9RHRg1`.-*uY/, '-`` ..     ;v~.`-FQgRQBWHBHRBQgQgRRHI-. ]RWRQgRHBWgBt'  vWgHgRBWRHHHHM>-.-dggWB9,--.;T<  ``  >@HQHgHRP ` . ` ---.
' --`'-  ``'-  --`~VHBWBgHRQRBQQQQHgWWR&C~'` 1MWRz-` ngBg&po{+,`'-`. '.      '*1j5O&&WWQBBgBBWRR$ -`iHQBBggBgQgQ8:--/DWRBHBggHQgHQY `.T&DO#+` -'`- .. .' *NWRWQBQw `  `` -`- 
 -.-`.. . .  .-  .`.ogRWQRBRgRRQRWQWggHWQMv `.:To>- _8ggWWgQQH@wnL=_ `. '.  `''  `  ,*?LTyC4VVe3?`  ~lnea34aa4Vox:   ljuFunyfYxv=+'  --+--` .   ``'`'-`. vRBQBBQHw.  ''-  `-`
```'  ..- ` ` '`.- . sQgWWHggWBgHgWQBHRQHBH5*'-' '`>$QBBWBHQWHQBRQHDOZ7'-''``  ' ..`' `. `.-. .  ...-`` .'``.` '`'' '-''`  `'-'``.-     - .   -   ' - '  TRBHBWRBh `- -  . . 
` `-'. `-.' '- -  -  `TQHRRBRHgBRgRHRQHgQHWRH5; .  *KHWRBHBRHBWgHRQWRRQv' `TVy{r!-.'-`.'-``  ..' ` -'-...   ``------ ...'--  -  ..--.-`` - .-.'--`-`  '` YHBgQWgHE.'`.'.. -`-
.``.  ---`. . -' -`''- lNBRggBRQHBRgBHgRQQQWRggh7,   ?COgQRWWQRWWRgRQHO<`` SQHWg@OXzc;+-...- .' ..-''.'` `' .'.  - ..-'. ... `  '.  ' -- - - ``.` - '-'.-hRgRBgWHw- ---.``'.`
  ' ``-...`' ..'- `.. ' "%WQBWgRWHBQgHBQRggHgRBQROfr.' ,?4OBgRQRRQQRBg7 -'r@QQHBHRHHgW&MSeti~-.'..'``-.. -  ' '....`--'-`.   ' '-'`  - . ''` ` -.' <T.  >DBRgQBWgw- -``.``- '
 ' -  `.'''- '. '.'`.---' 7OHRBBRQBWQWgHQBWHBHBQQggQhc! .'_)VOHBQBHRHu-`-+qgHgBHHRRRHHWRRRgBO>'` YeyYi)'=>:: -``..' `.`.''' ''  `    . . -  i1-   "%<'`'XHQQWBQHWw' --   ` - 
'..-`. ` `'' ` --.-' `'``  ,fDgBWHWRWQQgHRBgQBBQQgBHRWD4)!'  ,(FMgHHj .'~9QRgHHBWWHRBgWHQWgWW".'<OgHggggRRDN@Oa:-.`~\1TTT1x?'.'`.iu$kMi '.+Pg1' `+G;'''YQRBRRRQgQ6-   ` `'  `
   -.'-.`'`` ... `.'  '-.  ''!TOBgBWWRRgQQgRgBRHHBHBWggQWN#\.'-' =v\--'~XgBRBWRgBWgRQRQQQQWHN". ?&BgHHQHBRgBRQp_ ` $BQHHBWBO>-  3BHgB1--.+URW+.- I\'.`YRWgWgHWHWQ9-' -.. .  `
--  ` ..  .`.`'`   `.   -  '. ._i6RQRDa%@HQWHHQpZ$MgBgHRWHQRD#i~-'.  ''^tqBWgBBBWWBBBHRgBgHgM<'-?RBWRRBgggWRQgn  `vQWHgWHg&|` `YWBWWt .`+dQHBXz+`'-':2WgWRRWQBQBR0-`    .--- 
.'.- .- . . '''`-.'.  `-.-  .. `  "a&WB%s7Y$DggRQM3YYCUgBBBHBHRBbov>-'`.``,*iz#hOQRgRQgRHHRQd:  \BQWBggBWRRQWD;.''pWRWRBW@i'` r@HBHA, .-6O9ez/!`' `]MRHQWggHBgWQgO -`   .''-`
..`. `-' `-. `.''`- -'- -  ` `-'`  `~l$QHHMV[v1ZNWWRHKjLvzANBWgRgQWWMkF}?,' ' '`- ")v1sak%9%l   =MgRBWWQHBgBBI.'';&HQgBHK".``.Jp9Zj| .- .'  `  ^v2OHggQRQBRBWWgBRN-`-'`'-'`'`
-  '`'''.`-.`` --`.`-`-'    `. '  ' `'-^{$DggWqoivtw@BBBWpa{vYZMHgggBQQRQgMA#s]?>` '- -'.   --`.-!?)?ii7l7v);- ' -(iv/?+''' ' `'`.     '`_"vyemRBRWHBQHWQRgHHRWWHQ-- ' ' -.' 
   ...` .  .-.  `-- ''- .`  .-    --`' '..-?zdWHBHKI]vY$&gQgWMkYvlf6&QRQBHBgRRQQgB&d6Zasz7v//(=>_`'`'.. ..''' - '    .'- . ^;?(/vTsoaEhOHgBRBBHHRgQWHWHggRBHBBBRHW^'.--`'.'- 
 . '''. --.--  -   -` -.  ''-. '..'`-.`.'. '`-<c#OQBWHM3TxT4bNRHHWdF{c7jGDHgQHWRHRgRRWRQWWgHWBQgHWWQgB@@NOOOOOMOMMON&@HQBWgRQggBgWRRHRHHQQBQgBRBR6wHgRgQHBRRWgHBHQ+'. '`     
`` --`.-.` '-`-  - -.' .-- ''     -'-''- -'' -.-'-*YZ&ggWH@Sf7[tXMQgHQ&9JcxlnSNRQWWHRWWBWQgHgRQHHWHgRWRRBggHBBHQBgRRgBgQgRgQgBRgBQHQgHgRBWBQgWOz;uQgRWQQQBOBWBQRBBv. '-  -'. 
 --`'`''-` ..  -'  . '``-.`'`-``'`'`.`'  .   `-'- .' .;1VMDBgRgOXfTYzam&WHQNdVYYly#A&BHBHWgQWQHWRgWgBQgNDOMOOGdbGMOMMD&QQBHWgWWWWWWBHWHRRQWOei)F&WBBgQWHgQlWBHgRQBy -  - -`'.
.` -  `'`''-' ' - .` `.`'.`.` .... .' `''.  `. '.` -```'` _/zZMBRRRQ&q3zyYyVXMD@gMPesTxts#ZSbO@N@DNDgRWQgBgWgWBWgQRRRgWBBBBRWBBRWQgRHWD841ic4OWWWRgRRHBRMv7WgHHgBWF .  - -'-'
`-. ' - ` ..-     .. - `. ``' ` ' `- ` .    `. `. '`'..'.`     <L2K@HHQgBW@MEItYYlzyV$dOOKqw42FCust1YyfsY{l[xYTftysY1zfn2ue#eaIaV2ttyyf2PMQWBggHHgHBB&av?uDQWHHQHHU'.  ```   
 ' .'.-' `. '  -'`- `.`-   -. .`-   '.''..-'`'`.`- '``  `.` .''`- .:vzP&BWWgWHgQRWNM0XCz1Yx1fnaZ8MDWHRQHBBQgQRggRD&DDNOOOOMOOOM&DHBQHQQWWWHggBHHRQOJv(fdggQgBBHWgWO'`````-..`
-'    ..'--`   . `-'  ''` ` - `---.'  `` - .'.- `    '  .`` -. '`'''..'!/zE&RRQgWWHHgBQWgRgQNOdX4FyzyftyF3I4XhGOMMDDD&QQgQRWHQgWHRHRHHWBQQRRB&OXT(v4OgQRRWBHHHBgRRn    '  -` 
 ` -'  '.'- ` -'    .. `  .. `- -`    -`' `-...-- -  '- ' '  ' -`.  .' . ..!*TZOgQQQQggHHWQWRgQBRHQRQWQRN@OOUw$$4eV#4IuoosfunonJ43##eVIaaV2jtfz4m&BRRgHQQWHgQHgRQ%_-   --    
. '- ``-   .'-``-` ''' `'-. ` - ..`--.-  .  -. - .'- -` ` - . `- .`  ' .     '  +LoG&WRHQQBWBWWgQBHWQBRQRWHWHRHgHHHBHBRQRRQQgBWQBBHgRWBBQHWBQQggWWggHRBQggBBQQQRV^.-'.  '   `
`'  `  `'``  . .'- ``'-`'`-`'  ''' '. ...-. -.. `` `' -  `''  -`.'-...`- -  ' ' .. -:(TV8DRQHBRQBQgRWHWWgRgRBQBRWBBgRQgQgQRBQgWWBWQHHQQRgBBHRHBWQBBgBHQQBWQWWQKv-    . '-   .
'`  - - '-```-` `'' `'..  -    - '''.`` -''` `` ` '-. .'  '`' -`'- .'.` ` `-`' .-.` -'  .~<"v{yCkKMBQWRWHRBBBHgQBBWRWWRBgQgQHHQQRgHQHBQRgHHRHWRQQWWRHWQgWHBHO7^'`.  .'' '`- -
.- ' -```  `'.' `-` .`'`` .-.'-      - ` '.- -.``-   --'' .- `--.  `   '  ` - ''` -- '-.''' --  ''-!=vlFVUMBHgWHQBgBRggRgRWWWHRQgQgHRHHQBWBHHBWRHQWBWRHHHMI) '  '.`'` `-'.''-
 `.` -  -''` -`. . - ` .''`   `.` '  ' ' ' .'-' ` - `-'--` `-.'.''-  - ' .``  . '  `.   ''-.-' '``` - -' ``!>\[uIUMgQgggggHgWgHRRQWHgWWBBRHQHRQHBRRHROa{"  `' .-`   -  -  - `
  '. .'  - ' '---  .'--`''  '   ' '. . . - ' -`   `.  `  -. .-- - `'   `  ' .' `'` -``-``- .-- .. . - '-- '--  `..'__|iLTyu#Z$SPPE8bGGb0Gb8qUPSk4t[(!` -.' '`' -`````' ' ''  
''`. '. '``'- - -`-''  .'-- --    -`  '`  `-` ` ` ``'-  `.`-   .'''-' '` '` --'   ' - ` ``   -' -- .   `-. `  `  - -'   - `'-` -   --'-` ``. `-.'. --. trolololololololo  `. 
` `  '.`. ``` -  -`'  `' -.--`'  `-`   .  `` --.- '  -- `-  . '  ' ` .'. -''.  '- '.  -'-. .`.'' '  .  '  '`  `  -  . - '' --`   '--' `-. -. .   .-''-.-'. -- ' -'' .'' ---  )" << endl;
    return;
}
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼MAINкрафт▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
int main()//карта карно ввод 16 перевод в двоичную, карта карно минимизация, самые большие контуры в первую очередь 96 + ДЗ №5 всё + спиннер на лизочке + 94-95
{
    system("chcp 65001");
    system("CLS");
    int HN(0);
    cout << toplc + horw6 + horw + horw80 + toprc + "\n" + vertw + "ДОМАШНЯЯ РАБОТА #1                                                                     " + vertw + "\n" + leftmw + horw6 + topmw + horw80 + rightmw + "\n" + vertw + "  11  " + vertw + "Герман                                                                          " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  12  " + vertw + "Выполнить действия с двумя числами                                              " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  13  " + vertw + "Решить линейное уравнение                                                       " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  14  " + vertw + "Решить квадратичное уравнение                                                   " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  15  " + vertw + "Ответить на вопрос о светлоте комнаты                                           " + vertw << endl;
    cout << leftmw + horw6 + botmw + horw80 + rightmw + "\n" + vertw + "ДОМАШНЯЯ РАБОТА #2                                                                     " + vertw + "\n" + leftmw + horw6 + topmw + horw80 + rightmw + "\n" + vertw + "  21  " + vertw + "Вычислить объём и полную поверхность усеченного конуса                          " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  22  " + vertw + "Решить разветвляющееся уравнение                                                " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  23  " + vertw + "Решить функцию                                                                  " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  24  " + vertw + "Написать 10 возрастающих натуральных чисел с заданного числа                    " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  25  " + vertw + "Протабулировать функцию от - 4 до 4 с шагом в 0.5                               " + vertw << endl;
    cout << leftmw + horw6 + botmw + horw80 + rightmw + "\n" + vertw + "ДОМАШНЯЯ РАБОТА #3                                                                     " + vertw + "\n" + leftmw + horw6 + topmw + horw80 + rightmw + "\n" + vertw + "  31  " + vertw + "Найти ежемесячные выплаты по данным сумме кредита(S), проценту(p), кол-ву лет(n)" + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  32  " + vertw + "Найти процент по данным времени, сумме и размеру выплат   " << red << "(БЕЗ <WINDOWS.H>)" << reset << "     " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  33  " + vertw + "Создать, написать в и прочитать файл                                            " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  34  " + vertw + "Отфильтровать все буквы из файла с буквами и числами                            " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  35  " + vertw + "Отсортировать в алфавитном порядке заданную строку в 30 символов                " + vertw << endl;//                                                                                                                                 "                                                                                                                                                                                "                                                                                                                                                                                "                                                                                                                                                                                "
    cout << leftmw + horw6 + botmw + horw80 + rightmw + "\n" + vertw + "ДОМАШНЯЯ РАБОТА #4                                                                     " + vertw + "\n" + leftmw + horw6 + topmw + horw80 + rightmw + "\n" + vertw + "  41  " + vertw + "Записать в файл 10 чисел, закрыть, открыть, прочитать, посчитать                " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  42  " + vertw + "Воспользовавшись сверхъестественными силами, сказать знак введённого числа      " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  43  " + vertw + "Сказать площадь фигур на выбор(круг, треуг, и прямоуг)                          " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  44  " + vertw + "Нарисовать 'Былую Славу' 1912г.                                                 " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  45  " + vertw + "Нарисовать график функции y = sin x                                             " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  46  " + vertw + "Перевести римское число в человеческое(и наоборот)                              " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  47  " + vertw + "Генератор псевдослучайных чисел                                                 " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  48  " + vertw + "Продавцы товары умножение матриц все дела                                       " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  49  " + vertw + "Перевести число из одной СС в другую                                            " + vertw << endl;
    cout << leftmw + horw6 + botmw + horw80 + rightmw + "\n" + vertw + "ДОМАШНЯЯ РАБОТА #5                                                                     " + vertw + "\n" + leftmw + horw6 + topmw + horw80 + rightmw + "\n" + vertw + "  51  " + vertw + "Найти НОД улиточным(вычитание) и быстрым(деление) способами                     " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  52  " + vertw + "Наколдовать все простые числа от 2 до заданного числа                           " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  53  " + vertw + "Хорошенько поработать с файлом                                                  " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  54  " + vertw + "Ряды                                                                            " + vertw + "\n" + leftmw + horw6 + midw + horw80 + rightmw + "\n" + vertw + "  55  " + vertw + "Файлы                                                                           " + vertw << endl;//                                                                                                                                                             "                                                                                                                                                                                "                                                                                                                                                                                "                                                                                                                                                                                "
    cout << botlc + horw6 + botmw + horw80 + botrc << endl;
    cout << "\n1 цифра - номер ДЗ, 2 цифра - номер задания в ДЗ.\n" << "\nНечисловые вводы приравниваются 0\n\n" << green << inthextobin("fac") << " " << yellow << 7 / 2 << reset << " " << red << (sqrt(32) == floor(sqrt(32))) << reset << "\n\nНомер задачи : ";
    getline(wcin, amogus);
    cout << fixed;
    HN = wcstod(amogus.c_str(), NULL);
    switch (HN)
    {
    case (-1):
    {
        return(0);
    }
    case (1):
    {
        kektask();
        break;
    }
    case (11):
    {
        H1N1();
        break;
    }
    case (12):
    {
        H1N2();
        break;
    }
    case (13):
    {
        H1N3();
        break;
    }
    case (14):
    {
        H1N4();
        break;
    }
    case (15):
    {
        H1N5();
        break;
    }
    case (21):
    {
        H2N1();
        break;
    }
    case (22):
    {
        H2N2();
        break;
    }
    case (23):
    {
        H2N3();
        break;
    }
    case (24):
    {
        H2N4();
        break;
    }
    case (25):
    {
        H2N5();
        break;
    }
    case (31):
    {
        H3N1();
        break;
    }
    case (32):
    {
#ifdef _WINDOWS_
        system("CLS");
        cout << red << "У этой задачи аллергия на заголовок <windows.h>, поэтому для её работы заголовок надо закомментировать." << reset << endl;;
        break;
#else
        H3N2();
        break;
#endif
    }
    case (33):
    {
        H3N3();
        break;
    }
    case (34):
    {
        H3N4();
        break;
    }
    case (35):
    {
        H3N5();
        break;
    }
    case (41):
    {
        H4N1();
        break;
    }
    case (42):
    {
        H4N2();
        break;
    }
    case (43):
    {
        H4N3();
        break;
    }
    case (44):
    {
        H4N4();
        break;
    }
    case (45):
    {
        H4N5();
        break;
    }
    case (46):
    {
        H4N6();
        break;
    }
    case (47):
    {
        H4N7();
        break;
    }
    case (48):
    {
        H4N8();
        break;
    }
    case (49):
    {
        H4N9();
        break;
    }
    case (51):
    {
        H5N1();
        break;
    }
    case (52):
    {
        H5N2();
        break;
    }
    case (53):
    {
        H5N3();
        break;
    }
    case (54):
    {
        H5N4();
        break;
    }
    case (55):
    {
        H5N5();
        break;
    }
    case (94):
    {
        nuts();
        break;
    }
    case (95):
    {
        bydlo();
        break;
    }
    default:
    {
        trololo();
        break;
    }
    }
    cout << "\nЗакрываемся? [y]: ";
    getline(wcin, amogus);
    if (amogus == L"y")
    {
        return(0);
    }
    main();
}
