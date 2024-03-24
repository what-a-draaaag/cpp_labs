#include "employees.h"
#include "bin_manip.h"

void do_cmd(std::string cmd, EmployeesArray& emp){
	if (cmd == "add"){
		emp.add();
		return;
	}
	if (cmd == "list"){
		emp.list();
		return;
	}
	if (cmd == "exit"){
		exit(0);
		return;
	}
	std::string filename;
	std::cin >> filename;
	if (cmd == "load"){
		emp.load(filename);
	}
	if (cmd == "save"){
		emp.save(filename);
	}
}

int main(){
	std::string cmd;
	EmployeesArray employees;
	while(std::cin){
		std::cin >> cmd;
		do_cmd(cmd, employees);
	}
}
