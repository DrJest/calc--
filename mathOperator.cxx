#include "mathOperator.hpp"
#include "mathNumber.hpp"
#include <cmath>
#include <string>
#include <sstream>
#include <QTextStream>

mathOperator::mathOperator() {
}

mathOperator::~mathOperator() {
}

mathOperator::mathOperator(char source) {
  QString s(source);
  this->_source = s;
  this->_type = "operator";
}

mathOperator::mathOperator(QString source) {
  this->_source = source;
  this->_type = "operator";
}

mathEntity* mathOperator::apply(mathEntity& first, mathEntity& second) {
  double f = first.eval(), s = second.eval(), r=0;
  if(this->_source=="+") {
    r = f+s;
  }
  else if(this->_source=="-") {
    r = f-s;
  }
  else if(this->_source=="x") {
    r = f*s;
  }
  else if(this->_source=="/") {
    r = f/s;
  }
  else if(this->_source=="%") {
    r = (int)f % (int)s;
  }
  else if(this->_source=="^") {
    r = pow(f,s);
  }
  mathEntity* ret = new mathNumber(QString::number(r));
  return ret;
}

mathEntity* mathOperator::apply(mathEntity& arg) {
  double f = arg.eval(), r=0;
  if(this->_source=="$0") {
    r = sqrt(f);
  }
  else if(this->_source=="$1") {
    r = sin(f);
  }
  mathEntity* ret = new mathNumber(QString::number(r));
  return ret;
}
