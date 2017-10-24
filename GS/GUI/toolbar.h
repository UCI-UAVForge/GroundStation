#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QToolBar>
#include <QToolButton>

class ToolBar : public QToolBar
{
public:
   ToolBar(QWidget * parent = 0);

   void addDockWidget();
   QToolButton * addButton(const QString &_text);
};

#endif // TOOLBAR_H
