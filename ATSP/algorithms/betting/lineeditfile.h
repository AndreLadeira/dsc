#ifndef LINEEDITFILE_H
#define LINEEDITFILE_H

#include <QLineEdit>
#include <QMouseEvent>

class LineEditFile : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEditFile(QWidget *parent = nullptr);
    void mouseDoubleClickEvent(QMouseEvent *event);


signals:

public slots:
};

#endif // LINEEDITFILE_H
