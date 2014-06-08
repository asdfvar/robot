#ifndef _LIST_H_
#define _LIST_H_

#include "robot.h"

class robot;

class list {

   public:

#if 0
      robot *prev, *head, *next;
      robot *head;
#endif
      int N;

      list();
      ~list();

      robot *get_robot();
      void append(robot*);
      void remove();
      void clear();
      void set_next();
      void set_prev();
      void print();

  private:

    robot *head;

};

#endif
