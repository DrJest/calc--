#if !defined(KEYPAD_HPP)

  #define KEYPAD_HPP

  #include <QPushButton>
  #include <QWidget>
  #include <QTextStream>
  #include <QTextEdit>
  #include <QKeyEvent>
  #include <QMap>
  #include <QLabel>
  #include "key.hpp"
  #include "mathParser.hpp"
  
  class keyPad : public QWidget
  {
    Q_OBJECT
    
    public:
      keyPad(QWidget* = 0);
      ~keyPad() {};
      keyPad* updateTopBar();
      
      void append(QString);
      
      void eval();
      
    protected:

    private:
      mathParser* _parser;
      QString _label;
      QLabel* _topBar;
      QTextEdit* _input;
      QTextEdit* _output;
  };

#endif
