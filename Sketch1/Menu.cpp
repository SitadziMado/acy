#include "Menu.h"
#include <locale.h>

/* char mapCyrillic(char character)
{
	using _u = unsigned char;
	static const int CharactersTotal = 256;
	static char map[CharactersTotal] = { 0 };
	static bool nonInit = true;

	if (nonInit)
	{
		map[_u('�')] = char('A');	map[_u('�')] = char('a');
		map[_u('�')] = char(160);	map[_u('�')] = char(178);
		map[_u('�')] = char('B');	map[_u('�')] = char(179);
		map[_u('�')] = char(161);	map[_u('�')] = char(180);
		map[_u('�')] = char(224);	map[_u('�')] = char(227);
		map[_u('�')] = char('E');	map[_u('�')] = char('e');
		map[_u('�')] = char(162);	map[_u('�')] = char(181);
		map[_u('�')] = char(163);	map[_u('�')] = char(182);
		map[_u('�')] = char(164);	map[_u('�')] = char(183);
		map[_u('�')] = char(165);	map[_u('�')] = char(184);
		map[_u('�')] = char(166);	map[_u('�')] = char(185);
		map[_u('�')] = char('K');	map[_u('�')] = char(186);
		map[_u('�')] = char(167);	map[_u('�')] = char(187);
		map[_u('�')] = char('M');	map[_u('�')] = char(188);
		map[_u('�')] = char('H');	map[_u('�')] = char(189);
		map[_u('�')] = char('O');	map[_u('�')] = char('o');
		map[_u('�')] = char(168);	map[_u('�')] = char(190);
		map[_u('�')] = char('P');	map[_u('�')] = char('p');
		map[_u('�')] = char('C');	map[_u('�')] = char('c');
		map[_u('�')] = char('T');	map[_u('�')] = char(191);
		map[_u('�')] = char(169);	map[_u('�')] = char('y');
		map[_u('�')] = char(170);	map[_u('�')] = char(228);
		map[_u('�')] = char('X');	map[_u('�')] = char('x');
		map[_u('�')] = char(229);	map[_u('�')] = char(229);
		map[_u('�')] = char(171);	map[_u('�')] = char(192);
		map[_u('�')] = char(172);	map[_u('�')] = char(193);
		map[_u('�')] = char(226);	map[_u('�')] = char(230);
		map[_u('�')] = char(173);	map[_u('�')] = char(194);
		map[_u('�')] = char(174);	map[_u('�')] = char(195);
		map[_u('�')] = char('b');	map[_u('�')] = char(196);
		map[_u('�')] = char(175);	map[_u('�')] = char(197);
		map[_u('�')] = char(176);	map[_u('�')] = char(198);
		map[_u('�')] = char(177);	map[_u('�')] = char(199);
		nonInit = false;
	}

	char rv = map[(unsigned char)character];
	return rv ? rv : character;
}

String operator ""_Cyr(char const* str, std::size_t size)
{
	static const int BufferSize = 256;
	char buffer[BufferSize];

	char const* src = str;
	char* dst = buffer;

	for (std::size_t i = 0; i < size; ++i)
	{
		*dst++ = mapCyrillic(*src++);
	}

	*dst = '\0';

	return String(buffer);
} */

#define A String('A')
#define B String(char(160))
#define V String('B')
#define G String(char(161))
#define D String(char(224))
#define E String('E')
#define Yo String(char(162))
#define Zh String(char(163))
#define Z String(char(164))
#define I String(char(165))
#define Ii String(char(166))
#define K String('K')
#define L String(char(167))
#define M String('M')
#define N String('H')
#define O String('O')
#define P String(char(168))
#define R String('P')
#define S String('C')
#define T String('T')
#define Y String(char(169))
#define F String(char(170))
#define X String('X')
#define Tz String(char(229))
#define Ch String(char(171))
#define Sh String(char(172))
#define Shi String(char(226))
#define tverdiy String(char(173))
#define Ui String(char(174))
#define myagkiy String('b')
#define Ee String(char(175))
#define Yu String(char(176))
#define Ya String(char(177))

#define a String('a')
#define b String(char(178))
#define v String(char(179))
#define g String(char(180))
#define d String(char(227))
#define e String('e')
#define yo String(char(181))
#define zh String(char(182))
#define z String(char(183))
#define si String(char(184))
#define ii String(char(185))
#define k String(char(186))
#define l String(char(187))
#define m String(char(188))
#define n String(char(189))
#define o String('o')
#define p String(char(190))
#define r String('p')
#define s String('c')
#define t String(char(191))
#define y String('y')
#define f String(char(228))
#define x String('x')
#define tz String(char(229))
#define ch String(char(192))
#define sh String(char(193))
#define shi String(char(230))
#define stverdiy String(char(194))
#define ui String(char(195))
#define smyagkiy String(char(196))
#define ee String(char(197))
#define u String(char(198))
#define ya String(char(199))

Menus menuMode = Menus::Main;

const String notification[] = { "�� ��������","�������� �����","�� ���������", "������" };
String dlin = D+l;
String kol = K+o+l;
String iz = I+z;
bool upside = true;

