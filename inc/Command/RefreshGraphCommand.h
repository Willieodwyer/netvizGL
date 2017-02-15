//
// Created by william on 15/02/17.
//

#ifndef NETVIZGL_REFRESHGRAPHCOMMAND_H
#define NETVIZGL_REFRESHGRAPHCOMMAND_H

#include "Command.h"
#include "../GLWindow.h"

class RefreshGraphCommand : Command {
 private:
  GLWindow *window;
 public:
  RefreshGraphCommand(GLWindow *window);

  void execute() override;
};

#endif //NETVIZGL_REFRESHGRAPHCOMMAND_H
