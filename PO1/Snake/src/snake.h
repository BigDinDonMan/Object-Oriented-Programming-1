#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include<vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#define DEFAULT_COUNTER_VALUE 15
class CSnake : public CFramedWindow
{
	private:
		unsigned int snake_size;
		std::pair<CPoint, CPoint> intro_coords;
		std::pair<CPoint, CPoint> help_coords;
		CPoint level_info_coords;
		CPoint points_coords;
		std::vector<CPoint> snake_elements_coords;
		CPoint food_location;

	public:
		bool help_displayed;
		bool game_began;
		bool paused;
		bool game_over;
		bool boost;
		unsigned int moveCounter;
		unsigned int modCounterValue;
		int action;
  		CSnake(CRect r, char _c = ' ');
  		void paint();
  		bool handleEvent(int key);
  		void initGame();
  		void handlePause();
  		void move(const CPoint& delta);
  		void calculateFoodPosition();
  		void moveSnake(const CPoint&);
  		void paintSnake();
  		void updateMoveCounter();
  		void reset();
  		int reversedClamp(int min, int max, int value);
  		int clamp(int min, int max, int value);

};

#endif
