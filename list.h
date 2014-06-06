#ifndef _LIST_H_
#define _LIST_H_

#include "robot.h"

class robot;

class list {

   public:

      robot *prev, *head, *next;

      list();
      ~list();

      void append(robot*);
      void print();

};

#endif
