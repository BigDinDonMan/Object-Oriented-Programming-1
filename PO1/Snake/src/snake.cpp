#include "snake.h"
#include "screen.h"


CSnake::CSnake(CRect r, char _c /*=' '*/) 
: 
CFramedWindow(r, _c), moveCounter(0), snake_size(1), game_began(false), action(KEY_RIGHT), boost(false), 
modCounterValue(DEFAULT_COUNTER_VALUE), help_displayed(false), paused(false), 
intro_coords(std::make_pair(CPoint(7, 7), CPoint(7, 8))), help_coords(std::make_pair(CPoint(7, 9), CPoint(7, 10))),
level_info_coords(CPoint(6, 4)), points_coords(CPoint(6, 5)), food_location(CPoint(geom.topleft.x + 1, geom.topleft.y + 1))
{}

int CSnake::reversedClamp(int min, int max, int value) {
    if (value < min) return max;
    if (value > max) return min;
    return value;
}

int CSnake::clamp(int min, int max, int value) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void CSnake::paint() {
	
    if (game_began) {
        gotoyx(level_info_coords.y, level_info_coords.x);
        printl("LEVEL: %u", this->snake_size);
        gotoyx(points_coords.y, points_coords.x);
        printl("POINTS: %u", (this->snake_size - 1) * 10);
    }

	CFramedWindow::paint();
    if (game_over) {
        gotoyx(help_coords.first.y, help_coords.first.x);
        printl("GAME OVER");
        gotoyx(help_coords.second.y, help_coords.second.x);
        printl("your score: %u", (snake_size - 1) * 10);
    }
    if (!game_began && !game_over) {
     gotoyx(intro_coords.first.y, intro_coords.first.x);
     printl("press h for help\n");
     gotoyx(intro_coords.second.y, intro_coords.second.x);
     printl("press r to start/restart");
    }
    if (help_displayed) {
    	gotoyx(help_coords.first.y, help_coords.first.x);
		printl("arrows - move snake(game) or window(pause)");
		gotoyx(help_coords.second.y, help_coords.second.x);
		printl("collect food to gather points");
    }
}

void CSnake::move(const CPoint& delta) {
	geom.topleft += delta;
	intro_coords = std::make_pair(intro_coords.first += delta, intro_coords.second += delta);
	help_coords = std::make_pair(help_coords.first += delta, help_coords.second += delta);
	level_info_coords += delta;
	points_coords += delta;
    food_location += delta;
    if (paused) {
        for (CPoint& x : snake_elements_coords) {
            x += delta;
        }
    }
}



void CSnake::updateMoveCounter() {
    modCounterValue = DEFAULT_COUNTER_VALUE - log(snake_size + 1) - sqrt(snake_size);
    modCounterValue = clamp(2, DEFAULT_COUNTER_VALUE, modCounterValue);
}

void CSnake::calculateFoodPosition() {
    CPoint foodPoint;
    for (;;) {
        bool flag= false;
        int x, y;
        x = geom.topleft.x + 1 + (rand() % (geom.size.x - 2));
        y = geom.topleft.y + 1 + (rand() % (geom.size.y - 2));
        foodPoint = CPoint(x, y);
        for (auto x : snake_elements_coords) {
            if (x == foodPoint) {
                flag = true;
                break;
            }
        }
        if (flag) {
            flag = false;
            continue;
        }
        break;
    }
    this->food_location = foodPoint;
}

void CSnake::moveSnake(const CPoint& dir) {
    CPoint prev = snake_elements_coords[0];
    snake_elements_coords[0] += dir;
    for (auto i = ++snake_elements_coords.begin(); i != snake_elements_coords.end(); ++i) {
        CPoint temp = *i;
        *i = prev;
        prev = temp;

    }
    for (CPoint& coord : snake_elements_coords) {
        int x = coord.x, y = coord.y;
        x = reversedClamp(geom.topleft.x + 1, geom.topleft.x + geom.size.x - 2, x);
        y = reversedClamp(geom.topleft.y + 1, geom.topleft.y + geom.size.y - 2, y);
        coord = CPoint(x, y);
    }
    
    if (snake_size > 1) {
        for (int i = 1; i < (int)snake_elements_coords.size(); ++i) {
            if (snake_elements_coords[i] == snake_elements_coords[0]) {
                game_over = true;
                game_began = false;
                break;
            }
        }
    }

    paint();
    update_screen();
    if (snake_elements_coords[0] == food_location) {
        ++snake_size;
        snake_elements_coords.push_back(food_location);
        paint();
        calculateFoodPosition();
        updateMoveCounter();
    }
    if (!game_over) paintSnake();
    refresh();
    moveCounter %= modCounterValue;
}

