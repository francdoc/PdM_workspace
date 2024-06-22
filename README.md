Preguntas asociadas al desarrollo de la práctica:

1) ¿De qué serviría usar un array de “leds” con la secuencia en el programa? ¿Qué pasa con nuestro programa si nos piden agregar/sacar/cambiar un led de la secuencia?

    Una estructura de dato en forma de array de LEDs sirve para concentrar en 1 sólo lugar del código las decisiones de diseño relacionadas a cuántos LEDs utilizar. Si se quiere modificar la secuencia habría que cambiar en la sección de "Private variables" los arreglos "LED_sequence_1" y "LED_sequence_2".

2) ¿Cómo responde el programa a las pulsaciones, hay falsos positivos o pulsaciones no detectadas? ¿Se implementa alguna técnica de antirrebote de las pulsaciones?

    Si se presiona 1 sóla vez (por un instante) el botón de usuario azul justo cuando el último LED3 de la secuencia terminó de hacer OFF, se invierte entonces la secuencia de "blink" y
    el orden de ejecución del "blink" pasa a ser LED3, LED2, LED1, LED3 (...).

    Si se mantiene apretado el botón azul durante la ejecución de la secuencia de "blink" {LED1, LED2, LED3, LED1 (...)} hasta que el LED3 termine de cumplir con el tiempo de OFF, entonces
    la función "get_btn_change" va a ser ejecutada y el estado del botón azul va a ser evaluado. Por lo cual la secuencia de "blink" se invierte y el orden pasaría a ser {LED3, LED2, LED1, LED3 (...)}.

    Cualquier pulsación por fuera de los 2 casos detallados no va a ser detectada por el programa.

3) ¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar un led? ¿Qué diferencia hay entre estas alternativas? ¿Se puede cambiar el sentido de la secuencia en cualquier momento de la ejecución?

    En este caso, el pulsador es leído luego de un ciclo completo de la secuencia. Es decir después de encender y apagar el LED3 cuando la secuencia es {LED1, LED2, LED3, LED1 (...)}.

    Si se quisiera leer el pulsador despúes de encender y apagar cualquier LED entonces habría que colocar la función "get_btn_change" dentro de "LED_sequence_blink". En particular luego de cada llamada a "blink_led". Pero aún haciendo esto se debería esperar a la ejecución completa de 1 "blink". Lo más eficiente sería implementar una interrupción ISR para modificar instantáneamente el sentido de ejecución de la secuencia de "blink" sin tener que esperar a que un LED termine de parpadear.

    Como está desarrollado el programa en este caso, no se puede cambiar el sentido de la secuencia en cualquier momento de la ejecución.

4) ¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido de cada led fuera sensiblemente más grande, 1 segundo por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?

    Las reglas descritas anteriormente para que haya inversión de secuencia de los LEDs se mantienen iguales pese al supuesto cambio en el tiempo de encendido de cada LED.

### Nota aclaratoria
Luego me di cuenta que podría haber usado la función "BSP_LED_On" perteneciente a la HAL de STM para evitar tener que manejar el estado del LED dentro de la función "LED_toggle".