#include <src/ui/imageview.h>

imageView::imageView(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{

}

imageView::~imageView()
{

}

void imageView::mousePressEvent(QMouseEvent *event)
{
    emit mouseEvent(event);

}
