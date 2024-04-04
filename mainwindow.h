#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QFileInfo>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // Прототип слота для открытия файла;
    void openFile();
    // Прототип слота для наложения блюр эффекта;
    void blurFileWithValue();

private:
    // Переменная указывающая путь к файлу;
    QString pathToFile;
    // прототип метода отрисовки указанного файла в label;
    void paintPictureWithBlur(int value);
    // Прототип метода blur;
    QImage blurImage(QImage source, int value);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
