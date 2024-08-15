### TP_FINAL_PCSE_CESE

**Trabajo Final**

- Materia: Programación de Microcontroladores
- Docente: Patricio Bos
- Alumno: Franco Chiesa Docampo
- Plataforma: NUCLEO-STM32F429ZI

**Descripción del Proyecto**

Este proyecto consiste en desarrollar un módulo de monitoreo de temperatura utilizando un sensor BME280 y una pantalla LCD para visualizar los datos. El sistema incluye las siguientes funcionalidades:

    1) Sensado de Temperatura: utilizando el sensor BME280.
    2) Visualización de Datos: a través de una pantalla LCD.
    3) Transmisión de Datos: el periférico UART del STM32 enviará los datos a una PC para visualizarlos mediante una terminal serie.
    4) Alerta de Temperatura: si la temperatura supera un umbral predefinido, se mostrará un mensaje de advertencia en la pantalla LCD.
    5) Tiempo: durante el funcionamiento del sistema se muestra en la pantalla LCD la fecha y la hora.

**Periféricos Utilizados**

    **UART**: Para la transmisión de datos hacia la PC.
    SPI: Comunicación con el sensor BME280.
    I2C: Interfaz con la pantalla LCD.