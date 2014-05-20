#include "mathNumber.hpp"

mathNumber::mathNumber() {
}

mathNumber::~mathNumber() {
}

mathNumber::mathNumber(char source) {
  QString s(source);
  this->_source = s;
  this->_type = "number";
}

mathNumber::mathNumber(QString source) {
  this->_source = source;
  if(source.indexOf(".")==-1)
    this->_type = "number";
  else
    this->_type = "dnumber";
}

double mathNumber::eval() {
  return this->_source.toDouble();
}

QString mathNumber::getSource() {
  return this->_source;
}
