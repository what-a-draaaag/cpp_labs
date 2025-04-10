#pragma once

#include <stdint.h>
#include <fstream>
#include <string>
#include <cstdint>
#include <iostream>
#include <vector>




class Employee{
public:
  virtual int salary() const = 0;
  virtual int get_type() const = 0;
  virtual std::string get_type_name() const = 0;

  friend std::istream& operator>>(std::istream& in, Employee& emp);
  friend std::ostream& operator<<(std::ostream& out, const Employee& emp);
  friend std::ifstream& operator>>(std::ifstream& in, Employee& emp);
  friend std::ofstream& operator<<(std::ofstream& out, const Employee& emp);

  virtual void write_text(std::ostream& out) const;
  virtual void write_bin(std::ofstream& out) const;
  virtual void read_text(std::istream& in);
  virtual void read_bin(std::ifstream& in);

protected:
  std::string _name;
  int32_t _base_salary;
};



class Developer: public Employee {
public:
  virtual int salary() const override;
  virtual int get_type() const override;
  virtual std::string get_type_name() const override;

  virtual void write_text(std::ostream& out) const override;
  virtual void write_bin(std::ofstream& out) const override;
  virtual void read_text(std::istream& in) override;
  virtual void read_bin(std::ifstream& in) override;
private:
  bool _has_bonus;
};



class SalesManager: public Employee {
public:
  virtual int salary() const override;
  virtual int get_type() const override;
  virtual std::string get_type_name() const override;

  virtual void write_text(std::ostream& out) const override;
  virtual void write_bin(std::ofstream& out) const override;
  virtual void read_text(std::istream& in) override;
  virtual void read_bin(std::ifstream& in) override;
  
private:
  int32_t _sold_nm, _price;
};



class EmployeesArray {
public:
  void add(const Employee* emp);
  int total_salary() const;
  ~EmployeesArray();

  void add();
  void list();
  void load(std::string filename);
  void save(std::string filename);

  void read_new_emp(std::ifstream& in);
  Employee* make_employee(int type);
private:
  std::vector<Employee*> _employees;
};
