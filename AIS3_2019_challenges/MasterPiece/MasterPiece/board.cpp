#include "board.h"
#include "flag.h"
#include <QMessageBox>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>

Board::Board(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    PenWidth = 2;
    PenColor = Qt::black;
    drawing = false;
    image = QImage( 650,410, QImage::Format_Mono);
    bitmap = new bool*[image.height()];
    for( int row = 0 ; row < image.height() ; row++){
        bitmap[row] = new bool[image.width()];
    }
    image.fill(qRgb(255, 255, 255));
    update();
}
void Board::checkFlag(){
    bool pass = true;
    for( int row = 0 ; row < image.height() ; row++){
        for( int col = 0 ; col < image.width() ; col++){
            bitmap[row][col] =  image.pixelColor(col,row) == Qt::white;
        }
    }
    image.fill(qRgb(255, 255, 255));
    for( int row = 0 ; row < image.height() ; row++){
        for( int col = 0 ; col < image.width() ; col++){
            if( bitmap[row][col] != flag[row*image.width()+col]){
                pass = false;
                break;
            }
        }
    }
    //draw flag
    /*
    for( int row = 0 ; row < image.height() ; row++){
        for( int col = 0 ; col < image.width() ; col++){
            image.setPixel(col,row,flag[row*image.width()+col]);
        }
    }
    */
    if (!pass){
        QMessageBox::critical(NULL, "UhUh", "Bob Ross:\nThat is not the flag, that's your ugly ass", QMessageBox::Yes, QMessageBox::Yes);
    }else{
        QMessageBox::about(NULL, "Yeah!", "Bob Ross:\nYes, that the flag !!");
    }
    //test
    /*
    FILE* temp;
    temp = fopen("/Users/terrykitsune/Desktop/output.txt","w");
    for( int row = 0 ; row < image.height() ; row++){
        for( int col = 0 ; col < image.width() ; col++){
            fwrite(bitmap[row][col]==1?"1":"0",1,1,temp);
            fwrite(",",1,1,temp);
        }
    }
    fclose(temp);
    */
    update();
}

void Board::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
           lastPoint = event->pos();
           drawing = true;
       }
}
void Board::mouseMoveEvent(QMouseEvent *event){
    if ((event->buttons() & Qt::LeftButton) && drawing)
        drawLineTo(event->pos());
}

void Board::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && drawing) {
        drawLineTo(event->pos());
        drawing = false;
    }
}

void Board::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void Board::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(PenColor, PenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);

    int rad = (PenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}
