#if !defined(KEY_HPP)
  #define KEY_HPP

  #include <QPushButton>
  #include <QTextStream>
  #include <QWidget>
  #include <QMouseEvent>

  class key : public QPushButton
  {
    Q_OBJECT
    
    public:
      key();
      key(QString, QWidget*);
      ~key(){};
      
      QString getLabel();
      
    protected:
      void mousePressEvent(QMouseEvent*);
    
    private:
      QString _label;
      QWidget* _parent;
  };

#endif

