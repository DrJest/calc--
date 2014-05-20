#include "mathParser.hpp"
#include <iostream>
#include <QString>
#include <QRegExp>
#include <QMap>
#include <QTextStream>
#include <cmath>

mathParser::mathParser() {
  this->_source = "";
}

mathParser::mathParser(QString source) {

  try {
    this->_source = this->clear(source);
    this->_entities = this->parse(this->_source);
  }
  catch (const char* error) {
    std::cerr << error << std::endl;
  }
}

double mathParser::eval() {
  return this->eval(this->clear(this->_source));
}

double mathParser::eval(QString source) {
  source = this->clear(source);

  int start, end;
  QString inner;
  while(source.indexOf(QRegExp("\\{[^{}]+\\}"))>-1) {
    start = source.indexOf(QRegExp("\\{[^{}]+\\}"));
    end = source.indexOf("}", start);
    inner = source.mid(start+1, end-start);
    source = source.replace(QRegExp("\\{[^{}]+\\}"), QString::number(this->eval(inner)));
  }

  QVector<mathEntity*> ents = this->parse(source);
  mathOperator* op;

  // ^, sqrt, sin, cos
  for (int i = 0; i<ents.size(); ++i) {
    if(ents[i]->isOperator() && ents[i]->eval()==0) {
      op = (mathOperator*) ents[i];
      if(i+1>=ents.size())
        throw "Invalid Source";
      
      if(ents[i]->getSource()=="^") {
        if(i==0)
          throw "Invalid Source";
        mathEntity* t = op->apply(*ents[i-1],*ents[i+1]);
        ents.replace(i, t);
        ents.remove(i+1);
        ents.remove(i-1);
        i-=2;
      } else {
        mathEntity* t = op->apply(*ents[i+1]);
        ents.replace(i, t);
        ents.remove(i+1);
        i--;
      }
    }
  }

  // x, /, %
  for (int i = 0; i<ents.size(); ++i) {
    if(ents[i]->isOperator() && ents[i]->eval()==1) {
      if(i+1>=ents.size() || i==0 || !ents[i]->isNumber())
        throw "Invalid Source";
      op = (mathOperator*) ents[i];
      mathEntity* t = op->apply(*ents[i-1],*ents[i+1]);
      ents.replace(i, t);
      ents.remove(i+1);
      ents.remove(i-1);
      i-=2;
    }
  }

  // -
  for (int i = 0; i<ents.size(); ++i) {
    if(ents[i]->isOperator() && ents[i]->eval()==-1) {
      if(i+1>=ents.size() || !ents[i+1]->isNumber())
        throw "Invalid Source";
      QString o = ents[i+1]->getSource();
      mathEntity* t = new mathNumber("-"+o);
      ents.replace(i+1, t);
      if(i>0 && ents[i-1]->isNumber()) {
        mathEntity* p = new mathOperator('+');
        ents.replace(i, p);
      }
      else {
        ents.remove(i);
        i--;
      }
    }
  }
      
  // +
  for (int i = 0; i<ents.size(); ++i) {
    if(i==0) {
      ents.remove(i);
    }
    if(i>0 && ents[i]->isOperator() && ents[i]->eval()==2) {
      if(i+1>=ents.size())
        throw "Invalid Source";
      op = (mathOperator*) ents[i];
      mathEntity* t = op->apply(*ents[i-1],*ents[i+1]);
      ents.replace(i, t);
      ents.remove(i+1);
      ents.remove(i-1);
      i-=2;
    }
  }
  return ents[0]->eval();
}

QString mathParser::clear(QString source) {
  QString clearSource = source;
  clearSource = clearSource.replace(QRegExp("\\s"),""); //trim all spaces
  clearSource = clearSource.replace(QRegExp("x"),"*"); //
  clearSource = clearSource.replace(QRegExp(","),"."); //
  clearSource = clearSource.replace(QRegExp("[\\(\\[]"),"{")
                           .replace(QRegExp("[\\)\\]]"),"}");
  /** 
   * special functions
   */                           
  clearSource = clearSource.replace(QRegExp("sqrt"), "$0")
                           .replace(QRegExp("asin|arcsin"), "$1")
                           .replace(QRegExp("sin"), "$2")
                           .replace(QRegExp("acos|arcos"), "$3")
                           .replace(QRegExp("cos"), "$4")
                           .replace(QRegExp("atan|arctan"), "$5")
                           .replace(QRegExp("tan"), "$6")
                           .replace(QRegExp("exp"), "$7")
                           .replace(QRegExp("log"), "$8")
                           .replace(QRegExp("ln"), "$9")
                           .replace(QRegExp("e"), QString::number(exp(1.0)))    // M_E alongside with
                           .replace(QRegExp("PI"), QString::number(4*atan(1))); // M_PI are not available on not posix compliant platforms.

  clearSource = clearSource.replace(QRegExp("[a-zA-Z]"),"");
  clearSource = clearSource.replace(QRegExp("\\*"),"x");
  return clearSource;
}

QVector<mathEntity*> mathParser::parse(QString s) {
  QString source = clear(s);
  QVector<mathEntity*> entities;
  if(source=="")
    throw "Empty Source";
  int openBra = 0, closeBra = 0;
  entities.push_back(new mathOperator('+')); //I make sure last() contains something
  char current;
  for (int i=0; i<source.length(); ++i) {
    current = source[i].toLatin1();
      mathEntity* last = entities.last();
    if(mathEntity::isOperator(current)) {
      if(current=='{') {
        openBra++;
      }
      if(current=='}') {
        if(last->getSource()=="{")
          throw "Empty Brackets";
        closeBra++;
      }
      entities.push_back(new mathOperator(current));
    }
    else if(mathEntity::isNumber(current)) {
      if(last->isNumber()) {
        QString newSource = last->getSource() + current;
        mathEntity* newLast = new mathNumber(newSource);
        entities.replace(entities.size()-1, newLast);
      }
      else {
        entities.push_back(new mathNumber(current));
      }
    }
    else if(current=='.') {
      if(last->isNumber()) {
        if(last->hasDot()) 
          throw "Multiple dots in number";
        QString newSource = last->getSource() + current;
        mathEntity* newLast = new mathNumber(newSource);
        entities.replace(entities.size()-1, newLast);
      }
      else {
        entities.push_back(new mathNumber("0."));
      }
    }
    else if(current=='$') {
      mathEntity* newOp = new mathOperator("$"+source[++i]);
      entities.push_back(newOp);
    }
  }
  entities.remove(0);
  if(openBra!=closeBra) 
    throw "Mismatched Brackets";
    
  if(entities.isEmpty())
    throw "Empty Source";
    
  return entities;
}
