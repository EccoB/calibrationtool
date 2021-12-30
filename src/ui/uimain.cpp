#include "uimain.h"
#include "./ui_uimain.h"
#include "userstrings.h"


#include <QScreen>
#include <QImageReader>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
//------
#include <string>
#include <src/ui/imageview.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

//const string uiWrongImageHeader="File not supported";
//const string uiWrongImageText="The File %1 you chose is not supported. Error %2";

//------ Are here to make a shortcut, istead of loading it from a file (which can be later done, I define it here ---
#define C_FX 3751.937744140625d
#define C_FY 3821.9775390625d
#define C_CX    1280
#define C_CY    960
//
#define k1  -1.2093325853347778
#define k2  -1.041786551475525
#define k3  -0.004819112829864025
#define p1  -0.0027203019708395004
#define p2  64.01393127441406
#define k4  -0.5568028688430786
#define k5  -3.6638600826263428
#define k6  78.03067016601562


/**
 * @brief UImain::UImain GUI that interacts with the user, lets him load an image, scales it, put in 2D-points of the image and shows the calculated results
 * @param parent
 */
UImain::UImain(const UserStrings &ustr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UImain),uStrings(ustr)
{
    ui->setupUi(this);

    solution.setRefreshedImageCallback(
                [this](const cv::Mat &m) { return this->updateImageM(m); });
    setDefaultSettings();

}



/**
 * @brief UImain::setDefaultSettings sets the Default settings of the ImageView-GUI such as size and color settings
 */
void UImain::setDefaultSettings(){

    resize(QGuiApplication::primaryScreen()->availableSize()*3/5);
    //-- Create the imageView
    imageUserL=new imageView(this);
    imageUserL->setScaledContents(false);
    ui->scrollArea->setWidget(imageUserL);
    //ui->scrollArea->layout()->addWidget(imageUserL);
    connect(imageUserL,&imageView::mouseEvent,this,&UImain::imageclicked);
}

/**
 * @brief UImain::updateImage sets a new image and displays it to the user
 * @param img
 */
void UImain::updateImage(const QImage &img)
{
    image = img;    //we copy the image
    imageUserL->setPixmap(QPixmap::fromImage(image));
    imageUserL->adjustSize();

    //At the sime time, we upate the labels, should be done more elgant in a later program to avoid unnecessary rewrites
    if(solution.getSolutionValid()){
        QString text=QString("x:%1 y:%2 z:%3").arg(solution.getPositionOfObject().x).arg(solution.getPositionOfObject().y).arg(solution.getPositionOfObject().z);
        ui->lPositionCam->setText(text);
        ui->lPositionCam->setStyleSheet("QLabel { background-color : green; }");
    }
}

/**
 * @brief UImain::updateImage sets an image and displays it to the user
 * @param img
 */
void UImain::updateImageM(const cv::Mat &img)
{
    updateImage(QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped());
}

UImain::~UImain()
{
    delete ui;
}


/**
 * @brief UImain::createPoint creates a new Point
 * @param x [pxl] coordinate from up left
 * @param y [pxl] coordinate from up left
 */
void UImain::createPoint(int x, int y){
    // I intentionally do not want the main window to draw anything except the image to
    // shift the computing power to the other classes (enables later video display, ect.)
    solution.addPoint(x,y);

}

/**
 * @brief UImain::imageclicked Slot called when the user clicks at any position in the image
 * @param event QMouseEvent with the position and pressed button
 */
void UImain::imageclicked(QMouseEvent *event){
    if(event->type()==QEvent::MouseButtonPress){
        switch (event->button()) {
        case Qt::LeftButton:
            this->createPoint(event->pos().rx(),event->pos().ry());
            break;
        default:
            qDebug()<<"No task for button "<<event->button();
            break;
        }
    }
}


void UImain::scaleImage(double factor)
{
    /*
    scaleFactor *= factor;
    ui->imageUserL->resize(scaleFactor * ui->imageUserL->pixmap(Qt::ReturnByValue).size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
    */
}

/**
 * @brief UImain::LoadFile loads an Image that than will be displayed and can be edited by the user
 * @param fileName path to the file
 * @return Wether opening the file was successfull
 */
bool UImain::loadFile(const QString &fileName){
    qDebug()<<"Trying to load file "<<fileName;

    //--- Load as QImage - deprecated ------
    QImageReader imageReader(fileName);
    imageReader.setAutoDetectImageFormat(true);
    imageReader.setAutoTransform(true);
    const QImage nImage = imageReader.read();
    if(nImage.isNull()){
        QMessageBox::information(this, uStrings.getUserString("uiWrongImageHeader").c_str(),tr(uStrings.getUserString("uiWrongImageText").c_str()).arg(QDir::toNativeSeparators(fileName),imageReader.errorString()));
        return false;
    }
    //updateImage(nImage);

    //------ Load as CV Image -----
    cv::Mat image = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);
    solution.setOriginalImage(image);
    updateImageM(image);

    return true;
}

void UImain::on_pushButton_clicked()
{
    QFileDialog dialog(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.jpeg *.JPG *.bmp)"));
    if(dialog.exec()){
        QStringList filenames= dialog.selectedFiles();
        if(filenames.length()==1)
            loadFile(filenames[0]);
    }
}

