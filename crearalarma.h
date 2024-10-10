// crearalarma.h
#ifndef CREARALARMA_H
#define CREARALARMA_H

#include <QDialog>
#include <QString>
#include "alarma.h"

namespace Ui {
class CrearAlarma;
}

/**
 * @brief La clase CrearAlarma permite al usuario crear y editar alarmas en un dialogo.
 */
class CrearAlarma : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase CrearAlarma.
     *
     * @param parent El widget padre de este dialogo (opcional).
     */
    explicit CrearAlarma(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase CrearAlarma.
     */
    ~CrearAlarma();

    /**
     * @brief Establece los detalles de una alarma existente para editar.
     *
     * @param alarma La alarma que se va a editar.
     */
    void setAlarma(const Alarma &alarma);

    /**
     * @brief Obtiene la alarma creada o editada.
     *
     * @return La alarma como un objeto de la clase Alarma.
     */
    Alarma getAlarma() const;

signals:
    /**
     * @brief Señal que se emite cuando se crea una nueva alarma.
     *
     * @param alarma La alarma creada.
     */
    void alarmaCreada(const Alarma &alarma);

private slots:
    /**
     * @brief Slot que se activa al crear una alarma.
     *
     * Este metodo recopila los datos de la interfaz de usuario y emite la señal
     * alarmaCreada con la nueva alarma.
     */
    void crearAlarma();

private:
    Ui::CrearAlarma *ui; ///< Puntero a la interfaz de usuario (UI) de CrearAlarma.
};

#endif // CREARALARMA_H
