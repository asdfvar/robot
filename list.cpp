/*
 * Circular linked list
 */

#include "list.h"
#include <iostream>

class robot;

list::list() {
  head = next = prev = 0;
}

list::~list() {}

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

void list::print() {

  robot *plc = head;

  do {

    std::cout << plc << std::endl;

    plc = plc->next;

  } while (plc != head);

}
