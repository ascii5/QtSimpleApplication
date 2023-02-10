#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintwidget.h"
#include<QColorDialog>
#include<QPen>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        this -> setWindowTitle(QString("PainterX"));
        ui->cboShape->addItem("Point", static_cast<int>(_Point));
        ui->cboShape->addItem("Line", static_cast<int>(_Line));

        ui->cboShape->addItem("Rectangle", static_cast<int>(_Rect));
        ui->cboShape->addItem("Rounded Rectangle", static_cast<int>(_RoundedRect));
        ui->cboShape->addItem("Ellipse", static_cast<int>(_Ellipse));

        ui->cboShape->addItem("Arc", static_cast<int>(_Arc));
        ui->cboShape->addItem("Pie", static_cast<int>(_Pie));
        ui->cboShape->addItem("Chord", static_cast<int>(_Chord));

        ui->cboShape->addItem("Polyline", static_cast<int>(_Polyline));
        ui->cboShape->addItem("Polygon", static_cast<int>(_Polygon));

        ui->cboShape->addItem("Path", static_cast<int>(_Path));

        ui->cboShape->addItem("Text", static_cast<int>(_Text));
        ui->cboShape->addItem("Pixmap", static_cast<int>(_Pixmap));

        ui->sbPenWidth->setRange(1, 10);

            // 3. 线型
            // 3.1 线型-实线、虚线、点画线等
            ui->cboPenStyle->addItem("Solid", static_cast<int>(Qt::SolidLine));
            ui->cboPenStyle->addItem("Dash", static_cast<int>(Qt::DashLine));
            ui->cboPenStyle->addItem("Dot", static_cast<int>(Qt::DotLine));
            ui->cboPenStyle->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
            ui->cboPenStyle->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));
            ui->cboPenStyle->addItem("None", static_cast<int>(Qt::NoPen));

            // 3.2 线型-线的端点的样式
            ui->cboPenCap->addItem("Flat", static_cast<int>(Qt::FlatCap));
            ui->cboPenCap->addItem("Square", static_cast<int>(Qt::SquareCap));
            ui->cboPenCap->addItem("Round", static_cast<int>(Qt::RoundCap));

            // 3.3 连接-两根线的连接处的样式
            ui->cboPenJoin->addItem("Miter", static_cast<int>(Qt::MiterJoin));
            ui->cboPenJoin->addItem("Bevel", static_cast<int>(Qt::BevelJoin));
            ui->cboPenJoin->addItem("Round", static_cast<int>(Qt::RoundJoin));
            ui->cboBrushStyle->addItem(tr("Linear Gradient"), static_cast<int>(Qt::LinearGradientPattern));
                ui->cboBrushStyle->addItem(tr("Radial Gradient"), static_cast<int>(Qt::RadialGradientPattern));
                ui->cboBrushStyle->addItem(tr("Conical Gradient"), static_cast<int>(Qt::ConicalGradientPattern));
                ui->cboBrushStyle->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
                ui->cboBrushStyle->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
                ui->cboBrushStyle->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
                ui->cboBrushStyle->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
                ui->cboBrushStyle->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
                ui->cboBrushStyle->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
                ui->cboBrushStyle->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
                ui->cboBrushStyle->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
                ui->cboBrushStyle->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
                ui->cboBrushStyle->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
                ui->cboBrushStyle->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
                ui->cboBrushStyle->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
                ui->cboBrushStyle->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
                ui->cboBrushStyle->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
                ui->cboBrushStyle->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
                ui->cboBrushStyle->addItem(tr("None"), static_cast<int>(Qt::NoBrush));


           connect(ui -> cboShape,&QComboBox::activated,this,&MainWindow::shapChanged);
           // 画笔宽度
           connect(ui -> sbPenWidth, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
           // 画笔颜色
           connect(ui -> btnPenColor, SIGNAL(clicked()), this, SLOT(onBtnPenColorClicked()));
           // 画笔样式
           connect(ui -> cboPenStyle, SIGNAL(activated(int)), this, SLOT(penChanged()));
           // 画笔末端
           connect(ui -> cboPenCap, SIGNAL(activated(int)), this, SLOT(penChanged()));
           // 画笔连接
           connect(ui -> cboPenJoin, SIGNAL(activated(int)), this, SLOT(penChanged()));
           //画刷颜色
           connect(ui -> btnBrushColor,SIGNAL(clicked(bool)),this,SLOT(onBtnBrushColorClicked()));
           //画刷样式
           connect(ui -> cboBrushStyle,SIGNAL(activated(int)),this,SLOT(brushChanged()));

           connect(ui -> chkAntialiasing,&QCheckBox::toggled,this,&MainWindow::antialiasingChange);
           connect(ui -> chkTransformation,&QCheckBox::toggled,this,&MainWindow::transformationChanged);
           //画笔颜色按钮颜色初始化
           QPalette pal = ui -> btnPenColor ->palette();
           pal.setColor(QPalette::Button,QColor(253,34,0));
           ui -> btnPenColor ->setPalette(pal);
           ui -> btnPenColor -> setAutoFillBackground(true);
           ui -> btnPenColor -> setFlat(true);

           ui -> sbPenWidth -> setValue(5);
           penChanged();

           //画刷颜色初始化
           ui -> btnBrushColor -> setPalette(pal);
           ui -> btnBrushColor -> setAutoFillBackground(true);
           ui -> btnBrushColor -> setFlat(true);
           brushChanged();

}
void MainWindow::transformationChanged(void)
{
    ui -> paintwidget -> setTransformation(ui -> chkTransformation -> isChecked());
}
void MainWindow::antialiasingChange(void)
{
    ui ->paintwidget -> setAntialias(ui -> chkAntialiasing->isChecked());
    //qDebug()<<"isChecked:"<<ui -> chkAntialiasing->isChecked();
}
void MainWindow::onBtnBrushColorClicked(void)
{
    QColor color = QColorDialog::getColor(QColor(255,0,0),this,"选取颜色");
    if(!color.isValid())
        return;

    QPalette pal = ui -> btnBrushColor -> palette();
    pal.setColor(QPalette::Button,QColor(color));

    ui -> btnBrushColor -> setPalette(pal);
    ui -> btnPenColor -> setAutoFillBackground(true);
    ui -> btnPenColor -> setFlat(true);

    brushChanged();
}
void MainWindow::brushChanged(void)
{
    QColor color = ui -> btnBrushColor -> palette().color(QPalette::Button);

    int index = ui -> cboBrushStyle -> currentIndex();
    Qt::BrushStyle style = (Qt::BrushStyle)ui -> cboBrushStyle -> itemData(index).toInt();

    if(style == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0, 50, 100, 50);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, color);
        linearGradient.setColorAt(1.0, Qt::black);
        ui->paintwidget->setBrush(linearGradient);
    }
    else if ( style == Qt::RadialGradientPattern )
    {
        // 线径向渐变
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        ui->paintwidget->setBrush(radialGradient);
    }
    else if ( style == Qt::ConicalGradientPattern )
    {
        // 锥形渐变
        // QConicalGradient(qreal cx, qreal cy, qreal startAngle)
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);
        ui->paintwidget->setBrush(conicalGradient);
    }
    else if ( style == Qt::TexturePattern )
    {
        // 纹理样式
        ui->paintwidget->setBrush(QBrush(QPixmap(":/images/brick.png")));
    }
    else
    { // 其他
        ui->paintwidget->setBrush(QBrush(color, style));
    }
}
void MainWindow::penChanged(void)
{
    int width = ui -> sbPenWidth -> value();

    QColor color = ui -> btnPenColor ->palette().color(QPalette::Button);

    int styleIndex = ui -> cboPenStyle ->currentIndex();
    Qt::PenStyle style = (Qt::PenStyle)ui -> cboPenStyle ->itemData(styleIndex).toInt();

    int capIndex = ui -> cboPenCap -> currentIndex();
    Qt::PenCapStyle cap = (Qt::PenCapStyle)ui -> cboPenCap -> itemData(capIndex).toInt();

    int joinIndex = ui -> cboPenJoin -> currentIndex();
    Qt::PenJoinStyle join = (Qt::PenJoinStyle)ui -> cboPenJoin -> itemData(joinIndex).toInt();

    ui -> paintwidget -> setPen(QPen(color,width,style,cap,join));
}
void MainWindow::onBtnPenColorClicked(void)
{
    QColor color = QColorDialog::getColor(QColor(255,0,0),this,"选取颜色");
    if(!color.isValid())
            return;
    QPalette pal = ui -> btnPenColor -> palette();
    pal.setColor(QPalette::Button,color);
    ui -> btnPenColor -> setPalette(pal);
    ui -> btnPenColor -> setAutoFillBackground(true);
    ui -> btnPenColor -> setFlat(true);

    penChanged();
}
void MainWindow::shapChanged(void)
{
    int index = ui -> cboShape ->currentIndex();
    Shape shape = (Shape)ui -> cboShape ->itemData(index).toInt();
    ui -> paintwidget ->setShape(shape);
}
MainWindow::~MainWindow()
{
    delete ui;
}
