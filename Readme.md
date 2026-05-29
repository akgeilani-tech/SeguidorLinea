# Robot Seguidor de Linea

Robot seguidor de línea basado en Arduino Nano, utilizando sensores analógicos QTR-8A, motores N20 y driver TB6612FNG.

El proyecto está desarrollado en lenguaje C/C++ usando Visual Studio Code + PlatformIO.

Diseñado para:

- seguimiento de línea negra sobre fondo blanco
- circuitos con curvas cerradas
- control opcional de alta velocidad (Habilitando la funcion FastPWM)
- estabilidad dinámica usando control PD
- arquitectura modular y escalable

---

## 1 - Características

- Control PID optimizado para line follower
- Lectura analógica de 8 sensores QTR
- Velocidad dinámica según curvatura
- Frenado automático en curvas
- Arquitectura modular orientada a objetos
- Timing preciso usando `micros()`
- Compatible con PlatformIO
- Optimizado para Arduino Nano AVR
- Calibración automática QTR
- filtro derivativo
- Preparado para futuras mejoras:
  - EEPROM
  - auto tuning
  - control adaptativo
  - detección de pérdida de línea

---

## 2 - Hardware utilizado

| Componente | Descripción |
| --- | --- |
| Arduino Nano | Microcontrolador principal |
| TB6612FNG | Driver dual puente H |
| QTR-8A | Sensor analógico de 8 canales |
| Motores N20 | Motores DC reductores |
| Batería LiPo 2S | Alimentación principal |
| Protoboard | Prototipo inicial |

---

## 3 - Arquitectura del proyecto

```text
SeguidorLinea/
│
├── include/
│   ├── Config.h
│   ├── Motor.h
│   ├── Motors.h
│   ├── PID.h
│   ├── Robot.h
│   └── Sensors.h
│
├── src/
│   ├── main.cpp
│   ├── Motor.cpp
│   ├── Motors.cpp
│   ├── PID.cpp
│   ├── Robot.cpp
│   └── Sensors.cpp
│
├── platformio.ini
│
└── README.md
```

---

## 4 - Conexiones

### Arduino Nano ↔ TB6612FNG

| Arduino Nano | TB6612FNG |
| --- | --- |
| D3 | PWMB |
| D4 | BIN2 |
| D5 | BIN1 |
| D6 | STBY |
| D7 | AIN1 |
| D8 | AIN2 |
| D9 | PWMA |
| 5V | VCC |
| GND | GND |

---

### TB6612FNG ↔ Motores

| TB6612FNG | Motor |
| --- | --- |
| A01 / A02 | Motor izquierdo |
| B01 / B02 | Motor derecho |

---

### Arduino Nano ↔ QTR-8A

| QTR-8A | Arduino Nano |
| --- | --- |
| OUT1 | A0 |
| OUT2 | A1 |
| OUT3 | A2 |
| OUT4 | A3 |
| OUT5 | A4 |
| OUT6 | A5 |
| OUT7 | A6 |
| OUT8 | A7 |
| VCC | 5V |
| GND | GND |
| IR | 5V |

---

### Alimentación

#### Recomendado

- Batería LiPo 2S
  - 7.4V nominal
  - 8.4V cargada

---

| Batería | Destino |
| --- | --- |
| + | VM TB6612FNG |
| + | VIN Arduino Nano |
| - | GND común |

---

## 5 - Protección y filtrado

### Capacitor principal

Entre:

- VM
- GND

Agregar:

- 470uF a 1000uF electrolítico
- 100nF cerámico

---

### Capacitores en motores

En cada motor N20:

- capacitor cerámico 100nF entre terminales

Esto reduce:

- ruido EMI
- glitches
- resets aleatorios
- lecturas falsas del QTR

---

## 6 - Configuración del sensor

### Altura recomendada

```text
3 mm
```

---

### Distancia eje ↔ sensores

```text
8 cm
```

Esto mejora:

- anticipación de curvas
- estabilidad
- capacidad de giro

---

## 7 - Control PID y velocidad

El robot utiliza un controlador PID.

### Parámetros actuales del PID

```cpp
#define KP             0.11f
#define KI             0.00f
#define KD             1.60f
```

---

### Velocidad dinámica

La velocidad disminuye automáticamente al entrar en curvas:

```cpp
dynamicSpeed =
    BASE_SPEED -
    (abs(error) * CURVE_FACTOR);
```

---

### Parámetros actuales de velocidad

```cpp
#define BASE_SPEED     120
#define CURVE_FACTOR   0.055f
```

---

### Loop de control

El sistema utiliza timing preciso basado en `micros()`:

```cpp
void loop()
{
    uint32_t now = micros();

    if(now - lastLoop >= LOOP_TIME_US)
    {
        lastLoop += LOOP_TIME_US;

        robot.update();
    }
}
```

---

### Frecuencia actual

```cpp
#define LOOP_TIME_US 1000
```

Resultado:

```text
1000 Hz
```

---

## 8 - Calibración de sensores

El sistema utiliza calibración automática QTR.

```cpp
void Sensors::calibrate()
{
    for(uint16_t i = 0; i < 400; i++)
    {
        qtr.calibrate();

        delayMicroseconds(1500);
    }
}
```

Durante la calibración:

- mover el robot manualmente
- cubrir línea negra y fondo blanco
- mover izquierda/derecha

---

### Indicador LED

El LED integrado del Nano puede utilizarse para:

- calibración en progreso (parpadea)
- calibración exitosa (queda encendido)
- error sensores (parpadea rápido)

---

## 9 - Compilación

### Requisitos

- Visual Studio Code
- PlatformIO

---

### Compilar

```bash
pio run
```

---

### Subir firmware

```bash
pio run --target upload
```

---

### Monitor serial

```bash
pio device monitor
```

---

### Configuración PlatformIO

```ini
[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino

upload_speed = 115200
monitor_speed = 115200
```

## 10 - Problemas comunes

### El robot “se vuelve loco” al iniciar

Posibles causas:

- ruido EMI
- STBY flotante
- calibración incorrecta
- alimentación inestable

### Solución recomendada

Agregar:

- pull-down 10kΩ en STBY
- capacitores
- delay inicial
- calibración estable

---

### El robot oscila demasiado

Posibles causas:

- KP muy alto
- KD muy bajo
- sensores demasiado altos
- ruido eléctrico

---

### El robot se sale en curvas

Posibles causas:

- exceso velocidad
- poca desaceleración dinámica
- sensores demasiado retrasados
- mala tracción

---

## 11 - Recomendaciones futuras

### Hardware

- PCB dedicada
- regulador independiente
- encoder motores
- chasis rígido
- ruedas de mayor adherencia

---

### Software

- filtro derivativo
- control adaptativo
- auto calibración
- detección pérdida línea
- perfiles de velocidad
- EEPROM

---

### Estado del proyecto

Actualmente:

- prototipo funcional
- seguimiento estable
- optimizado para curvas
- tuning en progreso

---

## 12 - Licencia

MIT License

---

### Autor

Desarrollado por:

Ing. Ahmed Kamil Geilani
