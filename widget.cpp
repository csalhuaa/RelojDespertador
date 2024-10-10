#include "widget.h"
#include "ui_widget.h"
#include "crearalarma.h"
#include "ventanaalarma.h"
#include <QDateTime>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QListWidgetItem>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QCloseEvent>
#include <QStandardPaths>

Widget* Widget::instance = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Aplicacion de Alarmas");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::actualizarHora);
    timer->start(1000);

    actualizarFechaHora();
    cargarAlarmas();

    connect(ui->btnCrear, &QPushButton::clicked, this, &Widget::abrirCrearAlarma);
    connect(ui->btnCronometro, &QPushButton::clicked, this, &Widget::abrirCronometro);
}

void Widget::closeEvent(QCloseEvent *event) {
    guardarAlarmas();
    event->accept();
}

Widget* Widget::getInstance(QWidget *parent) {
    if (instance == nullptr) {
        instance = new Widget(parent);  // Crear la instancia única si aún no existe
    }
    return instance;
}

void Widget::guardarAlarmas() {
    QJsonArray jsonArray;

    for (const Alarma &alarma : alarmas) {
        QJsonObject jsonAlarma;
        jsonAlarma["hora"] = alarma.getHora();
        jsonAlarma["minuto"] = alarma.getMinuto();
        jsonAlarma["nombre"] = alarma.getNombre();
        jsonAlarma["activo"] = alarma.isActivo();

        jsonArray.append(jsonAlarma);
    }

    QJsonDocument jsonDoc(jsonArray);

    QString ruta = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir directorio(ruta);

    if (!directorio.exists()) {
        directorio.mkpath(".");
    }

    QFile archivo(directorio.filePath("alarmas.json"));
    if (archivo.open(QIODevice::WriteOnly)) {
        archivo.write(jsonDoc.toJson());
        archivo.close();
    } else {
        qWarning("No se pudo abrir el archivo para escribir las alarmas.");
    }
}

void Widget::cargarAlarmas() {
    QString ruta = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile archivo(QDir(ruta).filePath("alarmas.json"));

    if (!archivo.open(QIODevice::ReadOnly)) {
        qWarning("No se pudo abrir el archivo para leer las alarmas.");
        return;
    }

    QByteArray contenido = archivo.readAll();
    archivo.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(contenido);
    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        qWarning("El formato del archivo JSON es incorrecto.");
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue &valor : jsonArray) {
        QJsonObject jsonAlarma = valor.toObject();

        int hora = jsonAlarma["hora"].toInt();
        int minuto = jsonAlarma["minuto"].toInt();
        QString nombre = jsonAlarma["nombre"].toString();
        bool activo = jsonAlarma["activo"].toBool();

        Alarma alarma(hora, minuto, nombre, activo);
        agregarAlarma(alarma);
    }
}


Widget::~Widget()
{
    delete ui;
}

void Widget::actualizarFechaHora() {
    QDateTime fechaHoraActual = QDateTime::currentDateTime();
    QString fechaActual = fechaHoraActual.toString("dddd, dd 'de' MMMM");
    ui->labelFecha->setText(fechaActual);
}

void Widget::actualizarHora() {
    QDateTime fechaHoraActual = QDateTime::currentDateTime();
    QString horaActual = fechaHoraActual.toString("hh:mm:ss");
    ui->labelHora->setText(horaActual);

    if (fechaHoraActual.time().second() == 0) {
        verificarAlarmas();
    }
}

void Widget::abrirCrearAlarma() {
    CrearAlarma *crearAlarma = new CrearAlarma(this);
    connect(crearAlarma, &CrearAlarma::alarmaCreada, this, &Widget::agregarAlarma);
    crearAlarma->exec();
}

