//
// Created by william on 24/01/17.
//

#ifndef NETVIZGL_TEXTNODECOMMAND_H
#define NETVIZGL_TEXTNODECOMMAND_H

#include "../GLWindow.h"
#include "Command.h"

class TextNodeCommand : public Command{
 private:
  GLWindow *window;
 public:
  TextNodeCommand(GLWindow *pWindow);
  void execute() override;
};

#endif //NETVIZGL_TEXTNODECOMMAND_H