Menu::Menu(const LiquidCrystal& lcdInit) :
	lcd(lcdInit)
{
	lcd.begin(16,2);
	for (size_t i = 0; i < maxX; i++)
	{
		for (size_t j = 0; j < maxY; j++)
		{
			if (j != maxY - 1)
				items[i][j] = "               ";
			else 
				items[i][j] = "|______________|";
		}
	}

	// Menu curX = 0
	//items[0][0] = Sh+a+g+si+':';
	// Close curX = 2
	items[2][0] = P+r+o+d+o+l+zh+si+t+smyagkiy+':'+' '+'#';
	items[2][1] = M+e+n+u+':'+' '+'*';
	// Input curX = 3
	items[3][0] = dlin + String(char(184)) + String(char(189)) + ": ";
	items[3][1] = kol + ": ";
	
	// Print a message to the LCD.
	lcd.print("  "+Z+a+g+r+y+z+k+a+"...");
}

void Menu::UpdateProgRaw(int id, int leng, int amt)
{
	items[0][id] = String(id+1) + "." + dlin + ":" + String(leng) + " " + kol + ":" + String(amt);
}

void Menu::DrawMenu()
{
	String str = "";
	switch (menuMode)
	{
	case Main: // +'>' before selected line
		lcd.setCursor(0, 0);
		if (upside) str = ">";
		lcd.print(str+items[curX][curY]);
		lcd.setCursor(0, 1);
		str = "";
		if (!upside) str = ">";
		lcd.print(str+items[curX][curY + 1]);
		break;
	case Inp: // cursor after selected line
		if (upside) 
		{
			lcd.setCursor(0, 1);
			lcd.print(items[curX][1]);
			lcd.setCursor(0, 0);
			lcd.print(items[curX][0]);
		}
		else
		{
			lcd.setCursor(0, 0);
			lcd.print(items[curX][0]);
			lcd.setCursor(0, 1);
			lcd.print(items[curX][1]);
		}
		break;
	default:
		lcd.setCursor(0, 0);
		lcd.print(items[curX][curY]);
		lcd.setCursor(0, 1);
		lcd.print(items[curX][curY + 1]);
		break;
	}
}

void Menu::RunProg(int id, int leng, int amt) 
{
	lcd.clear();
	items[1][0] = String(id) + "." + dlin + ":" + "0" + " " + iz + " " + String(leng);
	items[1][1] = kol + ":" + "0" + " " + iz + " " + String(amt);
	curX = 1;
	curY = 0;
	menuMode = Menus::Run;
}

void Menu::SetMenuMode(int newMenu)
{
	upside = true;
	menuMode = Menus(newMenu);
	switch (newMenu)
	{
	case Main:
		curX = 0;
		curY = 0;
		break;
	case Inp:
		upside = true;
		lcd.clear();
		curX = 3;
		curY = 0;
		break;
	case Stop:
		lcd.clear();
		curX = 2;
		curY = 0;
		break;
	case Run:
		break;
	default:
		break;
	}
}


void Menu::SetMenuMode(int newMenu, int id_y) 
{
	upside = true;
	menuMode = Menus(newMenu);
	switch (newMenu)	
	{
	case Main:
		curX = 0;
		curY = id_y;
		break;
	case Inp:
		upside = true;
		lcd.clear();
		curX = 3;
		curY = id_y;
		break;
	case Stop:
		lcd.clear();
		curX = 2;
		curY = id_y;
		break;
	case Run:
		break;
	default:
		break;
	}
}

void Menu::ApplyInput(int id, int &leng, int &amt)
{
	leng = items[3][0].substring(6).toInt();
	amt = items[3][1].substring(5).toInt();
	if (id > 15) id = 15;
	items[0][id] = String(id+1)+"."+ 
		dlin + ":"+ String(leng)+" " +
		kol +  ":"+ String(amt);
	items[3][0] = dlin+si+n+": ";
	items[3][1] = kol + ": ";
}

///
///
///
void Menu::Notification(int i)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(notification[i]);
}

void Menu::Input(char cha)
{
	if (upside && items[curX][curY].length() < 10 )// "dlin: " - 6 + 4 numbers
		items[curX][curY] += cha;
	if (!upside && items[curX][curY + 1].length() < 7)	 // "kol: " - 5 + 2 numbers
		items[curX][curY+1] += cha;
	
}

///
/// Delete last symbol
///
void Menu::DelLast()
{
	if (upside && items[curX][curY].length() > 6) //"dlin: " - 6
	{
		items[curX][curY] = items[curX][curY].substring(0, items[curX][curY].length() - 1);
		lcd.clear();
	}
	if(!upside && items[curX][curY+1].length() > 5) // "kol: "- 5
	{
		items[curX][curY+1] = items[curX][curY+1].substring(0, items[curX][curY+1].length() - 1);
		lcd.clear();
	}
}

void Menu::Right()
{
	lcd.scrollDisplayLeft();
}

void Menu::Left()
{
	lcd.scrollDisplayRight();
}

void Menu::Down()
{
	lcd.clear();
	if (upside) upside = !upside;
		else if (menuMode != Menus::Inp)
			if (curY < maxY - 2)
				++curY;
}

void Menu::Up()
{
	lcd.clear();
	if (!upside) upside = !upside;
	else if (menuMode != Menus::Inp)
		if (curY > 0)
			--curY;
}

int Menu::getX() const
{
	return curX;
}

int Menu::getY() const
{
	return curY;
}

void Menu::Toast(String str)
{
	lcd.setCursor(0, 0);
	lcd.print(str);
}



