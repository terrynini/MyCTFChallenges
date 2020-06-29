#ifndef MASTERPIECE_H
#define MASTERPIECE_H

#include <QMainWindow>

namespace Ui {
class MasterPiece;
}

class MasterPiece : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterPiece(QWidget *parent = nullptr);
    ~MasterPiece();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MasterPiece *ui;
};

#endif // MASTERPIECE_H
