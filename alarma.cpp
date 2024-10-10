#include "alarma.h"

Alarma::Alarma(int hora, int minuto, const QString &nombre, bool activo)
    : hora(hora), minuto(minuto), nombre(nombre), activo(activo) {}

int Alarma::getHora() const { return hora; }
int Alarma::getMinuto() const { return minuto; }
bool Alarma::isActivo() const { return activo; }
QString Alarma::getNombre() const { return nombre; }

void Alarma::activar() { activo = true; }
void Alarma::desactivar() { activo = false; }

