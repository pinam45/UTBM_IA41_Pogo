#include <iostream>
#include <ConsoleControl.h>
#include <ConsoleControlMenu.h>
#include <ConsoleControlUtility.h>

int main() {
	cc_clean();
	const char* choices[] = {
	  "Human vs Human",
	  "Human vs AI",
	  "AI vs AI",
	  "Options",
	  "Exit"
	};
	cc_Menu menu;
	menu.choices = choices;
	menu.choicesNumber = 5;
	menu.currentChoice = 1;
	menu.choiceOnEscape = 4;
	menu.title = "Magic Pogo";
	const cc_MenuColors colors = {
	  CYAN,
	  BLACK,
	  WHITE,
	  BLACK,
	  CYAN,
	  BLACK
	};
	bool loop = true;
	while(loop){
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice){
			case 0:
				//TODO
				break;
			case 1:
				//TODO
				break;
			case 2:
				//TODO
				break;
			case 3:
				//TODO
				break;
			case 4:
				loop = false;
				break;
			default:break;
		}
	}
	return 0;
}
