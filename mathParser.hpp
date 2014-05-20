#if !defined(MATHPARSER_HPP)

  #define MATHPARSER_HPP
  #include <cmath>
  #include <QVector>
  #include "mathEntity.hpp"
  #include "mathOperator.hpp"
  #include "mathNumber.hpp"
  struct mathCouple {
    QVector<mathEntity*> entities;
    QString source;
  };

  class mathParser {
    public:
      mathParser();
      mathParser(QString);
      ~mathParser();
      
      QString clear(QString);
      QVector<mathEntity*> parse(QString);
      
      double eval();
      double eval(QString);
      
    private:
      QVector<mathEntity*> _entities;
      QString _source;
  };

#endif
