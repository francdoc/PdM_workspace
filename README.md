### Cohorte: CESE 23Co2024
```
Materia: Programación de Microprocesadores

Docente: Patricio Bos (@patriciobos)
```

#### PREGUNTAS PRÁCTICA 1

1) **¿De qué serviría usar un array de “leds” con la secuencia en el programa? ¿Qué pasa con nuestro programa si nos piden agregar/sacar/cambiar un led de la secuencia** 

    Una estructura de dato en forma de array de LEDs sirve para concentrar en 1 sólo lugar del código las decisiones de diseño relacionadas a cuántos LEDs utilizar. EN el programa desarrollado para la práctica (si se quiere modificar la secuencia) habría que cambiar en la sección de "Private variables" los arreglos "LED_sequence_1" y "LED_sequence_2". 
    
    #### Contexto
    ```
    https://github.com/francdoc/PdM_workspace/blob/main/Practica_1.2/Src/main.c#L51
    ```

2) **¿Cómo responde el programa a las pulsaciones, hay falsos positivos o pulsaciones no detectadas? ¿Se implementa alguna técnica de antirrebote de las pulsaciones?**

    Si se presiona 1 sóla vez (por un instante) el botón de usuario azul justo cuando el último LED3 de la secuencia terminó de hacer OFF, se invierte entonces la secuencia de "blink" y el orden de ejecución del "blink" pasa a ser LED3, LED2, LED1, LED3 (...).

    Si se mantiene apretado el botón azul durante la ejecución de la secuencia de "blink" {LED1, LED2, LED3, LED1 (...)} hasta que el LED3 termine de cumplir con el tiempo de OFF, entonces la función "get_btn_change" va a ser ejecutada y el estado del botón azul va a ser evaluado. Por lo cual la secuencia de "blink" se invierte y el orden pasaría a ser {LED3, LED2, LED1, LED3 (...)}: 

    #### Contexto
    ```
    https://github.com/francdoc/PdM_workspace/blob/main/Practica_1.2/Src/main.c#L108  
    
    https://github.com/francdoc/PdM_workspace/blob/main/Practica_1.2/Src/main.c#L198    
    ```

    Cualquier pulsación por fuera de los 2 casos detallados no va a ser detectada por el programa.

    El programa no cuenta actualmente con mecanismo antirrebote por software.

3) **¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar un led? ¿Qué diferencia hay entre estas alternativas? ¿Se puede cambiar el sentido de la secuencia en cualquier momento de la ejecución?**

    En este caso, el pulsador es leído luego de un ciclo completo de la secuencia. Es decir después de encender y apagar el LED3 cuando la secuencia es {LED1, LED2, LED3, LED1 (...)}.

    Si se quisiera leer el pulsador despúes de encender y apagar cualquier LED entonces habría que colocar la función "get_btn_change" dentro de "LED_sequence_blink". En particular luego de cada llamada a "blink_led". Pero aún haciendo esto se debería esperar a la ejecución completa de 1 "blink" individual.
    
    Lo mejor sería implementar una interrupción ISR sumado a un "sleep" no bloqueante para modificar instantáneamente el sentido de ejecución de la secuencia de "blink" sin tener que esperar a que un LED termine de parpadear por completo (ciclo on/off).

    Como está desarrollado el programa en este caso, no se puede cambiar el sentido de la secuencia en cualquier momento de la ejecución.

4) **¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido de cada led fuera sensiblemente más grande, 1 segundo por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?**

    Las reglas y comportamiento descrito anteriormente (para que haya inversión de secuencia de los LEDs) se mantiene igual pese al supuesto cambio en el tiempo de encendido de cada LED.

### Nota aclaratoria

Observé que podría haber utilizado las funciones "BSP_LED_On" y "BSP_LED_Off" de la HAL de STM para evitar la necesidad de gestionar el estado del LED mediante las llamadas a LED_toggle(led, ON) y LED_toggle(led, OFF) dentro de la función LED_blink.

#### Contexto
```
https://github.com/francdoc/PdM_workspace/blob/main/Practica_1.2/Src/main.c#L86

https://github.com/francdoc/PdM_workspace/blob/main/Practica_1.2/Src/main.c#L108    
```

#### PREGUNTAS PRÁCTICA 3

1) **¿Es suficientemente clara la consigna 2 o da lugar a implementaciones con distinto comportamiento?** 

    No queda en claro cuántos ciclos de parpeadeo se quiere para cada LED. Para el ejercicio 3.1.2 (que sintetiza el punto 3.1 y 3.2) lo dejé fijo en 1 ciclo para cada tiempo de parpeadeo de LED posible. Sin posibilidad de ser modificado. Para el ejercicio 3.3 lo dejé configurable como una variable MACRO (#define).

2) **¿Se puede cambiar el tiempo de encendido del led fácilmente en un solo lugar del código o éste está hardcodeado?**

    Está configurable como un vector de tiempos.

3)  **¿Hay números “mágicos” en el código?**

    En el ejercicio 3.1.2 sí. En el ejercicio 3.3 traté de darles contexto y significado a todos los magic numbers.

4) **¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código compile?** 

    ```
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>

    #include "stm32f4xx_hal.h"
    ```

5) **Si las funcionalidades de una API propia crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usen en la implementación, ¿Cuál sería el mejor lugar?.**

    Supongo que seguir trabajando dentro de la carpeta Drivers estaría bien.
    
6) **¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos esperados?**

    En la sección "Private define" y "Private variables" están todos los parámetros configurables para el usuario. Incluí control de parámetros en todas las funciones.

