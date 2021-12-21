#ifndef UIMAIN_H
#define UIMAIN_H

#include <QMainWindow>
#include "userstrings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UImain; }
QT_END_NAMESPACE

class UImain : public QMainWindow
{
    Q_OBJECT

public:
    UImain(const UserStrings &ustr, QWidget *parent = nullptr);
    void updateImage(const QImage &img);
    ~UImain();

    bool loadFile(const QString &fileName);
protected:
    void scaleImage(double factor);
private:
    Ui::UImain *ui;
    void setDefaultSettings();
    QImage image;       //ImageBuffer for displaying to the user
    const UserStrings& uStrings;
    };
#endif // UIMAIN_H
