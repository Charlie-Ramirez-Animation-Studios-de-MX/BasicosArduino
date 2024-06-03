//Semaforo De Maquina de 3 estados Simplificado con Preferencia de Paso mediante Sensor Pullup y reset
// Definición de los pines para los LEDs
const int pinRojo = 13;
const int pinAmarillo = 12;
const int pinVerde = 11;

// Definición de los pines para los botones
const int pinReset = 2;
const int pinSensor = 3;

void setup() {
  // Configurar los pines de los LEDs como salidas
  pinMode(pinRojo, OUTPUT);
  pinMode(pinAmarillo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  
  // Configurar los pines de los botones como entradas con pull-up interno
  pinMode(pinReset, INPUT_PULLUP);
  pinMode(pinSensor, INPUT_PULLUP);

  // Inicializar los LEDs apagados
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinAmarillo, LOW);
  digitalWrite(pinVerde, LOW);
}

void loop() {
  // Verificar si se presiona el botón de reset (lógica invertida, activo bajo)
  if (digitalRead(pinReset) == LOW) {
    // Apagar todos los LEDs
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAmarillo, LOW);
    digitalWrite(pinVerde, LOW);

    // Esperar hasta que se libere el botón de reset
    while (digitalRead(pinReset) == LOW) {
      delay(10); // Pequeña demora para evitar un bucle ocupado
    }
    
    // Reiniciar el ciclo desde el estado verde
    return;
  }

  // Estado inicial: Luz verde encendida
  digitalWrite(pinVerde, HIGH);

  // Esperar hasta que el sensor sea activado (lógica invertida, activo bajo)
  while (digitalRead(pinSensor) == HIGH) {
    if (digitalRead(pinReset) == LOW) {
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinAmarillo, LOW);
      digitalWrite(pinVerde, LOW);
      while (digitalRead(pinReset) == LOW) {
        delay(10);
      }
      return;
    }
    delay(10); // Pequeña demora para evitar un bucle ocupado
  }

  // Contador de 5 segundos para cambiar a amarillo
  for (int i = 0; i < 50; i++) {
    if (digitalRead(pinReset) == LOW) {
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinAmarillo, LOW);
      digitalWrite(pinVerde, LOW);
      while (digitalRead(pinReset) == LOW) {
        delay(10);
      }
      return;
    }
    delay(100);
  }

  // Cambiar a amarillo durante 3 segundos
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAmarillo, HIGH);
  for (int i = 0; i < 30; i++) {
    if (digitalRead(pinReset) == LOW) {
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinAmarillo, LOW);
      digitalWrite(pinVerde, LOW);
      while (digitalRead(pinReset) == LOW) {
        delay(10);
      }
      return;
    }
    delay(100);
  }

  // Cambiar a rojo
  digitalWrite(pinAmarillo, LOW);
  digitalWrite(pinRojo, HIGH);

  // Esperar hasta que el sensor sea desactivado (lógica invertida, activo bajo)
  while (digitalRead(pinSensor) == LOW) {
    if (digitalRead(pinReset) == LOW) {
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinAmarillo, LOW);
      digitalWrite(pinVerde, LOW);
      while (digitalRead(pinReset) == LOW) {
        delay(10);
      }
      return;
    }
    delay(10); // Pequeña demora para evitar un bucle ocupado
  }

  // Contador de 5 segundos para volver a verde
  for (int i = 0; i < 50; i++) {
    if (digitalRead(pinSensor) == LOW) {
      i = 0; // Reiniciar el contador si el sensor se activa nuevamente
    }
    if (digitalRead(pinReset) == LOW) {
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinAmarillo, LOW);
      digitalWrite(pinVerde, LOW);
      while (digitalRead(pinReset) == LOW) {
        delay(10);
      }
      return;
    }
    delay(100);
  }

  // Cambiar a verde
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, HIGH);
}
