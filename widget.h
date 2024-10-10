#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSoundEffect>
#include <QList>
#include "alarma.h"
#include "cronometro.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

/**
 * @brief La clase Widget es la interfaz principal de la aplicacion de alarmas.
 *
 * Gestiona la creacion, visualizacion, edicion y eliminacion de alarmas,
 * asi como la verificacion de las alarmas activas y la actualizacion de la
 * fecha y hora en la interfaz.
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Obtiene la única instancia de Widget (patrón Singleton).
     *
     * Si la instancia aún no ha sido creada, la crea y la devuelve.
     * De lo contrario, devuelve la instancia existente.
     *
     * @param parent El widget padre de la instancia de Widget.
     * @return Un puntero a la única instancia de Widget.
     */
    static Widget* getInstance(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase Widget.
     */
    ~Widget();

    /**
     * @brief Actualiza la fecha y hora mostradas en la interfaz.
     *
     * Esta funcion se llama periodicamente para mantener la
     * informacion actualizada.
     */
    void actualizarFechaHora();

    /**
     * @brief Actualiza la hora mostrada en la interfaz.
     *
     * Verifica si es el inicio de un nuevo minuto y llama a
     * la funcion de verificacion de alarmas si es necesario.
     */
    void actualizarHora();

private slots:
    /**
     * @brief Abre el dialogo para crear una nueva alarma.
     */
    void abrirCrearAlarma();

    /**
     * @brief Agrega una nueva alarma a la lista de alarmas.
     *
     * @param alarma La alarma que se va a agregar.
     */
    void agregarAlarma(const Alarma &alarma);

    /**
     * @brief Verifica si alguna de las alarmas activas debe sonar.
     *
     * Esta funcion se llama cada minuto para comprobar si
     * las alarmas coinciden con la hora actual.
     */
    void verificarAlarmas();

    /**
     * @brief Abre el dialogo para editar una alarma existente.
     *
     * @param index El indice de la alarma en la lista de alarmas.
     */
    void editarAlarma(int index);

    /**
     * @brief Elimina una alarma de la lista de alarmas.
     *
     * @param index El indice de la alarma a eliminar.
     */
    void eliminarAlarma(int index);

    /**
     * @brief Actualiza la visualizacion de una alarma en la lista.
     *
     * @param index El indice de la alarma a actualizar.
     * @param alarma La nueva informacion de la alarma.
     */
    void actualizarWidgetAlarma(int index, const Alarma &alarma);

    /**
     * @brief Muestra la ventana de alarma cuando una alarma suena.
     *
     * @param index El indice de la alarma que esta sonando.
     * @param alarma La alarma que ha sonado.
     */
    void mostrarVentanaAlarma(int index, const Alarma &alarma);

    /**
     * @brief Abre la ventana del cronometro.
     *
     * Cierra la ventana actual y muestra la interfaz del cronometro.
     */
    void abrirCronometro();

    /**
     * @brief Guarda las alarmas en un archivo JSON.
     *
     * Serializa la lista de alarmas y las guarda en un archivo al
     * cerrar la aplicacion.
     */
    void guardarAlarmas();

    /**
     * @brief Carga las alarmas desde un archivo JSON.
     *
     * Deserializa las alarmas guardadas y las carga en la lista
     * al iniciar la aplicacion.
     */
    void cargarAlarmas();

private:
    /**
     * @brief Constructor privado de la clase Widget.
     *
     * Este constructor es privado para implementar el patrón Singleton.
     *
     * @param parent El widget padre de la instancia.
     */
    explicit Widget(QWidget *parent = nullptr);

    static Widget *instance;  ///< Instancia única de la clase Widget (Singleton)
    Ui::Widget *ui; ///< Puntero a la interfaz de usuario (UI) de Widget.
    QTimer *timer; ///< Puntero al temporizador que actualiza la hora.
    QSoundEffect *soundEffect; ///< Puntero al objeto de sonido que se reproduce durante las alarmas.
    QList<Alarma> alarmas; ///< Lista de alarmas activas en la aplicacion.
    Cronometro *cronometro; ///< Puntero a la ventana del cronometro

protected:
    /**
     * @brief Evento que se activa al cerrar la ventana
     *
     * Sobrescribe el evento closeEvent para ejecutar acciones
     * como guardar las alarmas al cerrar la aplicacion
     *
     * @param event El evento de cierre que está siendo procesado
     */
    void closeEvent(QCloseEvent *event) override;

};

#endif // WIDGET_H
