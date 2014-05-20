#include <QMainWindow>
#include <QTextStream>
#include <QApplication>
#include <QVector>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QMenu>
#include <QTextStream>
#include <QMap>
#include <QDesktopWidget>
#include <QWidget>
#include <QIcon>

#include "mainWindow.hpp"
#include "keyPad.hpp"

int main(int argc, char *argv[])
{    
    QApplication app(argc, argv);  
    
    mainWindow * window = new mainWindow;
    
    QDesktopWidget * dt = QApplication::desktop();

    keyPad * kb = new keyPad(window);
    
    window->setMainWidget<keyPad*>(kb);

    // set Height and Width of the main window
    int wHeight = 20 + 250 + 50; //navbar+keypad+results
    int wWidth  = 250;
    
    //centering the window
    int x,y;
    x = ( dt->width() - wWidth ) / 2;
    y = ( dt->height() - wHeight ) / 2;
       
    
    window->resize(wWidth, wHeight);
    window->move( x , y );    
    window->setWindowTitle("Calculator++");
    //window->setWindowIcon(QIcon("assets/icon.png"));   
    window->draw()->show();

    return app.exec();
}
