#include "winsys.h"
#include "cpoint.h"
#include "snake.h"
#include "screen.h"

#include<typeinfo>
#include <list>
#include <string>
#include <ctype.h>
#include <stdarg.h>
using namespace std;

void CView::move(const CPoint & delta)
{
  geom.topleft += delta;
}

void CWindow::paint()
{
  for (int y = geom.topleft.y; y < geom.topleft.y + geom.size.y; y++)
    for (int x = geom.topleft.x; x < geom.topleft.x + geom.size.x; x++)
    {
      gotoyx(y, x);
      printl("%c", c);
    }
}

bool CWindow::handleEvent(int key)
{
  switch (key)
    {
    case KEY_UP:
      move (CPoint (0, -1));
      return true;
    case KEY_DOWN:
      move (CPoint (0, 1));
      return true;
    case KEY_RIGHT:
      move (CPoint (1, 0));
      return true;
    case KEY_LEFT:
      move (CPoint (-1, 0));
      return true;
    };
  return false;
}

void CFramedWindow::paint()
{
  for(int y = geom.topleft.y; y < geom.topleft.y + geom.size.y; y++)
  {
    if((y == geom.topleft.y) || (y == geom.topleft.y + geom.size.y-1))
    {
      for(int x = geom.topleft.x; x < geom.topleft.x + geom.size.x; x++)
      {
        gotoyx(y, x);
        if((x == geom.topleft.x) || (x == geom.topleft.x + geom.size.x-1))
          printl ("+");
        else
          printl ("-");
      }
    }
    else
    {
      for(int x = geom.topleft.x; x < geom.topleft.x + geom.size.x; x++)
      {
        gotoyx(y, x);
        if((x == geom.topleft.x) || (x == geom.topleft.x + geom.size.x-1))
          printl ("|");
        else
          printl ("%c", c);
      }
    }
  }
}

void CInputLine::paint()
{
  CFramedWindow::paint();

  unsigned int row = 0;
  for(int y = geom.topleft.y+1; y < geom.topleft.y + geom.size.y-1; y++, row++)
  {
    unsigned int letter = row * (geom.size.x-2);
    for (int x = geom.topleft.x+1; x < geom.topleft.x + geom.size.x-1; x++, letter++)
    {
      gotoyx(y, x);
      printl("%c", letter < text.size() ? text[letter] : c);
    }
  }
}

bool CInputLine::handleEvent(int c)
{
  if(CFramedWindow::handleEvent(c))
    return true;
  if((c == KEY_DC) || (c == KEY_BACKSPACE))
    {
      if (text.length() > 0)
        {
          text.erase (text.length() - 1);
          return true;
        };
    }
  if((c > 255) || (c < 0))
    return false;
  if(!isalnum (c) && (c != ' '))
    return false;
  text.push_back(c);
  return true;
}

void CGroup::paint()
{
  for(int y= geom.topleft.y; y < geom.topleft.y + geom.size.y; y++)
  {
    gotoyx(y, geom.topleft.x);
    for(int x = 0; x < geom.size.x; x++)
      printl (".");
  }

  for (list< CView * >::iterator i = children.begin(); i != children.end(); i++)
    (*i)->paint();
}

bool CGroup::handleEvent(int key)
{
  if (!children.empty() && children.back()->handleEvent (key))
    return true;
  if (key == '\t')
    {
      if (!children.empty())
        {
          children.push_front(children.back());
          children.pop_back();
        };
      return true;
    }
  return false;
}

void CGroup::insert(CView * v)
{
  children.push_back(v);
}

CGroup::~CGroup()
{
  for (list< CView * >::iterator i = children.begin();
       i != children.end(); i++)
    delete(*i);
}

CDesktop::CDesktop() : CGroup(CRect())
{
  init_screen();
  update_screen();
}

CDesktop::~CDesktop()
{
  done_screen();
}

void CDesktop::paint()
{
  getscreensize (geom.size.y, geom.size.x);

  for(int y = geom.topleft.y; y < geom.topleft.y + geom.size.y; y++)
  {
    gotoyx(y, geom.topleft.x);
    for (int x = 0; x < geom.size.x; x++)
      printl (".");
  }

  CGroup::paint();
}

int CDesktop::getEvent()
{
  return ngetch();
}

void CDesktop::run()
{
  update_screen();
  paint();
  refresh();
  
  
  CSnake* snake = dynamic_cast<CSnake*>(children.back());
  srand(time(NULL));
  while(1)
  {
    int c = getEvent();
    if(c == 'q' || c == 'Q')
      break;
    // ++snake->moveCounter;
    if (c == 'p' || c == 'P') {
      snake->handlePause();
    }
    if (c == KEY_RESIZE || CGroup::handleEvent(c)) {
      if (snake != children.back() || !snake->game_began || snake->paused) {
        update_screen();
        paint();
        refresh();
      }
    }
    /*if (c == '\t') {
      if (!snake->game_began)
        goto changeWindow;
    }

    if (snake == children.back()) {
    if (!snake->game_began || snake->paused ) {
        if (c==KEY_RESIZE || snake->handleEvent(c)) {
        update_screen();
        if (!snake->game_began || snake->paused) paint();
        if (snake->paused) snake->paintSnake();
        refresh();
     }
    } 
    
    if (snake->game_began && !snake->paused) {
          
          for (auto i = tempVec.begin(); i != tempVec.end(); ++i) {
           if (*i == c) snake->boost = true;
          }

          if (tempVec.size() >= 3) {
            tempVec.clear();
            snake->boost = false;
          }
          if (c == KEY_RESIZE || snake->handleEvent(c)) {
              
              update_screen();
              snake->paintSnake();
              refresh();
            
          }
    }
    if (snake->game_began && snake->paused) {
      if (c==KEY_RESIZE || snake->handleEvent(c)) {
        update_screen();
        paint();
        snake->paintSnake();
        refresh();
      }
    }
  }
  else {
    changeWindow:
    if (c == KEY_RESIZE || CGroup::handleEvent(c)) {
      update_screen();
      paint();
      if (snake == children.back() && snake->paused) {
        snake->paint();
      }
      //snake->paint();
      refresh();
    } 
  }
  tempVec.push_back(c);*/
}
}
