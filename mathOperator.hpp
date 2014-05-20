#if !defined(MATHOPERATOR_HPP)

  #define MATHOPERATOR_HPP

  #include <cmath>
  #include "mathEntity.hpp"
  
  class mathOperator :
    public mathEntity
  {
    public:
      mathOperator();
      mathOperator(char);
      mathOperator(QString);
      mathOperator(QString, bool);
      ~mathOperator();
      
      double eval() {
        if(this->_source=="-") return -1;
        if(this->_source=="+") return 2;
        if(this->_source=="x"||this->_source=="/"||this->_source=="%") return 1;
        return 0;
      }
      
      mathEntity* apply(mathEntity&, mathEntity&);
      mathEntity* apply(mathEntity&);
    
    protected:
  };

#endif
