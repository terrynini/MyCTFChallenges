#include "masterpiece.h"
#include "ui_masterpiece.h"
#include <QBitmap>

MasterPiece::MasterPiece(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterPiece)
{
    ui->setupUi(this);
    ui->label->setMask(ui->label->pixmap()->mask());
}

MasterPiece::~MasterPiece()
{
    delete ui;
}

void MasterPiece::on_pushButton_clicked()
{
    ui->widget->checkFlag();
}
