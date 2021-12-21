#include "uimain.h"
#include "./ui_uimain.h"
#include "userstrings.h"


#include <QScreen>
#include <QImageReader>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QDebug>
//------
#include <string>
//const string uiWrongImageHeader="File not supported";
//const string uiWrongImageText="The File %1 you chose is not supported. Error %2";



/**
 * @brief UImain::UImain GUI that interacts with the user, lets him load an image, scales it, put in 2D-points of the image and shows the calculated results
 * @param parent
 */
UImain::UImain(const UserStrings &ustr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UImain),uStrings(ustr)
{
    ui->setupUi(this);
    setDefaultSettings();
}



/**
 * @brief UImain::setDefaultSettings sets the Default settings of the ImageView-GUI such as size and color settings
 */
void UImain::setDefaultSettings(){
    ui->imageUserL->setScaledContents(true);
    resize(QGuiApplication::primaryScreen()->availableSize()*3/5);
}

/**
 * @brief UImain::updateImage sets a new image and displays it to the user
 * @param img
 */
void UImain::updateImage(const QImage &img)
{
    image = img;    //we copy the image
    ui->imageUserL->setPixmap(QPixmap::fromImage(image));
    ui->imageUserL->adjustSize();
}

UImain::~UImain()
{
    delete ui;
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
    QImageReader imageReader(fileName);
    imageReader.setAutoDetectImageFormat(true);
    imageReader.setAutoTransform(true);
    const QImage nImage = imageReader.read();
    if(nImage.isNull()){
        QMessageBox::information(this, uStrings.getUserString("uiWrongImageHeader").c_str(),tr(uStrings.getUserString("uiWrongImageText").c_str()).arg(QDir::toNativeSeparators(fileName),imageReader.errorString()));
        return false;
    }
    updateImage(nImage);


    return true;
}
