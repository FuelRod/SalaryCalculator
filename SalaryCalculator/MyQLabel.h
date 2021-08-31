
#include <QObject>
#include <QLabel>
#include <QMessageBox>

class YourLabelClass : public QLabel{

signals:
    void myLabelClicked();       // Signal to emit

public slots:
    void slotLabelClicked();    // Slot which will consume signal

protected:
    bool event(QEvent *myEvent); // This method will give all kind of events on Label Widget
};
