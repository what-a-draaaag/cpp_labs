#include <string>
#include <map>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "matrix.h"

typedef std::map<int, Matrix*> var_storage;

int get_reg(std::string arg){
  return stoi(arg.substr(1,1));
}

int main(int, char **) {
  std::string cmd, arg1, arg2;
  var_storage vars;
  for (int i=0; i<10; i++){
    vars[i] = new Matrix(0,0);
  }

  while (std::cin) {
    try{
      std::cin >> cmd;
      if (cmd == "exit") {
        break;

      } else if (cmd == "elem") {
        std::size_t row, col;
        std::cin >> arg1 >> row >> col;
        int reg = get_reg(arg1);
        std::cout << vars[reg]->get(row, col) <<std::endl;

      } else if (cmd == "load") {
        std::string filename;
        std::cin >> arg1 >> filename;
        int reg = get_reg(arg1);
        vars[reg]->load(filename);

      } else if (cmd == "print") {
        std::cin >> arg1;
        int reg = get_reg(arg1);
        vars[reg]->print();

      }else if (cmd == "add") {
        std::cin >> arg1 >> arg2;
        int reg1 = get_reg(arg1);
        int reg2 = get_reg(arg2);
        *vars[reg1] += *vars[reg2];

      } else if (cmd == "mul") {
        std::cin >> arg1 >> arg2;
        int reg1 = get_reg(arg1);
        int reg2 = get_reg(arg2);
        *vars[reg1] *= *vars[reg2];
       }
      
    }
    catch (MatrixException& e){
      std::cout << e.what() << std::endl;
    }
}

  for (var_storage::iterator it = vars.begin(); it != vars.end(); ++it) {
    delete it->second;
  }
}
