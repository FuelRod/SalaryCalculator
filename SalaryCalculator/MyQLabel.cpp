#include "MyQLabel.h"
#include "qDebug.h"


YourLabelClass :: YourLabelClass(QWidget* parent) : QLabel(parent) {
   connect(this, SIGNAL(myLabelClicked()), this, SLOT(slotLabelClicked()));
}
