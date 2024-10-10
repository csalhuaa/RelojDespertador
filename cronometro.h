#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <QWidget>
#include <QTimer>
#include <QTime>

namespace Ui {
class Cronometro;
}

/**
 * @class Cronometro
 * @brief Esta clase representa un cronómetro dentro de la aplicación.
 *
 * La clase Cronometro permite iniciar, detener, reiniciar y registrar marcas de tiempo,
 * además de manejar la actualización del tiempo transcurrido en pantalla.
 */
class Cronometro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase Cronometro.
     *
     * Inicializa el cronómetro y configura las conexiones necesarias.
     *
     * @param parent Puntero al widget padre (si existe). Por defecto es nullptr.
     */
    explicit Cronometro(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase Cronometro.
     *
     * Libera la memoria asignada a los objetos dinámicos.
     */
    ~Cronometro();

private slots:
    /**
     * @brief Inicia el cronómetro.
     *
     * Activa el temporizador que controla el tiempo transcurrido.
     */
    void iniciarCronometro();

    /**
     * @brief Detiene el cronómetro.
     *
     * Pausa el temporizador, deteniendo el aumento del tiempo transcurrido.
     */
    void detenerCronometro();

    /**
     * @brief Actualiza el tiempo mostrado en el cronómetro.
     *
     * Se llama periódicamente mediante el temporizador, aumentando el tiempo transcurrido
     * y actualizando la interfaz de usuario para reflejarlo.
     */
    void actualizarTiempo();

    /**
     * @brief Regresa a la ventana principal de la aplicación.
     *
     * Cierra la ventana del cronómetro y muestra la ventana principal.
     */
    void regresarVentanaPrincipal();

    /**
     * @brief Registra una marca de tiempo en el cronómetro.
     *
     * Almacena el tiempo actual en el que se hizo clic en el botón de registrar marca.
     */
    void registrarMarca();

    /**
     * @brief Reinicia el cronómetro.
     *
     * Pone el tiempo transcurrido a cero y detiene el cronómetro si estaba en ejecución.
     */
    void reiniciarCronometro();

private:
    Ui::Cronometro *ui;       ///< Puntero a la interfaz de usuario del cronómetro.
    QTimer *timer;            ///< Temporizador que actualiza el tiempo transcurrido.
    QTime tiempoTranscurrido; ///< Objeto que almacena el tiempo transcurrido desde el inicio del cronómetro.
    QTime tiempo;             ///< Objeto que maneja el tiempo actual del cronómetro.
};


#endif // CRONOMETRO_H
