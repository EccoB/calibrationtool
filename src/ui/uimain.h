#ifndef UIMAIN_H
#define UIMAIN_H

#include <QMainWindow>
#include "userstrings.h"
#include <src/ui/imageview.h>
#include <opencv2/core/core.hpp>
#include <camerapose.h>

QT_BEGIN_NAMESPACE
namespace Ui { class UImain; }
QT_END_NAMESPACE

class UImain : public QMainWindow
{
    Q_OBJECT

public:
    UImain(const UserStrings &ustr, QWidget *parent = nullptr);
    void updateImage(const QImage &img);
    void updateImageM(const cv::Mat &img);
    ~UImain();

    bool loadFile(const QString &fileName);
protected:
    void scaleImage(double factor);
    void createPoint(int x, int y);
protected slots:
    void imageclicked(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pResetPoints_clicked();

private:
    Ui::UImain *ui;
    imageView *imageUserL;
    void setDefaultSettings();
    QImage image;       //ImageBuffer for displaying to the user
    const UserStrings& uStrings;
    CameraPose solution;

    };
#endif // UIMAIN_H
