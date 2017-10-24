#include "toolbar.h"

ToolBar::ToolBar(QWidget * parent)
{
    setStyleSheet("QToolButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                  "stop: 0 #dadbde, stop: 1 #f6f7fa);}");
}

void ToolBar::addDockWidget() {

}
QToolButton* addButton(const QString &_text)
{

}
