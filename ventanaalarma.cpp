#include "ventanaalarma.h"
#include "ui_ventanaalarma.h"

VentanaAlarma::VentanaAlarma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VentanaAlarma)
{
    ui->setupUi(this);

    setWindowTitle("Alarma Sonando");

    configurarGif();
    configurarSonido();

    connect(ui->btnApagar, &QPushButton::clicked, this, &VentanaAlarma::apagarAlarma);
    connect(this, &QDialog::rejected, this, &VentanaAlarma::apagarAlarma);
}

VentanaAlarma::~VentanaAlarma()
{
    if (movie) {
        movie->stop();
        delete movie;
    }
    delete ui;
}

void VentanaAlarma::configurarGif()
{
    if (!ui->graphicsView->scene()) {
        ui->graphicsView->setScene(new QGraphicsScene(this));
    }

    movie = new QMovie(":/assets/pato.gif");
    if (!movie->isValid()) {
        qDebug() << "El GIF no se ha cargado correctamente.";
    }

    pixmapItem = new QGraphicsPixmapItem();
    ui->graphicsView->scene()->addItem(pixmapItem);

    connect(movie, &QMovie::frameChanged, this, [this]() {
        QPixmap scaledPixmap = movie->currentPixmap().scaled(ui->graphicsView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pixmapItem->setPixmap(scaledPixmap);
    });

    movie->start();
}

void VentanaAlarma::configurarSonido()
{
    soundEffect = new QSoundEffect(this);
    soundEffect->setSource(QUrl("qrc:/assets/alarma.wav"));
    soundEffect->setLoopCount(QSoundEffect::Infinite);
    soundEffect->play();
}

void VentanaAlarma::setDetallesAlarma(const QString &hora, const QString &nombre)
{
    ui->labelHora->setText("Hora: " + hora);
    ui->labelNombre->setText("Alarma: " + nombre);
}

void VentanaAlarma::apagarAlarma()
{
    if (soundEffect->isPlaying()) {
        soundEffect->stop();
    }

    accept();
}
