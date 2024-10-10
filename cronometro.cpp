#include "cronometro.h"
#include "ui_cronometro.h"
#include "widget.h"

Cronometro::Cronometro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cronometro),
    timer(new QTimer(this)),
    tiempoTranscurrido(0, 0, 0, 0),
    tiempo(0, 0, 0, 0)
{
    ui->setupUi(this);

    setWindowTitle("Cronometro");

    connect(timer, &QTimer::timeout, this, &Cronometro::actualizarTiempo);
    connect(ui->btnIniciar, &QPushButton::clicked, this, &Cronometro::iniciarCronometro);
    connect(ui->btnDetener, &QPushButton::clicked, this, &Cronometro::detenerCronometro);
    connect(ui->btnRegresar, &QPushButton::clicked, this, &Cronometro::regresarVentanaPrincipal);
    connect(ui->btnMarcar, &QPushButton::clicked, this, &Cronometro::registrarMarca);
    connect(ui->btnReiniciar, &QPushButton::clicked, this, &Cronometro::reiniciarCronometro);

    ui->btnDetener->setEnabled(false);
    ui->btnMarcar->setEnabled(false);
    ui->btnReiniciar->setEnabled(false);

    ui->tableWidgetMarcas->setColumnCount(2);
    ui->tableWidgetMarcas->setHorizontalHeaderLabels(QStringList() << "Marca" << "Tiempo Acumulado");
    ui->tableWidgetMarcas->horizontalHeader()->setStretchLastSection(false);
    ui->tableWidgetMarcas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    timer->setInterval(10);  // 10 ms = 0.01 segundos
}

void Cronometro::registrarMarca() {
    QString tiempoAcumuladoStr = tiempoTranscurrido.toString("hh:mm:ss.zz");
    QString tiempoStr = tiempo.toString("hh:mm:ss.zz");

    int rowCount = ui->tableWidgetMarcas->rowCount();

    ui->tableWidgetMarcas->insertRow(rowCount);

    ui->tableWidgetMarcas->setItem(rowCount, 0, new QTableWidgetItem(tiempoStr));
    tiempo.setHMS(0, 0, 0, 0);
    ui->tableWidgetMarcas->setItem(rowCount, 1, new QTableWidgetItem(tiempoAcumuladoStr));

    ui->tableWidgetMarcas->item(rowCount, 0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetMarcas->item(rowCount, 1)->setTextAlignment(Qt::AlignCenter);
}

void Cronometro::reiniciarCronometro() {
    timer->stop();
    tiempo.setHMS(0, 0, 0, 0);
    tiempoTranscurrido.setHMS(0, 0, 0, 0);
    ui->labelTiempo->setText("00:00:00.00");
    ui->tableWidgetMarcas->setRowCount(0);

    ui->btnRegresar->setEnabled(true);
    ui->btnIniciar->setEnabled(true);
    ui->btnDetener->setEnabled(false);
    ui->btnMarcar->setEnabled(false);
    ui->btnReiniciar->setEnabled(false);
}

Cronometro::~Cronometro()
{
    delete ui;
}

void Cronometro::iniciarCronometro() {
    if (!timer->isActive()) {
        timer->start();
        ui->btnRegresar->setEnabled(false);
        ui->btnIniciar->setEnabled(false);
        ui->btnDetener->setEnabled(true);
        ui->btnMarcar->setEnabled(true);
        ui->btnReiniciar->setEnabled(true);
    }
}

void Cronometro::detenerCronometro() {
    if (timer->isActive()) {
        timer->stop();

        ui->btnRegresar->setEnabled(true);
        ui->btnIniciar->setEnabled(true);
        ui->btnDetener->setEnabled(false);
        ui->btnMarcar->setEnabled(false);
        ui->btnReiniciar->setEnabled(true);
    }
}

void Cronometro::actualizarTiempo() {
     // Aumenta el tiempo en 10 ms
    tiempo = tiempo.addMSecs(10);
    tiempoTranscurrido = tiempoTranscurrido.addMSecs(10);

    QString tiempoStr = QString("%1:%2:%3.%4")
                            .arg(tiempoTranscurrido.hour(), 2, 10, QChar('0'))
                            .arg(tiempoTranscurrido.minute(), 2, 10, QChar('0'))
                            .arg(tiempoTranscurrido.second(), 2, 10, QChar('0'))
                            .arg(tiempoTranscurrido.msec() / 10, 2, 10, QChar('0'));

    ui->labelTiempo->setText(tiempoStr);
}

void Cronometro::regresarVentanaPrincipal() {
    Widget *widget = Widget::getInstance();
    widget->show();
    this->close();
}
