#include "paintwidget.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include<QColorDialog>

paintWidget::paintWidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground);
}
void paintWidget::setShape(Shape shape)
{
    mShape = shape;
    update();
}
void paintWidget::paintEvent(QPaintEvent* event)
{
        static const QPoint points[4] =
        {
            QPoint(10, 80),  //
            QPoint(20, 10),  //
            QPoint(80, 30),  //
            QPoint(90, 70)   //
        };
        QRect rect(10,20,80,60);
        QRect rect2(10,10,80,80);
        int startAngle = 30*16;
        int arcLength = 120*16;

        QPainterPath path;
        path.moveTo(20,80);
        path.lineTo(20,30);
        path.cubicTo(QPoint(80,0),QPoint(50,50),QPoint(80,80));
        // 创建画家类的对象，参数为绘图设备。指定为this，表示在当前窗口绘制
        QPainter painter(this);
        painter.setPen(mPen);
        painter.setBrush(mBrush);
        painter.setRenderHint(QPainter::Antialiasing,this -> mAntialias);
        //qDebug()<<mAntialias;
        //painter.setBrush(QPixmap(":/src/软件小妹二维码.jpg"));
        for ( int x = 0; x < width(); x += 100 ) {
            for ( int y = 0; y < height(); y += 100 ) {
                // 先保存原来的状态
                // (0,0),(0,100),(0,200),(0,300)...(0,600)
                // (100,0),(100,100),(100,200),(100,300)...(100,600)
                // ...
                // (800,0),(800,100),(800,200),(800,300)...(800,600)
                painter.save();
                painter.translate(x, y);  // translate 修改的是坐标系
                if(mTransformation)
                {
                    painter.translate(50,50);
                    painter.rotate(90.0);
                    painter.scale(0.7,0.7);
                    painter.translate(-50,-50);
                }
                switch ( mShape ) {
                    // 点、线
                    case _Point:
                        painter.drawPoints(points, 4);
                        break;
                    case _Line:
                        painter.drawLine(points[0], points[2]);
                        break;
                    case _Polyline:
                        painter.drawPolyline(points, 4);
                        break;
                    case _Polygon:
                        painter.drawPolygon(points, 4);
                        break;
                    case _Rect:
                        painter.drawRect(rect);
                        break;
                    case _RoundedRect:
                        painter.drawRoundedRect(rect,25,25,Qt::RelativeSize);
                        break;
                    case _Ellipse:
                        painter.drawEllipse(QPoint(50,50),40,40);
                        break;
                    case _Arc:
                        painter.drawArc(rect2,startAngle,arcLength);
                        break;
                    case _Pie:
                        painter.drawPie(rect2,startAngle,arcLength);
                        break;
                    case _Chord:
                        painter.drawChord(rect2,startAngle,arcLength);
                        break;
                    case _Path:
                        painter.drawPath(path);
                        break;
                    case _Pixmap:
                        painter.drawPixmap(rect,QPixmap(":/test.jpg"));
                        break;
                    case _Text:
                        painter.drawText(rect,Qt::AlignCenter,"test");
                        break;
                }

                painter.restore();
            }
        }
}
void paintWidget::setTransformation(bool transformation)
{
    mTransformation = transformation;
    update();
}
void paintWidget::setAntialias(bool antialias)
{
    mAntialias = antialias;
    update();
}
void paintWidget::setBrush(QBrush brush)
{
    mBrush = brush;
    update();
}
void paintWidget::setPen(QPen pen)
{
    mPen = pen;
    update();
}
