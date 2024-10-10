#ifndef ALARMA_H
#define ALARMA_H

#include <QString>

/**
 * @brief La clase Alarma representa una alarma con hora, minuto, nombre y estado (activo o inactivo).
 */
class Alarma
{
private:
    int hora;        ///< Hora en formato 24 horas (0-23).
    int minuto;      ///< Minuto de la alarma (0-59).
    QString nombre;  ///< Nombre o descripcion de la alarma.
    bool activo;     ///< Estado de la alarma, si esta activa o no.

public:
    /**
     * @brief Constructor de la clase Alarma.
     *
     * @param hora La hora en formato 24 horas (0-23).
     * @param minuto El minuto de la alarma (0-59).
     * @param nombre El nombre o descripcion de la alarma.
     * @param activo Indica si la alarma esta activa o no (por defecto es true).
     */
    Alarma(int hora, int minuto, const QString &nombre, bool activo = true);

    /**
     * @brief Obtiene la hora de la alarma.
     *
     * @return La hora de la alarma en formato 24 horas.
     */
    int getHora() const;

    /**
     * @brief Obtiene el minuto de la alarma.
     *
     * @return El minuto de la alarma.
     */
    int getMinuto() const;

    /**
     * @brief Verifica si la alarma esta activa.
     *
     * @return true si la alarma esta activa, false si no.
     */
    bool isActivo() const;

    /**
     * @brief Obtiene el nombre o descripcion de la alarma.
     *
     * @return El nombre de la alarma como QString.
     */
    QString getNombre() const;

    /**
     * @brief Activa la alarma.
     *
     * Cambia el estado de la alarma a activo.
     */
    void activar();

    /**
     * @brief Desactiva la alarma.
     *
     * Cambia el estado de la alarma a inactivo.
     */
    void desactivar();
};
#endif // ALARMA_H
