#include "crearalarma.h"
#include "ui_crearalarma.h"
#include <QMessageBox>

CrearAlarma::CrearAlarma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CrearAlarma)
{
    ui->setupUi(this);

    setWindowTitle("Crear Alarma");

    ui->checkBoxActivo->setStyleSheet(
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

    connect(ui->btnCancelar, &QPushButton::clicked, this, &CrearAlarma::reject);
    connect(ui->btnCrearAlarma, &QPushButton::clicked, this, &CrearAlarma::crearAlarma);
}

CrearAlarma::~CrearAlarma()
{
    delete ui;
}

void CrearAlarma::setAlarma(const Alarma &alarma)
{
    ui->spinBoxHora->setValue(alarma.getHora());
    ui->spinBoxMinuto->setValue(alarma.getMinuto());
    ui->lineEditNombre->setText(alarma.getNombre());
    ui->checkBoxActivo->setChecked(alarma.isActivo());

    ui->btnCrearAlarma->setText("Guardar Cambios");
}

Alarma CrearAlarma::getAlarma() const
{
    int hora = ui->spinBoxHora->value();
    int minuto = ui->spinBoxMinuto->value();
    QString nombre = ui->lineEditNombre->text();
    bool activo = ui->checkBoxActivo->isChecked();

    return Alarma(hora, minuto, nombre, activo);
}

void CrearAlarma::crearAlarma()
{
    QString nombre = ui->lineEditNombre->text().trimmed();

    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Nombre invalido", "Por favor, ingresa un nombre para la alarma.");
        return;
    }

    Alarma nuevaAlarma = getAlarma();
    emit alarmaCreada(nuevaAlarma);
    accept();
}
