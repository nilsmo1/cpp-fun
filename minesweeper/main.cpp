#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <termios.h>

#define ROWS   15
#define COLS   17
#define MINE_P 15

#define MINE_C 	  '@'
#define EMPTY_C   ' '
#define HIDDEN_C  '.'
#define FLAGGED_C '?'

#define endl '\n'

enum State   { HIDDEN, SHOWN, FLAGGED };
enum Content { EMPTY , MINE };

struct Cell {
	int row, col;
	State state = HIDDEN;
	Content content = EMPTY;	
};

typedef std::vector<Cell> Row;
typedef std::vector<Row>  Field;

Field initField() {
	Field field;
	for (int i=0; i<ROWS; i++) {
		Row row;
		for (int j=0; j<COLS; j++) {
			Content content = ((std::rand() % 100 > MINE_P)? EMPTY : MINE);
			row.push_back(Cell {i, j, .content=content});
		} field.push_back(row);
	} return field;
}

int nbors(Field field, Cell c) {
	if (c.content == MINE) return 0;
	int row = c.row, col = c.col, dr, dc, ns = 0;
	for (dr=-1; dr<2; dr++) for (dc=-1; dc<2; dc++) {
			if (!(row + dr < ROWS and row + dr >= 0) ||
				!(col + dc < COLS and col + dc >= 0) ||
				dr==dc && dc==0)
				continue;
			if (field[row+dr][col+dc].content == MINE) ns++; 
	} return ns; 
}

void displayCell(Cell c, int ns) {
	switch (c.state) {
		case HIDDEN  : std::cout << HIDDEN_C ; break;
		case FLAGGED : std::cout << FLAGGED_C; break;
		case SHOWN   : switch (c.content) {
				case MINE  : std::cout << MINE_C; break;
				case EMPTY : if (ns > 0) std::cout << ns;
							 else std::cout << EMPTY_C;
		}
	}
}

void displayField(Field field, int cr, int cc) {
	int rid = 0, cid = 0;
	for (auto r : field) { for (auto c : r) { 
			bool ch_prev (rid == cr && cid-1 == cc);
			bool ch = (rid == cr && cid == cc);
			int ns = nbors(field, c);
			if (ch) std::cout << '(';
			else if (!ch_prev) std::cout << EMPTY_C;
			displayCell(c, ns);
			if (ch) std::cout << ')';
			cid++;
		} if (rid == cr && cid == cc) std::cout << endl; 
		else std::cout << EMPTY_C << endl; cid=0; rid++;
	}
}

void showAllMines(Field& field) {
	for (auto &r : field) for (auto &c : r) {
		if (c.content == MINE) c.state = SHOWN;
	}
}

void openCell(Field& field, int cr, int cc) {
	Row ns{}; Cell pc, tmpc;
	int dr, dc, row, col;
	Cell ch = field[cr][cc];
	if (ch.content == MINE){ field[cr][cc].state = SHOWN; return; }
	if (nbors(field, ch) == 0) {
		ns.push_back(ch);
		while (!ns.empty()) {
			pc = ns.back(); ns.pop_back();
			row = pc.row;
			col = pc.col;
			for (dr=-1; dr<2; dr++) for (dc=-1; dc<2; dc++) {
				if (!(row + dr < ROWS and row + dr >= 0) ||
					!(col + dc < COLS and col + dc >= 0) ||
					dr==dc && dc==0)
					continue;
				Cell tmpc = field[row+dr][col+dc];
				if (tmpc.state == HIDDEN && nbors(field, tmpc) == 0) {
					field[row+dr][col+dc].state = SHOWN;
					ns.push_back(tmpc);
				} else if (tmpc.state == HIDDEN) 
					field[row+dr][col+dc].state = SHOWN;
			}
		}
	} else field[cr][cc].state = SHOWN;
}

bool onlyMinesLeft(Field field) {
	for (auto r : field) for (auto c : r) {
		if (c.state == HIDDEN && c.content == EMPTY) return false;
	} return true;
}

void flagCell(Field& field, int cr, int cc) {
    if (field[cr][cc].state != SHOWN) {field[cr][cc].state = FLAGGED; }
}

int main() {
	
	struct termios tattr;
	struct termios saved_attributes;

	tcgetattr(0, &saved_attributes);
	tcgetattr(0, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &tattr);

	std::srand(std::time(nullptr));
	Field field = initField();
	int cr = 0, cc = 0;
	displayField(field, cr, cr);
    std::cout << endl;
	std::cout << "\e[?25l";

	char in;
	while (std::cin >> in) {
		switch(in) {
			case 'w': if (cr != 0     ) cr-- ; break;
			case 's': if (cr <  ROWS-1) cr++ ; break;
			case 'a': if (cc != 0     ) cc-- ; break;
			case 'd': if (cc <  COLS-1) cc++ ; break;
			case 'e': openCell(field, cr, cc); break;
			case 'f': flagCell(field, cr, cc); break;
		} if (in == 'q') break;
		std::cout << "\033["<<ROWS+1<<'A';
		std::cout << "\033["<<COLS+1<<'D';
		displayField(field, cr, cc);
        std::cout << endl;
		Cell tmpc = field[cr][cc];
		if (tmpc.state == SHOWN && tmpc.content == MINE) {
			showAllMines(field);
			std::cout << "\033["<<ROWS+1<<'A';
			std::cout << "\033["<<COLS+1<<'D';
			displayField(field, cr, cc);
			std::cout << "You lose.." << endl;;
			break;
		} if (onlyMinesLeft(field)) {
			std::cout << "\033["<<ROWS+1<<'A';
			std::cout << "\033["<<COLS+1<<'D';
			displayField(field, cr, cc);
            std::cout << "You win!" << endl; 
            break;
        }
	} std::cout << "\e[?25h";
	tcsetattr(0, TCSANOW, &saved_attributes);
    return 0;
}
