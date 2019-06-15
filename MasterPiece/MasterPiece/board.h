#ifndef BOARD_H
#define BOARD_H

#include <QWidget>

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    void checkFlag();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    void drawLineTo(const QPoint &endPoint);
    QImage image;
    int PenWidth;
    QColor PenColor;
    QPoint lastPoint;
    bool drawing;
    bool** bitmap;
};

#endif // BOARD_H
