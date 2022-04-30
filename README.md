# codigoiot-refrigeracion

Este es un ejemplo sobre un sistema de control de refrigeramiento

Requisitos

- Sensor de temperatura y humedad 
- 3 Botones
- 2 Leds
- MCU Esp32 

Roles y Descripción

- Boton1: Manual. Activa la refrigeración al ser presionado 
- Boton2: Alta demanda 
- Boton3: Sobre carga de funcionamiento  
- Led1: Refrigeracion manual 
- Led2: Refrigeración automática  

Funcionamiento

Que se encienda la refrigeracion manual cada que se presione el boton de manual  

La refrigeracion manual tiene prioridad a la refrigeracion automática.  

Si la termperatura es alta (mayor a 28, por ejemplo), se activa la refrigeracion automática  

Si tengo alta demanda o sobre carga, se activa la refrigeración automática  

Si tengo alta demanda o sobrecarga de funcionamiento y ademas temperatura alta, se activan ambas refrigeraciones

![Maquina abstracta](https://github.com/eolandro/codigoiot-refrigeracion/blob/main/diagram/Diagrama.png)
