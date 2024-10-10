#ifndef VENTANAALARMA_H
#define VENTANAALARMA_H

#include <QDialog>
#include <QDir>
#include <QSoundEffect>
#include <QGraphicsPixmapItem>
#include <QMovie>

namespace Ui {
class VentanaAlarma;
}

/**
 * @brief La clase VentanaAlarma muestra una ventana de dialogo cuando una alarma suena.
 *
 * Permite visualizar la hora y el nombre de la alarma, asi como gestionar la
 * reproduccion de un sonido y una animacion (GIF) asociados.
 */
class VentanaAlarma : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase VentanaAlarma.
     *
     * @param parent El widget padre de este dialogo (opcional).
     */
    explicit VentanaAlarma(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase VentanaAlarma.
     */
    ~VentanaAlarma();

    /**
     * @brief Establece los detalles de la alarma que esta sonando.
     *
     * @param hora La hora de la alarma.
     * @param nombre El nombre de la alarma.
     */
    void setDetallesAlarma(const QString &hora, const QString &nombre);

    /**
     * @brief Configura la animacion GIF que se mostrara en la ventana de alarma.
     */
    void configurarGif();

    /**
     * @brief Configura el sonido que se reproducira cuando suene la alarma.
     */
    void configurarSonido();

signals:
    /**
     * @brief Señal que se emite cuando la alarma ha sido apagada.
     */
    void alarmaApagada();

private slots:
    /**
     * @brief Slot que se activa para apagar la alarma.
     *
     * Este metodo detiene el sonido y cierra la ventana de alarma.
     */
    void apagarAlarma();

private:
    Ui::VentanaAlarma *ui; ///< Puntero a la interfaz de usuario (UI) de VentanaAlarma.
    QSoundEffect *soundEffect; ///< Puntero al objeto de sonido que se reproduce durante la alarma.
    QMovie *movie; ///< Puntero al objeto de pelicula que se utiliza para mostrar el GIF.
    QGraphicsPixmapItem *pixmapItem; ///< Puntero al item grafico que contiene el GIF.
};


#endif // VENTANAALARMA_H
