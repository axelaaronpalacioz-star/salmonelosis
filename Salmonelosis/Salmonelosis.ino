
const int NUM_PREGUNTAS = 11;

const char* preguntas[NUM_PREGUNTAS] = {
  "1. Tienes diarrea?",
  "2. Tienes dolor abdominal?",
  "3. Tienes colicos abdominales?",
  "4. Tienes fiebre?",
  "5. Tienes nauseas?",
  "6. Has tenido vomitos?",
  "7. Tienes escalofrios?",
  "8. Tienes malestar general?",
  "9. Tienes dolor de cabeza?",
  "10. Tienes debilidad?",
  "11. Has comido fuera de tu casa estos dias?"
};

int respuestas[NUM_PREGUNTAS];
int preguntaActual = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);

  Serial.println("================================");
  Serial.println(" EVALUACION EDUCATIVA DE SINTOMAS");
  Serial.println("================================");
  Serial.println("Responde 1 para SI y 0 para NO.");
  Serial.println();

  Serial.println(preguntas[preguntaActual]);
  Serial.println("Escribe 1 o 0 y presiona Enter.");
}

void loop() {
  if (preguntaActual < NUM_PREGUNTAS &&
      Serial.available() > 0) {

    String entrada = Serial.readStringUntil('\n');
    entrada.trim();

    if (entrada != "0" && entrada != "1") {
      Serial.println("Respuesta no valida. Escribe 1 o 0.");
      return;
    }

    respuestas[preguntaActual] = entrada.toInt();
    preguntaActual++;

    if (preguntaActual < NUM_PREGUNTAS) {
      Serial.println(preguntas[preguntaActual]);
      Serial.println("Escribe 1 o 0 y presiona Enter.");
    } else {
      evaluarSintomas();
    }
  }
}

void evaluarSintomas() {
  int totalSintomas = 0;

  // Contar los 10 sintomas
  for (int i = 0; i < 10; i++) {
    totalSintomas += respuestas[i];
  }

  // Exposicion: comer fuera de casa
  int comioFuera = respuestas[10];

  Serial.println();
  Serial.println("================================");
  Serial.println(" RESULTADO DE LA EVALUACION");
  Serial.println("================================");

  Serial.print("Total de sintomas: ");
  Serial.println(totalSintomas);

  Serial.print("Comio fuera de casa: ");
  Serial.println(comioFuera == 1 ? "SI" : "NO");

  // Reglas educativas de clasificacion
  if (totalSintomas >= 6 &&
      respuestas[0] == 1 &&
      comioFuera == 1) {

    Serial.println("Resultado: MUY POSIBLE SALMONELOSIS");
    Serial.println("Consulta a un profesional de salud.");

  } else if (
      (totalSintomas >= 4 && respuestas[0] == 1) ||
      (totalSintomas >= 5 && comioFuera == 1) ||
      (respuestas[0] == 1 &&
       respuestas[3] == 1 &&
       totalSintomas >= 3)) {

    Serial.println("Resultado: POSIBLE SALMONELOSIS");
    Serial.println("Consulta a un profesional de salud.");

  } else {
    Serial.println("Resultado: NO PROBABLE DE SALMONELOSIS");
  }

  Serial.println("================================");

  // Preparar una nueva evaluacion
  preguntaActual = 0;

  Serial.println();
  Serial.println("Nueva evaluacion:");
  Serial.println(preguntas[preguntaActual]);
  Serial.println("Escribe 1 o 0 y presiona Enter.");
}
