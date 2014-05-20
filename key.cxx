#include "key.hpp"
#include "keyPad.hpp"

key::key()
{
}

key::key(QString label, QWidget* parent)
  : QPushButton(label, parent)
{
  this->_label = label;
  this->_parent = (keyPad*)parent;
}

QString key::getLabel() {
  return this->_label;
}

void key::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    if (this->_label == "=") {
      keyPad* t = (keyPad*) this->_parent;
      t->eval();
      return;
    }
    keyPad* t = (keyPad*) this->_parent;
    t->append(this->_label);
  } else {
    QWidget::mousePressEvent(event);
  }
}
