#include "mathEntity.hpp"
bool mathEntity::isOperator() {
  return this->_type=="operator";
}
bool mathEntity::isNumber() {
  return this->_type=="number" || this->_type=="dnumber";
}
bool mathEntity::hasDot() {
  return this->_type=="dnumber";
}
bool mathEntity::isOperator(char cur) {
  QString ops = "+-x/%^";
  return ops.indexOf(cur)>-1;
}
bool mathEntity::isNumber(char cur) {
  return '0'<=cur && cur<='9';
}
bool mathEntity::isDot(char cur) {
  return cur=='.';
}

QString mathEntity::getSource() {
  return this->_source;
}
