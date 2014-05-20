#if !defined(MATHNUMBER_HPP)

  #define MATHNUMBER_HPP

  #include <cmath>
  #include "mathEntity.hpp"
  
  class mathNumber :
    public mathEntity
  {
    public:
      mathNumber();
      mathNumber(char);
      mathNumber(QString);
      ~mathNumber();
      
      double eval();
      QString getSource();
      
    protected:
  };

#endif

