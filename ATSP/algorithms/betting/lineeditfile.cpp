#include "lineeditfile.h"
#include <QFileDialog>

LineEditFile::LineEditFile(QWidget *parent):QLineEdit(parent)
{
}

void LineEditFile::mouseDoubleClickEvent(QMouseEvent *event)
{

    QString fname = QFileDialog::getOpenFileName(this,tr("Open TSP File"), ".",
                                 tr("TSP lib Files (*.atsp)"));
    this->setText(fname);
}
