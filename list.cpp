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
  head = next = prev = 0;
}

/**************
 * Destructor *
 **************/

list::~list() {

  while (head != 0) {
     delete head;
     head = next;
     next = head->next;
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

  next = next->next;
  head = head->next;
  prev = prev->next;

}

/**********
 * Append *
 **********/

void list::append(robot *rob) {

  if (head == 0) {

    head = next = prev = rob;

    // attach the robot

    rob->prev = prev;
    rob->next = next;

  } else {

    // attach the robot

    rob->prev = head;
    rob->next = next;

    // set the new position

    head->next = rob;

    head = rob;
    prev = rob->prev;
    next = rob->next;

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