void CSnake::paintSnake() {
    if (game_over) return;
    for (auto i = snake_elements_coords.begin(); i != snake_elements_coords.end(); ++i) {
        gotoyx((*i).y, (*i).x);
        if (i != snake_elements_coords.begin()) printc('+');
        else printc('o');
    }
    gotoyx(food_location.y, food_location.x);
    printc('$');
}

void CSnake::reset() {
    snake_elements_coords.clear();
    paused = game_over = false;
    game_began = true;
    action = KEY_RIGHT;
    modCounterValue = DEFAULT_COUNTER_VALUE;
    moveCounter = 0;
    snake_size = 1;
    int x = (geom.size.x + geom.topleft.x) / 2, y = (geom.size.y + geom.topleft.y) / 2;
    gotoyx(y, x);
    snake_elements_coords.push_back(CPoint(x, y));
    printc('+');
}


void CSnake::initGame() {
    help_displayed = false;
    reset();
    calculateFoodPosition();
}

void CSnake::handlePause() {
	if (!game_began) return;
	paused = !paused;
}

bool CSnake::handleEvent(int key) {
	if (!game_began || paused) {
       if (CWindow::handleEvent(key)) return true;
	   switch (key) {
    		case 'h': case 'H':
                if (paused) return false;
    			help_displayed = !help_displayed;
    			paint();
    			return true;
    		case 'r': case 'R':
    			initGame();
    			return true;
	   }
    }
    
    if (game_began && !paused) {
        ++moveCounter;
        update_screen();
        paint();
        paintSnake();
        refresh();
        switch (key) {
            case KEY_DOWN:
            if (action == KEY_UP) return false; 
            moveSnake(CPoint(0, 1));
            action = key;
            return true; 
            case KEY_UP:
            if (action == KEY_DOWN) return false;
            moveSnake(CPoint(0, -1));
            action = key;
            return true;  
            case KEY_RIGHT:
            if (action == KEY_LEFT) return false; 
            moveSnake(CPoint(1, 0));
            action = key;
            return true; 
            case KEY_LEFT:
            if (action == KEY_RIGHT) return false;
            moveSnake(CPoint(-1, 0));
            action = key;
            return true;
            default:
            if (moveCounter < modCounterValue) return false;
            switch (action) {
                case KEY_RIGHT:
                moveSnake(CPoint(1, 0));
                return true; 
                case KEY_UP:
                moveSnake(CPoint(0, -1));
                return true; 
                case KEY_DOWN:
                moveSnake(CPoint(0, 1));
                return true; 
                case KEY_LEFT:
                moveSnake(CPoint(-1, 0));
                return true; 
            } 
        }
        // switch (key) {
        //     if (key == action) {
        //         boost = true;
        //     }
        //     case KEY_UP:
        //     if (action == KEY_DOWN) return false;
        //     if (!boost && moveCounter % modCounterValue != 0) {
        //         action = KEY_UP;
        //         return true;
        //     }
        //     moveSnake(CPoint(0, -1));
        //     action = KEY_UP;
        //     return true;
        //     case KEY_DOWN:
        //     if (action == KEY_UP) return false;
        //     if (!boost && moveCounter % modCounterValue != 0) {
        //         action = KEY_DOWN;
        //         return true;
        //     }
        //     moveSnake(CPoint (0, 1));
        //     action = KEY_DOWN;
        //     return true;
        //     case KEY_RIGHT:
        //     if (action == KEY_LEFT) return false;
        //     if (!boost && moveCounter % modCounterValue != 0) {
        //         action = KEY_RIGHT;
        //         return true;
        //     }
        //     moveSnake(CPoint (1, 0));
        //     action = KEY_RIGHT;
        //     return true;
        //     case KEY_LEFT:
        //     if (action == KEY_RIGHT) return false;
        //     if (!boost && moveCounter % modCounterValue != 0) {
        //         action = KEY_LEFT;
        //         return true;
        //     }
        //     moveSnake(CPoint (-1, 0));
        //     action = KEY_LEFT;
        //     return true;
        //     default:
        //     switch (action) {
        //         case KEY_UP:
        //         if (moveCounter % modCounterValue != 0) {
        //             return false;
        //         }
        //         moveSnake(CPoint(0, -1));
        //         return true;
        //         case KEY_DOWN:
        //         if (moveCounter % modCounterValue != 0) {
        //             return false;
        //         }
        //         moveSnake(CPoint (0, 1));
        //         return true;
        //         case KEY_RIGHT:
        //         if (moveCounter % modCounterValue != 0) {
        //             return false;
        //         }
        //         moveSnake(CPoint (1, 0));
        //         return true;
        //         case KEY_LEFT:
        //         if (moveCounter % modCounterValue != 0) {
        //             return false;
        //         }
        //         moveSnake(CPoint (-1, 0));
        //         return true;
        //     }
        //     return true;
        // }
    }
	return false;
}