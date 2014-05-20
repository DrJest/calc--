#if !defined(MATHENTITY_HPP)

  #define MATHENTITY_HPP
  #include <QString>
  
  class mathEntity {
    public:
      bool isOperator();
      bool isNumber();
      bool hasDot();

      static bool isOperator(char);
      static bool isNumber(char);
      static bool isDot(char);
      
      virtual double eval()=0;
      QString getSource();
      
    protected:
      QString _source;
      QString _type;
      double _value;
  };

#endif
