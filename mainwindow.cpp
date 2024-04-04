#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Реализация слота открытия файла;
void MainWindow::openFile()
{
    // Открытие fileDialog, чтобы пользователь выбрал нужный файл.
    pathToFile = QFileDialog::getOpenFileName(this,
                                              "open file to blur",
                                              "",
                                              "format file (*.jpg)");

    // Проверка существует ли указанный файл;
    if (QFileInfo::exists(pathToFile))
        // Вызов метода отрисовки файла;
        paintPictureWithBlur(ui->horizontalSlider->value());
}

// Реализация слота который накладывает эффект блюр
// в зависимости от положения слайдера;
void MainWindow::blurFileWithValue()
// Вызов метода отрисовки файла;
{ paintPictureWithBlur(ui->horizontalSlider->value());}

// Реализация метода отрисовки файла в label;
void MainWindow::paintPictureWithBlur(int value)
{
    // Установка файла в label;
    ui->label->setPixmap(QPixmap::fromImage(blurImage(QImage(pathToFile), value).scaled(
        ui->label->width(), ui->label->height(), Qt::KeepAspectRatio)));
}

QImage MainWindow::blurImage(QImage source, int value)
{
    if (source.isNull()) return QImage();

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto* blur = new QGraphicsBlurEffect;

    blur->setBlurRadius(value);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);

    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);

    QPainter painter(&result);

    scene.render(&painter, QRectF(),
                 QRectF(0, 0, source.width(), source.height()));
    return result;
}
