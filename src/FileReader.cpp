//
// Created by werl on 14/11/16.
//

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "../inc/FileReader.h"
using namespace std;

std::string FileReader::openFile(string cmd) {
  string data;
  FILE *stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }

  std::ifstream file("temp");
  std::string line;

  if (file) {
    while (file >> std::ws && std::getline(file, line));

  } else
    std::cout << "Unable to open file.\n";

  system("rm temp");

  return line;
}
