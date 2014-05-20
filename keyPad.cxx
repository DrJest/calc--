#include "keyPad.hpp"
#include <iostream>
#include <string>
#include <sstream>

keyPad::keyPad(QWidget *parent)
  : QWidget(parent)
{
  int l = 50;
  for(int i = 0; i<9; ++i) {
    key* tmp = new key(QString::number(9-i), this);
    int top =  l * (i/3),
        left = l * (i%3);
    tmp->setGeometry(left, top, l, l);
  }
  key* zero = new key("0",this);
  zero->setGeometry(l, 3*l, l, l);
  
  key* dot = new key(".",this);
  dot->setGeometry(0, 3*l, l, l);
  
  key* equal = new key("=",this);
  equal->setGeometry(2*l, 3*l, l, l);
  
  QString ops = "+-x/%^()";
  for(int i = 0; i<ops.length(); ++i) {
    key* tmp = new key(""+ops[i], this);
    int left =  l * (i/4) + 3*l,
        top = l * (i%4);
    tmp->setGeometry(left, top, l, l);
  }
  
  QTextEdit* formula = new QTextEdit(this);
  formula->setGeometry(0, 4*l, 5*l, l);
  this->_input = formula;
  
  this->_output = new QTextEdit(this);
  this->_output->setReadOnly(true);
  this->_output->setGeometry(0, 5*l, 5*l, l);
  this->_parser = new mathParser();
}

keyPad* keyPad::updateTopBar()
{
  return this;  
}


void keyPad::append(QString el) {
  this->_input->insertPlainText(el);
}

void keyPad::eval() {
  QString input = this->_input->toPlainText();
  QString res;
  try {
    double result = this->_parser->eval(input);
    res = QString::number(result);
  } 
  catch (const char* error) {
    res = error;
  }
  this->_output->setPlainText(res);
}
