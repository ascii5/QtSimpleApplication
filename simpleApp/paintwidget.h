#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include<QPen>
#include <QWidget>
enum Shape {
    _Point,         //
    _Line,          //

    _Rect,          //
    _RoundedRect,   //
    _Ellipse,       //

    _Polyline,      //
    _Polygon,       //

    _Arc,           //
    _Pie,           //
    _Chord,         //

    _Path,          //

    _Text,          //
    _Pixmap
};
class paintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit paintWidget(QWidget *parent = nullptr);
    void setShape(Shape);
    void paintEvent(QPaintEvent* event);
    void switchShape(Shape mShape,QPainter painter);
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void setAntialias(bool antilalias);
    void setTransformation(bool transformation);
signals:
private:
    Shape mShape;
    QPen mPen;
    QBrush mBrush;
    bool mAntialias;
    bool mTransformation;
};

#endif // PAINTWIDGET_H
