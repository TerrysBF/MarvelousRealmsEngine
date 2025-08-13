#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "ECS/Actor.h" // Sugerencia: usa / para portabilidad

/**
 * @brief Clase principal de la aplicación/juego.
 *
 * Se encarga de inicializar sistemas, correr el loop principal (update/render)
 * e iniciar el cierre ordenado liberando recursos. Usa TSharedPointer para
 * manejar memoria compartida de forma segura.
 *
 * Flujo típico:
 *  - run():
 *      - init()
 *      - while(window->isOpen()) { update(); render(); }
 *      - destroy()
 */
class BaseApp {
public:
  /// Constructor por defecto; no hace trabajo pesado (init se encarga de eso).
  BaseApp() = default;

  /// Destructor: debe garantizar liberar recursos. Se sugiere llamar destroy().
  ~BaseApp();

  /**
   * @brief Punto de entrada de la app.
   * @return Código de salida (0 = OK, distinto de 0 = error).
   *
   * Orquesta el ciclo de vida completo:
   *  - Llama a init().
   *  - Ejecuta el game loop (update/render) mientras la ventana siga abierta.
   *  - Al terminar, llama a destroy().
   */
  int run();

  /**
   * @brief Inicializa todos los subsistemas necesarios.
   * @return true si todo salió bien; false si falla algo (ej., crear ventana).
   *
   * Aquí es donde:
   *  - Creas la ventana (resolución, título, VSync).
   *  - Preparas recursos (texturas, shapes, actores).
   *  - Inicializas ImGui (si no lo hace Window internamente).
   */
  bool init();

  /**
   * @brief Actualiza la lógica del juego por frame.
   *
   * Típico contenido:
   *  - Procesar input/eventos.
   *  - Avanzar cronómetros (vueltas/tiempo de carrera).
   *  - Mover jugador y bots (Steering Behaviors: Seek/Arrive/Path Following).
   *  - Resolver colisiones sencillas.
   */
  void update();

  /**
   * @brief Dibuja la escena y el HUD por frame.
   *
   * Típico contenido:
   *  - window->clear();
   *  - dibujar sprites/shapes/escena.
   *  - dibujar HUD con ImGui (velocidad, vuelta, tiempo, mapa miniatura).
   *  - window->display();
   */
  void render();

  /**
   * @brief Libera recursos y apaga subsistemas.
   *
   * Asegura que los smart pointers se reseteen y que la ventana/ImGui
   * queden correctamente cerrados.
   */
  void destroy();

private:
  /// Ventana principal (wrapper de SFML).
  EngineUtilities::TSharedPointer<Window> m_windowPtr;

  /// Ejemplo de shape/entidad gráfica sencilla.
  EngineUtilities::TSharedPointer<CShape> m_shapePtr;

  /// Actor ECS (ej.: jugador o bot). Nota: nombre corregido.
  EngineUtilities::TSharedPointer<Actor> m_ACircle;
};
