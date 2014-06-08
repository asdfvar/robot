/*
 * Circular linked list
 */

#include "list.h"
#include <iostream>

class robot;

/***************
 * Constructor *
 ***************/

list::list() {
  head = 0;
#if 0
  head = next = prev = 0;
#endif
  N = 0;
}

/**************
 * Destructor *
 **************/

list::~list() {

  robot *rob;

  while (N > 0) {
    rob = head;
    head = head->next;
    delete rob;
#if 0
     head = next;
     next = head->next;
#endif
     N--;
  }

}

/*************
 * get robot *
 *************/

robot *list::get_robot() {

  return head;

}

/********
 * next *
 ********/

void list::set_next() {

  head = head->next;

#if 0
  next = next->next;
  head = head->next;
  prev = prev->next;
#endif

}

void list::set_prev() {

  head = head->prev;
#if 0
  next = head;
  head = prev;
  prev = head->prev;
#endif

}

/**********
 * Append *
 **********/

void list::append(robot *rob) {

  if (N == 0) {

    head = rob;

    head->prev = rob;
    head->next = rob;

  } else {

    rob->next = head->next;
    rob->prev = head;
    head = head->next = head->next->prev = rob;

  }

#if 0
  next = head->next;
  prev = head->prev;
#endif

  N++;

}

/**********
 * remove *
 **********/

void list::remove() {

  if (N <= 0)
    return;

  robot *rob = head;

  N--;

  head = head->prev;
  head->next = head->next->next;
  head->next->prev = head;

#if 0
  prev = head->prev;
  next = head->next;
#endif

  delete rob;

  std::cout << "deleted " << rob << std::endl;

}

/*********
 * clear *
 *********/

void list::clear() {

  while (N > 0) {

    this->remove();

  }

}

/*********
 * Print *
 *********/

void list::print() {

  robot *plc = head;

  do {

    std::cout << plc << std::endl;

    plc = plc->next;

  } while (plc != head);

}
