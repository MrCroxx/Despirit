#ifndef SHORTCUTPIXMAP_H
#define SHORTCUTPIXMAP_H
#include <QPixmap>
#include <QMouseEvent>

class ShortcutPixmap : public QPixmap
{
    Q_OBJECT
public:
    ShortcutPixmap();
protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // SHORTCUTPIXMAP_H