void Widget::agregarAlarma(const Alarma &alarma) {
    QWidget *alarmaWidget = new QWidget();
    QGridLayout *layout = new QGridLayout(alarmaWidget);
    layout->setContentsMargins(5, 5, 5, 10);

    QString nombreAlarma = alarma.getNombre();
    if (nombreAlarma.length() > 30) {
        nombreAlarma = nombreAlarma.left(30) + "...";
    }

    // Crear un QLabel para el nombre de la alarma
    QLabel *labelNombre = new QLabel(nombreAlarma);
    labelNombre->setStyleSheet(
        "color:rgb(255, 126, 14);"
        "font-family: 'Segoe Print';"
        "font-size: 16px;"
        );

    // Crear un QLabel para la hora de la alarma
    QString horaTexto = QString("%1:%2")
                            .arg(alarma.getHora(), 2, 10, QChar('0'))
                            .arg(alarma.getMinuto(), 2, 10, QChar('0'));

    QLabel *labelHora = new QLabel(horaTexto);
    labelHora->setStyleSheet(
        "QLabel {"
        "font-size: 30px;"
        "color:rgb(255, 126, 14);"
        "font-family: 'Segoe Print';"
        "background-color: transparent;"
        "}"
        );

    QCheckBox *checkBox = new QCheckBox("");
    checkBox->setStyleSheet(
        "QCheckBox::indicator {"
        "width: 60px;"
        "height: 60px;"
        "}"
        "QCheckBox::indicator:checked {"
        "image: url(':/assets/toggle_on.png');"
        "}"
        "QCheckBox::indicator:unchecked {"
        "image: url(':/assets/toggle_off.png');"
        "}"
        );
    checkBox->setChecked(alarma.isActivo());

    QPushButton *btnEditar = new QPushButton("");
    QPushButton *btnEliminar = new QPushButton("");
    btnEditar->setStyleSheet(
        "QPushButton {"
        "color: #000;"
        "width: 40px;"
        "height: 40px;"
        "icon: url(':/assets/edit.png');"
        "}"
        );
    btnEditar->setIconSize(QSize(45, 45));

    btnEliminar->setStyleSheet(
        "QPushButton {"
        "color: #000;"
        "width: 40px;"
        "height: 40px;"
        "icon: url(':/assets/delete.png');"
        "}"
        );
    btnEliminar->setIconSize(QSize(45, 45));

    layout->addWidget(labelNombre, 0, 0);
    layout->addWidget(labelHora, 0, 1, Qt::AlignHCenter);
    layout->addWidget(checkBox, 0, 2, Qt::AlignRight);
    layout->addWidget(btnEditar, 0, 3, Qt::AlignRight);
    layout->addWidget(btnEliminar, 0, 4, Qt::AlignRight);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 0);
    layout->setColumnStretch(3, 0);
    layout->setColumnStretch(4, 0);

    // Crear un nuevo QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->listWidgetAlarmas);
    item->setSizeHint(alarmaWidget->sizeHint());

    ui->listWidgetAlarmas->addItem(item);
    ui->listWidgetAlarmas->setItemWidget(item, alarmaWidget);

    connect(checkBox, &QCheckBox::checkStateChanged, this, [=](int state) {
        int index = ui->listWidgetAlarmas->row(item);
        if (state == Qt::Checked) {
            alarmas[index].activar();
        } else {
            alarmas[index].desactivar();
        }
    });

    connect(btnEditar, &QPushButton::clicked, this, [=]() {
        editarAlarma(ui->listWidgetAlarmas->row(item));
    });

    connect(btnEliminar, &QPushButton::clicked, this, [=]() {
        eliminarAlarma(ui->listWidgetAlarmas->row(item));
    });

    alarmas.append(alarma);
}



void Widget::verificarAlarmas() {
    QTime currentTime = QTime::currentTime();

    for (int i = 0; i < alarmas.size(); ++i) {
        const Alarma &alarma = alarmas[i];

        if (!alarma.isActivo()) continue;

        QTime timeAlarma(alarma.getHora(), alarma.getMinuto());

        if (currentTime.hour() == timeAlarma.hour() && currentTime.minute() == timeAlarma.minute()) {
            mostrarVentanaAlarma(i, alarma);
        }
    }
}

void Widget::mostrarVentanaAlarma(int index, const Alarma &alarma) {
    VentanaAlarma *ventana = new VentanaAlarma(this);
    QString horaTexto = QString("%1:%2").arg(alarma.getHora(), 2, 10, QChar('0')).arg(alarma.getMinuto(), 2, 10, QChar('0'));
    ventana->setDetallesAlarma(horaTexto, alarma.getNombre());
    ventana->exec();

    alarmas[index].desactivar();

    actualizarWidgetAlarma(index, alarma);
}

void Widget::editarAlarma(int index) {
    if (index >= 0 && index < alarmas.size()) {
        CrearAlarma dialogoEditar(this);
        dialogoEditar.setWindowTitle("Editar Alarma");
        dialogoEditar.setAlarma(alarmas[index]);

        if (dialogoEditar.exec() == QDialog::Accepted) {
            Alarma alarmaEditada = dialogoEditar.getAlarma();
            alarmas[index] = alarmaEditada;

            actualizarWidgetAlarma(index, alarmaEditada);
        }
    }
}

void Widget::actualizarWidgetAlarma(int index, const Alarma &alarma) {
    QWidget *alarmaWidget = qobject_cast<QWidget*>(ui->listWidgetAlarmas->itemWidget(ui->listWidgetAlarmas->item(index)));

    if (alarmaWidget) {
        QGridLayout *layout = qobject_cast<QGridLayout*>(alarmaWidget->layout());

        if (layout) {
            QLabel *labelNombre = qobject_cast<QLabel*>(layout->itemAtPosition(0, 0)->widget());
            if (labelNombre) {
                QString nombreAlarma = alarma.getNombre();
                if (nombreAlarma.length() > 30) {
                    nombreAlarma = nombreAlarma.left(30) + "...";
                }
                labelNombre->setText(nombreAlarma);
            }

            QLabel *labelHora = qobject_cast<QLabel*>(layout->itemAtPosition(0, 1)->widget());
            if (labelHora) {
                QString horaTexto = QString("%1:%2")
                .arg(alarma.getHora(), 2, 10, QChar('0'))
                    .arg(alarma.getMinuto(), 2, 10, QChar('0'));
                labelHora->setText(horaTexto);
            }

            QCheckBox *checkBox = qobject_cast<QCheckBox*>(layout->itemAtPosition(0, 2)->widget());
            if (checkBox) {
                checkBox->setChecked(alarma.isActivo());
            }
        }
    }
}

void Widget::eliminarAlarma(int index) {
    if (index < 0 || index >= alarmas.size()) return;
    alarmas.removeAt(index);
    delete ui->listWidgetAlarmas->takeItem(index);
}

void Widget::abrirCronometro() {
    cronometro = new Cronometro();
    cronometro->setAttribute(Qt::WA_DeleteOnClose);
    cronometro->show();
    this->close();
}
