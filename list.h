#ifndef _LIST_H_
#define _LIST_H_

#include "robot.h"

class robot;

class list {

   public:

      robot *prev, *head, *next;
      int N;

      list();
      ~list();

      robot *get_robot();
      void append(robot*);
      void remove();
      void set_next();
      void set_prev();
      void print();

};

#endif
