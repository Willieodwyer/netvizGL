//
// Created by werl on 12/01/17.
//

#ifndef NETVIZGL_LOADGRAPHCOMMAND_H
#define NETVIZGL_LOADGRAPHCOMMAND_H

#include "Command.h"
#include "../Window.h"

class LoadGraphCommand : Command{
 private:
   Window *window;

 public:
  void Execute();
};

#endif //NETVIZGL_LOADGRAPHCOMMAND_H
