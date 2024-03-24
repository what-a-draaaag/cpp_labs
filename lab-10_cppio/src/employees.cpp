#include "employees.h"
#include "bin_manip.h"

EmployeesArray::~EmployeesArray(){
	for (int i = 0; i < _employees.size(); i++){
		delete _employees[i];
	}
}


//salary

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
  }

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
  }

int EmployeesArray::total_salary() const{
	int sum = 0;
	for (int i=0; i<_employees.size(); i++){
		sum += _employees[i]->salary();
	}
	return sum;
}



//get_type_name

std::string Developer::get_type_name() const{
	return "Developer";
}

std::string SalesManager::get_type_name() const{
	return "Sales Manager";
}


//get_type

int Developer::get_type() const{
	return 1;
}

int SalesManager::get_type() const{
	return 2;
}



//write_text

void Employee::write_text(std::ostream& out) const{
	out << "Name: " << _name << std::endl << "Base Salary: " << _base_salary << std::endl;
}

void Developer::write_text(std::ostream& out) const{
	Employee::write_text(out);
	out << "Has bonus: " << (_has_bonus? '+':'-') << std::endl;
}
void SalesManager::write_text(std::ostream& out) const{
	Employee::write_text(out);
	out << "Sold items: " << _sold_nm << std::endl << "Item price: " << _price << std::endl;
}



//write_bin

void Employee::write_bin(std::ofstream& out) const{
	out << write_c_str(_name) << write_le_int32(_base_salary);
}

void Developer::write_bin(std::ofstream& out) const{
	out << write_le_int32(1);
	Employee::write_bin(out);
	out << write_bool(_has_bonus);
}
void SalesManager::write_bin(std::ofstream& out) const{
	out << write_le_int32(2);
	Employee::write_bin(out);
	out << write_le_int32(_sold_nm) << write_le_int32(_price);
}



//read_text

void Employee::read_text(std::istream& in){
	std::cin >> _name >> _base_salary;
}

void Developer::read_text(std::istream& in){
	Employee::read_text(in);
	std::cin >> _has_bonus;
}

void SalesManager::read_text(std::istream& in){
	Employee::read_text(in);
	std::cin >> _sold_nm >> _price;
}



//read_bin

void Employee::read_bin(std::ifstream& in){
	in >> read_c_str(_name) >> read_le_int32(_base_salary);
}

void Developer::read_bin(std::ifstream& in){
	Employee::read_bin(in);
	in >> read_bool(_has_bonus);
}
void SalesManager::read_bin(std::ifstream& in){
	Employee::read_bin(in);
	in >> read_le_int32(_sold_nm) >> read_le_int32(_price);
}




//cmd


void EmployeesArray::add(){
	int type;
	std::cin >> type;
	Employee* new_emp;
	if (type == 1){
		new_emp = new Developer();
	}
	else{
		new_emp = new SalesManager();
	}
	new_emp->read_text(std::cin);
	_employees.push_back(new_emp);
}

void EmployeesArray::list(){
	for (int i=0; i<_employees.size(); i++){
		std::cout << i + 1 << ". " << _employees[i]->get_type_name()<< std::endl;
		std::cout << *_employees[i];
	}
	std::cout << "== Total salary: " << total_salary() << std::endl;
	std::cout << std::endl;
}
void EmployeesArray::load(std::string filename){
	std::ifstream in(filename, std::ios_base::binary);
	int32_t count;
  	in >> read_le_int32(count);
    for (int i=0; i<count; i++){
    	read_new_emp(in);
    }
   	in.close();
}
void EmployeesArray::save(std::string filename){
	std::ofstream out(filename, std::ios_base::binary | std::ios_base::out);
	out << write_le_int32(_employees.size());
    for (int i=0; i<_employees.size(); i++){
    	_employees[i]->write_bin(out);
    }
    out.close();
}



//read_new_emp


void EmployeesArray::read_new_emp(std::ifstream& in){
   	int type;
	in >> read_le_int32(type);
	Employee* new_emp;
	if (type == 1){
		new_emp = new Developer();
	}
	else{
		new_emp = new SalesManager();
	}
	in >> *new_emp;
	_employees.push_back(new_emp);
}





// >> << Employee

std::ostream& operator<<(std::ostream& out, const Employee& emp) {
    emp.write_text(out);
    return out;
}

std::istream& operator>>(std::istream& in, Employee& emp) {
    emp.read_text(in);
    return in;
}

std::ofstream& operator<<(std::ofstream& out, const Employee& emp) {
    emp.write_bin(out);
    return out;
}

std::ifstream& operator>>(std::ifstream& in, Employee& emp) {
    emp.read_bin(in);
    return in;
}