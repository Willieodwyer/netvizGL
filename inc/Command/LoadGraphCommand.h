//
// Created by werl on 12/01/17.
//

#ifndef NETVIZGL_LOADGRAPHCOMMAND_H
#define NETVIZGL_LOADGRAPHCOMMAND_H

#include "Command.h"
#include "../GLWindow.h"

class LoadGraphCommand : public Command {
private:
  GLWindow *window;
public:
    LoadGraphCommand(GLWindow *window);

public:
    void execute();
};

#endif //NETVIZGL_LOADGRAPHCOMMAND_H
