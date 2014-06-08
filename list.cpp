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
  N = 0;
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

void list::set_prev() {

  next = head;
  head = prev;
  prev = head->prev;

}

/**********
 * Append *
 **********/

void list::append(robot *rob) {

  N++;

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

/**********
 * remove *
 **********/

void list::remove() {

  robot *rob = head;

  N--;

  head = prev;
  prev = head->prev;
  head->next = next;

  delete rob;

  std::cout << "deleted "
    << rob << std::endl;

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
