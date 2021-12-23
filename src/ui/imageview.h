#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>

/**
 * @brief The imageView class extends the QLabel with the mousePressEvent to be able to detect the clicks on the image shown to the user
 */
class imageView : public QLabel
{
    Q_OBJECT
public:
    imageView();
    explicit imageView(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
   ~imageView();

signals:
    void mouseEvent(QMouseEvent* event);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // IMAGEVIEW_H
