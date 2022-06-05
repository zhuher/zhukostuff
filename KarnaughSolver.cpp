#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
const string black("\033[0;30m"), red("\033[0;31m"), green("\033[0;32m"), reset("\033[0m"), horw(u8"═"), horw5(u8"═════"), horw3(u8"═══"), vertw(u8"║"), toprc(u8"╗"), toplc(u8"╔"), botrc(u8"╝"), botlc(u8"╚"), topmw(u8"╦"), botmw(u8"╩"), leftmw(u8"╠"), rightmw(u8"╣"), midw(u8"╬"), yellow("\x1b[0;33m"), blue("\x1b[0;34m"), magenta("\x1b[0;35m"), cyan("\x1b[0;36m"), white("\x1b[0;37m"), bblack("\x1b[0;90m"), bred("\x1b[0;91m"), bgreen("\x1b[0;92m"), byellow("\x1b[0;93m"), bblue("\x1b[0;94m"), bmagenta("\x1b[0;95m"), bcyan("\x1b[0;96m"), bwhite("\x1b[0;97m");
wstring input(L"");
//Числовое значение символа (0...Z) в тридцатишестеричной системе счисления
long long powa(int base, int exponent)
{
	long long res(1);
	while (exponent)
	{
		int lbit(exponent & 1);
		if (lbit) { res *= base; }
		base *= base;
		exponent >>= 1;
	}
	return res;
}
int count(vector<int>& v, int n)
{
	int res(0); for (int i : v) { if (i == n) { ++res; } } return res;
}
int based(char numlet)
{
	if (numlet >= '0' && numlet <= '9') { return (numlet - '0'); }
	else if (numlet >= 'a' && numlet <= 'z') { return (numlet - 'a' + 10); }
	else if (numlet >= 'A' && numlet <= 'Z') { return (numlet - 'A' + 10); }
	else { return -1; }
}
//Переводчик целых чисел из десятичной в двоичную заданной битности
string intdectobin(int decnum, int bits)
{
	string binum("");
	for (int b(0); b < bits; ++b) { binum = to_string(decnum % 2) + binum; decnum /= 2; }
	return binum;
}
//Переводчик целых чисел из двоичной в десятичную
int intbintodec(string binum)
{
	int decnum(0);
	for (int n(0); n < binum.size(); ++n) { decnum += based(binum[n]) * powa(2, (binum.size() - n - 1)); }
	return decnum;
}
//Переводчик целых чисел из шестнадцатеричной в десятичную
string inthextobin(string num)
{
	string temp(num); num.clear();
	for (char c : temp)
	{
		switch (c)
		{
		case('0'): { num += "0000"; break; }
		case('1'): { num += "0001"; break; }
		case('2'): { num += "0010"; break; }
		case('3'): { num += "0011"; break; }
		case('4'): { num += "0100"; break; }
		case('5'): { num += "0101"; break; }
		case('6'): { num += "0110"; break; }
		case('7'): { num += "0111"; break; }
		case('8'): { num += "1000"; break; }
		case('9'): { num += "1001"; break; }
		case('A'):
		case('a'): { num += "1010"; break; }
		case('B'):
		case('b'): { num += "1011"; break; }
		case('C'):
		case('c'): { num += "1100"; break; }
		case('D'):
		case('d'): { num += "1101"; break; }
		case('E'):
		case('e'): { num += "1110"; break; }
		case('F'):
		case('f'): { num += "1111"; }
		}
	}
	return num;
}
//Генератор кода Грея для создания карты
vector<string> greyarr(int bits)
{
	vector<string> greys;
	if (bits <= 0) { return(vector<string>(0, "")); }
	greys.push_back("0");
	greys.push_back("1");
	int n(0), k(0);
	for (n = 2; n < (1 << bits); n = n << 1)
	{
		for (k = n - 1; k >= 0; --k) { greys.push_back(greys[k]); }
		for (k = 0; k < n; ++k) { greys[k] = "0" + greys[k]; }
		for (k = n; k < n * 2; ++k) { greys[k] = "1" + greys[k]; }
	}
	return greys;
}
//Счётчик единиц в двоичной записи числа
int cbits(int n)
{
	int count(0);
	while (n) { n &= (n - 1); ++count; }
	return count;
}
//Конвертер группы чисел в строку для вывода
string grouptoprint(vector<int>& intgroup, int& vars)
{
	string res("");
	for (int n : intgroup)
	{
		string curnum(intdectobin(n, vars));
		if (res.size() == 0) { res = curnum; }
		else
		{
			for (int c(0); c < curnum.size(); ++c) { if (curnum[c] != res[c]) { res[c] = '-'; } }
		}
		//cout << res << " VS " << curnum << endl;
	}
	return res;
}
//Счётчик суммы элементов вектора
int sum(vector<int> vec)
{
	int res(0);
	for (int n : vec) { res += n; }
	return res;
}
int main()
{
	setlocale(LC_ALL, "Russian_Russia.65001");
	//cout << "Салют, сча я тебе нарисую карту Карно.\n";
	while (true)
	{
		printf("Введите количество переменных [от 2 до 21] (минимизация до 4 включительно)\n");
		int vars(0);
		while (true) //допуск только соответствующего условиям ввода кол-ва переменных
		{
			printf("> ");
			getline(wcin, input);
			vars = wcstol(input.c_str(), NULL, 10);
			if (vars > 1 && vars <= 21) { break; }
		}
		printf("\nВведите целое шестнадцатеричное число длиной в %d.\nНедостающие цифры станут ведущими нулями.\n", (int)(powa(2, vars) / 4));
		while (true) //допуск только целочисленного положительного числа в шестнадцатеричной СС
		{
			bool ok(true);
			printf("> ");
			getline(wcin, input);
			for (char c : input) { if (based(c) < 0 || based(c) > 15) { ok = false; break; } }
			if (ok)
			{
				if (input.size() == (powa(2, vars) / 4)) { break; }
				else
				{
					if (input.size() > (powa(2, vars) / 4))
					{
						printf("Ввод должен быть на %d символ", (int)(input.size() - (powa(2, vars) / 4)));
						if ((input.size() - (powa(2, vars) / 4)) % 10 > 4 || (((input.size() - (powa(2, vars) / 4)) % 100 >= 11 && (input.size() - (powa(2, vars) / 4)) % 100 <= 19) || (input.size() - (powa(2, vars) / 4)) % 10 == 0))
						{
							printf("ов короче.\n");
						}
						else if ((input.size() - (powa(2, vars) / 4)) % 10 == 1) { printf(" короче.\n"); }
						else if ((input.size() - (powa(2, vars) / 4)) % 10 >= 2 && (input.size() - (powa(2, vars) / 4)) % 10 <= 4) { printf("a короче.\n"); }
					}
					else if (input.size() < (powa(2, vars) / 4))
					{
						int diff((powa(2, vars) / 4) - input.size());
						for (int add(0); add < diff; ++add) { input = L"0" + input; }
						break;
					}
				}
			}
		}
		//wcout << L"\nHexadecimal number is: " << input << endl;
		string binum(inthextobin(string(input.begin(), input.end())));
		//cout << "\nBinary number is: " << binum << endl;
		vector<int> ones, zeroes; //массивы позиций единиц и нулей
		for (int b = 0; b < powa(2, vars); ++b) { if (binum[b] == '1') { ones.push_back(b); } else { zeroes.push_back(b); } }
		int colvars = vars / 2.0, rowvars = vars / 2.0 == colvars ? colvars : colvars + 1;
		vector<string> greyrows(greyarr(rowvars)), greycols(greyarr(colvars)); //создание массива переменных рядов и столбцов карты
		vector<string> perhaps, certainly; //массив строк для фильтра и вывода результата
		vector<vector<pair<bool, int>>> kmap; //массив истинности и позиций карты
		vector<vector<bool>> truthtable;
		for (string r : greyrows) //заполнение массива позиций и массива истинности через сравнение каждой позиции с позициями единиц
		{
			vector<pair<bool, int>> krow;
			for (string c : greycols)
			{
				int pos(intbintodec(r + c));
				bool one(false);
				for (int o : ones) { if (pos == o) { one = true; break; } }
				pair<bool, int> e; e.first = one; e.second = pos;
				krow.push_back(e);
			}
			kmap.push_back(krow);
		}
		for (int i(0); i < binum.size(); ++i)
		{
			string bingus(intdectobin(i, vars));
			vector<bool> truthrow;
			for (char c : bingus)
			{
				truthrow.push_back(based(c));
			}
			if (binum[i] == '1')
			{
				truthrow.push_back(1);
			}
			else
			{
				truthrow.push_back(0);
			}
			truthtable.push_back(truthrow);
		}
		printf("\n(Лера привет!)Таблица истинности: \n");
		for (int i(0); i < truthtable.size(); ++i)
		{
			if (i == 0)
			{
				for (int k(0); k < truthtable[i].size(); ++k)
				{
					if (k == 0) { printf("%s", toplc); }
					printf("%s", horw3);
					if (k == truthtable[i].size() - 1) { printf("%s\n", toprc); }
					else { printf("%s", topmw); }
				}
				for (int k(0); k < truthtable[i].size(); ++k)
				{
					if (k == 0) { printf("%s", vertw); }
					if (k != truthtable[i].size() - 1)
					{
						printf(" %c ", 65 + k);
					}
					if (k == truthtable[i].size() - 1) { printf(" %s %s\n", u8"ƒ", vertw); }
					else { printf("%s", vertw); }
				}
				for (int k(0); k < truthtable[i].size(); ++k)
				{
					if (k == 0) { printf("%s", leftmw); }
					printf("%s", horw3);
					if (k == truthtable[i].size() - 1) { printf("%s\n", rightmw); }
					else { printf("%s", midw); }
				}
			}
			for (int k(0); k < truthtable[i].size(); ++k)
			{
				if (k == 0) { printf("%s", vertw); }
				if (truthtable[i][k]) { printf(" %s%d%s %s", green, (int)truthtable[i][k], reset, vertw); }
				else { printf(" %s%d%s %s", bred, (int)truthtable[i][k], reset, vertw); }
			}
			printf("\n");
			if (i == truthtable.size() - 1)
			{
				for (int k(0); k < truthtable[i].size(); ++k)
				{
					if (k == 0) { printf("%s", botlc); }
					printf("%s", horw3);
					if (k == truthtable[i].size() - 1) { printf("%s\n", botrc); }
					else { printf("%s", botmw); }
				}
			}
			else
			{
				for (int k(0); k < truthtable[i].size(); ++k)
				{
					if (k == 0) { printf("%s", leftmw); }
					printf("%s", horw3);
					if (k == truthtable[i].size() - 1) { printf("%s\n", rightmw); }
					else { printf("%s", midw); }
				}
			}
		}
		for (int krow(0); krow < kmap.size(); ++krow) //печать карты
		{
			if (krow == 0)
			{
				printf("%s", toplc); for (int build(0); build < rowvars; ++build) { printf("%s", horw); } printf("%s", topmw);
				for (int build(0); build < powa(2, colvars) * colvars + (powa(2, colvars) - 1); ++build) { printf("%s", horw); } printf("%s\n", toprc);
				printf("%s", vertw); for (int build(0); build < rowvars; ++build) { printf(" "); } printf("%s", vertw);
				if (colvars > 1)
				{
					for (int build(0); build < (powa(2, colvars) * colvars + (powa(2, colvars) - 1)) / 2 - colvars / 2; ++build) { printf(" "); } for (int build(0); build < colvars / 2; ++build) { printf("%c", 65 + rowvars + build); }
					printf(" "); for (int build(0); build < colvars / 2; ++build) { printf("%c", 65 + rowvars + colvars / 2 + build); } for (int build(0); build < (powa(2, colvars) * colvars + (powa(2, colvars) - 1)) / 2 - colvars / 2; ++build) { printf(" "); } printf("%s\n", vertw);
				}
				else
				{
					for (int build(0); build < (powa(2, colvars) * colvars + (powa(2, colvars) - 1)) / 2; ++build) { printf(" "); } printf("%c", 65 + rowvars + colvars);
					for (int build(0); build < (powa(2, colvars) * colvars + (powa(2, colvars) - 1)) / 2; ++build) { printf(" "); } printf("%s\n", vertw);
				}
				printf("%s", vertw);
				for (int build(0); build < rowvars; ++build) { printf("%c", 65 + build); }
				printf("%s", leftmw);
				for (int build(0); build < kmap[krow].size(); ++build)
				{
					for (int b(0); b < colvars; ++b) { printf("%s", horw); }
					if (build == kmap[krow].size() - 1) { printf("%s\n", rightmw); }
					else { printf("%s", topmw); }
				}
				printf("%s", vertw);
				for (int build(0); build < rowvars; ++build) { printf(" "); }
				printf("%s", vertw);
				for (int build(0); build < kmap[krow].size(); ++build)
				{
					for (int b(0); b < colvars; ++b)
					{
						/*if (greycols[build][b] == '1') { cout << green  << (char)(65 + rowvars + b) << reset; }
						else { cout << red  << (char)(65 + rowvars + b) << reset; }*/
						printf("%c", greycols[build][b]);
					}
					printf("%s", vertw);
				}
				printf("\n%s", leftmw);
				for (int build(0); build < rowvars; ++build) { printf("%s", horw); }
				printf("%s", midw);
				for (int build(0); build < kmap[krow].size(); ++build)
				{
					for (int b(0); b < colvars; ++b) { printf("%s", horw); }
					if (build == kmap[krow].size() - 1) { printf("%s\n", rightmw); }
					else { printf("%s", midw); }
				}

			}
			else
			{
				printf("%s", leftmw);
				for (int build(0); build < rowvars; ++build) { printf("%s", horw); }
				printf("%s", midw);
				for (int build(0); build < kmap[krow].size(); ++build)
				{
					for (int b(0); b < colvars; ++b) { printf("%s", horw); }
					if (build == kmap[krow].size() - 1) { printf("%s\n", rightmw); }
					else { printf("%s", midw); }
				}
			}
			printf("%s", vertw);
			for (int build(0); build < rowvars; ++build)
			{
				/*if (greyrows[krow][build] == '1') { cout << green  << (char)(65 + build) << reset; }
				else { cout << red  << (char)(65 + build) << reset; }*/
				printf("%c", greyrows[krow][build]);
			}
			printf("%s", vertw);
			for (pair<bool, int> pos : kmap[krow])
			{
				if (pos.first) { printf("%s%*d%s%s", green, colvars, (int)pos.first, reset, vertw); }
				else { printf("%s%*d%s%s", bred, colvars, (int)pos.first, reset, vertw); }
			}
			printf("\n");
		}
		printf("%s", botlc);
		for (int build(0); build < rowvars; ++build) { printf("%s", horw); }
		printf("%s", botmw);
		for (int build(0); build < kmap[0].size(); ++build)
		{
			for (int b(0); b < colvars; ++b) { printf("%s", horw); }
			if (build == kmap[0].size() - 1) { printf("%s\n", botrc); }
			else { printf("%s", botmw); }
		} //конец печати карты
		printf("%s", toplc); //печать позиций карты
		int width((to_string(powa(2, vars))).size());
		for (int build(0); build < kmap[0].size(); ++build)
		{
			for (int b(0); b < width; ++b) { printf("%s", horw); }
			if (build == kmap[0].size() - 1) { printf("%s\n", toprc); }
			else { printf("%s", topmw); }
		}
		for (int r(0); r < kmap.size(); ++r)
		{
			vector<pair<bool, int>> posrow = kmap[r];
			if (r != 0)
			{
				printf("%s", leftmw);
				for (int build(0); build < kmap[0].size(); ++build)
				{
					for (int b(0); b < width; ++b) { printf("%s", horw); }
					if (build == kmap[0].size() - 1) { printf("%s\n", rightmw); }
					else { printf("%s", midw); }
				}
			}
			printf("%s", vertw);
			for (pair<bool, int> posint : posrow) { printf("%*d%s", width, (int)posint.second, vertw); }
			printf("\n");
		}
		printf("%s", botlc);
		for (int build(0); build < kmap[0].size(); ++build)
		{
			for (int b(0); b < width; ++b) { printf("%s", horw); }
			if (build == kmap[0].size() - 1) { printf("%s\n", botrc); }
			else { printf("%s", botmw); }
		} //конец печати позиций карты
		printf("\n");
		vector<pair<vector<int>, vector<int>>> groups, groupstwo;
		for (int v(0); v <= vars; ++v)
		{
			pair<vector<int>, vector<int>> group;
			for (int o : ones) { if (cbits(o) == v) { group.first.push_back(o); } }
			if (group.first.size() != 0) { groupstwo.push_back(group); }
			else { group.first.push_back(-1); groupstwo.push_back(group); }
		}
		if (vars <= 4)
		{
			if (ones.size() == powa(2, vars)) { printf("\nМинимизация: 1\n"); continue; }
			else if (ones.size() == 0) { printf("\nМинимизация: 0\n"); continue; }
			//cout << "\n______________________________\n";
			//for (pair<vector<int>, vector<int>> group : groupstwo)
			//{
			//	for (int m : group.first) { cout << setw(width) << m << setw(0) << " "; }
			//	cout << endl;
			//}
			vector<int> usedints;
			bool found(false);
			for (int i(0); i < groupstwo.size(); ++i)
			{
				bool found(false);
				if (i != groupstwo.size() - 1)
				{
					if (groupstwo[i].first[0] == -1) { continue; }
					else if ((groupstwo[i + 1].first[0] == -1) && (i + 1 != groupstwo.size() - 1))
					{
						for (int check : usedints) { if (groupstwo[i].first[0] == check) { found = true; break; } }
						if (found) { found = false; continue; }
						else
						{
							usedints.push_back(groupstwo[i].first[0]);
							pair<vector<int>, vector<int>> topush;
							topush.first.push_back(groupstwo[i].first[0]);
							groups.push_back(topush);
						}
					}
					for (int k(0); k < groupstwo[i].first.size(); ++k)
					{
						for (int r(0); r < groupstwo[i + 1].first.size(); ++r)
						{
							for (int shift(0); shift <= vars; ++shift)
							{
								if ((groupstwo[i].first[k] ^ groupstwo[i + 1].first[r]) == (1 << shift))
								{
									pair<vector<int>, vector<int>> topush;
									topush.second.push_back(1 << shift);
									for (int check : usedints) { if (groupstwo[i].first[k] == check) { found = true; break; } }
									if (found) { found = false; }
									else { usedints.push_back(groupstwo[i].first[k]); }
									for (int check : usedints) { if (groupstwo[i + 1].first[r] == check) { found = true; break; } }
									if (found) { found = false; }
									else { usedints.push_back(groupstwo[i + 1].first[r]); }
									topush.first.push_back(groupstwo[i].first[k]);
									topush.first.push_back(groupstwo[i + 1].first[r]);
									groups.push_back(topush);
								}
							}
						}
						for (int check : usedints) { if (groupstwo[i].first[k] == check) { found = true; break; } }
						if (found) { found = false; }
						else
						{
							usedints.push_back(groupstwo[i].first[k]);
							pair<vector<int>, vector<int>> topush;
							topush.first.push_back(groupstwo[i].first[k]);
							groups.push_back(topush);
						}
					}
				}
				else
				{
					if (groupstwo[i].first[0] != -1)
					{
						for (int check : usedints) { if (groupstwo[i].first[0] == check) { found = true; break; } }
						if (found) { found = false; }
						else
						{
							pair<vector<int>, vector<int>> topush;
							topush.first.push_back(groupstwo[i].first[0]);
							groups.push_back(topush);
						}
					}
				}
			}
			usedints.clear();
			for (int i(0); i < groupstwo.size() - 1; ++i)
			{
				for (int k(0); k < groupstwo.size(); ++k)
				{
					if (groupstwo[i].first.size() > groupstwo[k].first.size())
					{
						pair<vector<int>, vector<int>> swap(groupstwo[k]);
						groupstwo[k] = groupstwo[i];
						groupstwo[i] = swap;
					}
				}
			}
			groupstwo = groups;
			while (true)
			{
				vector<pair<vector<int>, vector<int>>> sorted(groupstwo);
				while (true)
				{
					bool differ(false);
					for (int s(0); s < groupstwo.size(); ++s)
					{
						for (int q(s + 1); q != groupstwo.size(); ++q)
						{
							if (groupstwo[s].first.size() < groupstwo[q].first.size())
							{
								pair<vector<int>, vector<int>> swap(groupstwo[s]);
								groupstwo[s] = groupstwo[q];
								groupstwo[q] = swap;
							}
						}
					}
					for (int s(0); s < groupstwo.size(); ++s) { if (groupstwo[s] != sorted[s]) { differ = true; break; } }
					if (!differ) { break; }
					else { sorted = groupstwo; }
				}
				groups.clear();
				vector<vector<int>> usedgroups;
				for (int i(0); i < groupstwo.size(); ++i)
				{
					found = false;
					if (i != groupstwo.size() - 1)
					{
						for (int k(i + 1); k < groupstwo.size(); ++k)
						{
							for (int shift(0); shift <= vars; ++shift)
							{
								if ((sum(groupstwo[i].first) - sum(groupstwo[i].second) ^ sum(groupstwo[k].first) - sum(groupstwo[k].second)) == (1 << shift) && groupstwo[i].second == groupstwo[k].second)
								{
									bool samediff(false);
									for (int difference : groupstwo[i].second)
									{
										if ((1 << shift) == difference/* && difference != groupstwo[i].second.back()*/)
										{
											samediff = true; break;
										}
									}
									if (samediff) { continue; }
									bool overlap(false);
									for (int r(0); r < groupstwo[i].first.size(); ++r)
									{
										bool tobreak(false);
										for (int f(0); f < groupstwo[k].first.size(); ++f)
										{
											if (groupstwo[i].first[r] == groupstwo[k].first[f]) { overlap = true; tobreak = true; break; }
										}
										if (tobreak) { break; }
									}
									if (overlap)
									{
										continue;
									}
									for (vector<int> check : usedgroups) { if (check == groupstwo[k].first) { found = true; break; } }
									if (found) { found = false; }
									else { usedgroups.push_back(groupstwo[k].first); }
									pair<vector<int>, vector<int>> topush;
									for (int z : groupstwo[i].first) { topush.first.push_back(z); }
									for (int z : groupstwo[k].first) { topush.first.push_back(z); }
									for (int z : groupstwo[i].second) { topush.second.push_back(z); }
									topush.second.push_back(1 << shift);
									groups.push_back(topush);
								}
							}
						}
					}
					else
					{
						for (vector<int> check : usedgroups) { if (check == groupstwo[i].first) { found = true; break; } }
						if (found) { found = false; }
						else { usedgroups.push_back(groupstwo[i].first); groups.push_back(groupstwo[i]); }
					}
					for (vector<int> check : usedgroups) { if (check == groupstwo[i].first) { found = true; break; } }
					if (found) { found = false; }
					else { usedgroups.push_back(groupstwo[i].first); groups.push_back(groupstwo[i]); }
				}
				if (groupstwo == groups)
				{
					groups = groupstwo;
					while (true)
					{
						for (int i(0); i < groups.size() - 1; ++i)
						{
							for (int k(i + 1); k < groups.size(); ++k)
							{
								int matches(0);
								for (int r : groups[i].first)
								{
									bool erased(false);
									for (int f : groups[k].first)
									{
										if (r == f)
										{
											++matches;
											if (matches == groups[k].first.size())
											{
												groups.erase(groups.begin() + k);
												erased = true;
												break;
											}
										}
									}
									if (erased) { break; }
								}
							}
						}
						if (groups == groupstwo) { break; }
						else { groupstwo = groups; }
					}
					//cout << "______________________________\n";
					//for (int i(0); i < groups.size(); ++i)
					//{
					//	for (int m : groups[i].first) { cout << setw(width) << m << setw(0) << " "; }
					//	cout << setw(width) << "|";
					//	for (int m : groups[i].second) { cout << setw(width) << m << setw(0) << " "; }
					//	cout << endl;
					//}
					vector<vector<int>> essentialgroups, unessentialgroups;
					vector<int> essentialnums, unfoundnums;
					for (int o : ones)
					{
						int counter(0);
						for (pair<vector<int>, vector<int>> pair : groups)
						{
							if (count(pair.first, o) == 1) { ++counter; }
						}
						if (counter == 1) { essentialnums.push_back(o); }
					}
					for (int n : essentialnums)
					{
						for (pair<vector<int>, vector<int>> pair : groups)
						{
							if (count(pair.first, n) == 1)
							{
								essentialgroups.push_back(pair.first);
							}
						}
					}
					for (pair<vector<int>, vector<int>> p : groups)
					{
						bool found(false);
						for (vector<int> eg : essentialgroups)
						{
							if (p.first == eg) { found = true; break; }
						}
						if (!found) { unessentialgroups.push_back(p.first); }
					}
					//vector<vector<int>> temp;
					//for (vector<int> ug : unessentialgroups)
					//{
					//	temp.insert(temp.begin(), ug);
					//}
					//unessentialgroups = temp; temp.clear();
					for (int o : ones)
					{
						bool found(false);
						for (vector<int> eg : essentialgroups)
						{
							for (int en : eg)
							{
								if (o == en) { found = true; break; }
							}
							if (found) { /*cout << " found in " << eg[0] << endl;*/ break; }
						}
						if (!found)
						{
							unfoundnums.push_back(o);
						}
					}
					while (unfoundnums.size() != 0)
					{
						int maxmatched(0);
						vector<int> todel, matched, toessentialise;
						for (vector<int> ug : unessentialgroups)
						{
							matched.clear();
							for (int un : ug)
							{
								for (int o : unfoundnums)
								{
									if (un == o)
									{
										matched.push_back(o);
									}
								}
							}
							if (maxmatched < matched.size())
							{
								maxmatched = matched.size();
								toessentialise = ug;
								todel = matched;
							}
						}
						if (todel.size() != 0)
						{
							for (int d : todel)
							{
								for (int r(0); r < unfoundnums.size(); ++r) { if (d == unfoundnums[r]) { unfoundnums.erase(unfoundnums.begin() + r); } }
							}
							todel.clear();
						}
						if (toessentialise.size() != 0)
						{
							essentialgroups.push_back(toessentialise);
						}
					}
					for (int g(0); g < essentialgroups.size(); ++g)
					{
						//for (int n : essentialgroups[g])
						//{
						//	cout << n << " ";
						//}
						//cout << endl;
						perhaps.push_back(grouptoprint(essentialgroups[g], vars));
					}
					break;
				}
				else { groupstwo = groups; }
			}
			printf("\nПозиции единиц в карте: ");
			for (int o(0); o < ones.size(); ++o)
			{
				if (o != 0)
				{
					printf(", %d", ones[o]);
				}
				else
				{
					printf("%d", ones[o]);
				}
			}
			printf("\n");
			printf("\nПозиции нулей в карте: ");
			for (int z(0); z < zeroes.size(); ++z)
			{
				if (z != 0)
				{
					printf(", %d", zeroes[z]);
				}
				else
				{
					printf("%d", zeroes[z]);
				}
			}
			printf("\n");
			for (int times(0); times < vars; ++times)
			{
				for (int p(0); p < perhaps.size() - 1; ++p)
				{
					for (int pp(p + 1); pp < perhaps.size(); ++pp)
					{
						int diffs(0), diffpos(0);
						if (perhaps[p] == perhaps[pp]) { perhaps.erase(perhaps.begin() + pp); }
						else
						{
							for (int c(0); c < perhaps[p].size(); ++c)
							{
								if (perhaps[p][c] != perhaps[pp][c])
								{
									++diffs;
									diffpos = c;
									if (diffs > 1) { break; }
								}
							}
						}
						if (diffs == 1 && perhaps[p][diffpos] != '-' && perhaps[pp][diffpos] != '-')
						{
							perhaps[p][diffpos] = '-';
							perhaps.erase(perhaps.begin() + pp);
						}
					}
				}
			}
			certainly = perhaps;
			printf("\nМинимизация: "); //https://www.mathematik.uni-marburg.de/~thormae/lectures/ti1/code/qmc/ https://www.charlie-coleman.com/experiments/kmap/ https://arxiv.org/ftp/arxiv/papers/1404/1404.3349.pdf
			for (int mt(0); mt < certainly.size(); ++mt)
			{
				if (mt != certainly.size() - 1)
				{
					for (int c(0); c < certainly[mt].size(); ++c)
					{
						if (certainly[mt][c] == '1') { printf("%c", 65 + c); }
						else if (certainly[mt][c] == '0') { printf("%c%c", 33, 65 + c); }
					}
					printf("+");
				}
				else
				{
					for (int c(0); c < certainly[mt].size(); ++c)
					{
						if (certainly[mt][c] == '1') { printf("%c", 65 + c); }
						else if (certainly[mt][c] == '0') { printf("%c%c", 33, 65 + c); }
					}
				}
			}
			printf("\n\n");
		}
		if (ones.size() == powa(2, vars)) { printf("\nМинимизация: 1\n\n"); }
		else if (ones.size() == 0) { printf("\nМинимизация: 0\n\n"); }
	}
}
