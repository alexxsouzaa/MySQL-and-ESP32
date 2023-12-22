 __ __       ___  ___  _      ___    ___  ___  ___  ____ ___ 
|  \  \ _ _ / __]| . || |    | __]  | __]/ __]| . \[__ /[_  ]
|     || | |\__ \| | || |_   | _]   | _] \__ \|  _/ [_ \ / / 
|_|_|_| \  |[___/`___\|___|  |___]  |___][___/|_|  [___/[___]
        [__/                                                 
/*
Created in 04/05/2023.
*/

#include <WiFi.h>              // Biblioteca do WiFi.
#include <Wire.h>              // Biblioteca do WiFi.
#include <AHT10.h>             // Biblioteca do sensor AHT20.
#include <Adafruit_BMP280.h>   // Biblioteca do sensor BMP280.
#include <MySQL_Cursor.h>      // Biblioteca do MySQL.
#include <MySQL_Connection.h>  // Biblioteca do MySQL.

Adafruit_BMP280 bmp;
AHT10 myAHT20(AHT10_ADDRESS_0X38, AHT20_SENSOR);

IPAddress server_addr(85, 10, 205, 173);  //endereço IP do servidor MySQL.
char user[] = "xxxxxxxxxxxxxxxx";         //nome do usuário do MySQL.
char password[] = "xxxxxxxxxxxxxxxx";     //senha do usuário do MySQL.

char ssid_wifi[] = "xxxxxxxxxxxxxxxx";    //nome da rede WiFi.
char senha_wifi[] = "xxxxxxxxxxxxxxxx.";  //senha da rede WiFi.

//char INSERT_DATA[] = "INSERT INTO  NOME_DO_BANCO_DE_DADOS.NOME_DA_TABELA (COLUNA1, COLUNA2) VALUES (%d,%s)";
char INSERT_DATA[] = "INSERT INTO  dataBaseName.temperatura (ID_ESP, temperatura) VALUES (%d,%s)";

int id = 02;  // Identificador do ESP32.

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid_wifi, senha_wifi);  // Inicializa o WiFi.

  while (WiFi.status() != WL_CONNECTED) {  // Verifica a conexão do WiFi.
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }

  while (myAHT20.begin() != true) {  // Verifica o sensor AHT20.
    Serial.println(F("AHT20 não conectado"));
    delay(5000);
  }
  Serial.println(F("AHT20 OK"));

  if (!bmp.begin()) {  //Verifica o sensor BMP280.
    Serial.println(F("BMP280 não conectado"));
    while (1)
      ;
  } else {
    Serial.println(F("BMP280 OK"));
  }

  // Paranmetros do sensor BMP280.
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo operacional. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Sobreamostragem de pressão */
                  Adafruit_BMP280::FILTER_X16,      /* Filtragem. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tempo de espera. */
}

void loop() {
  DataSend(id, bmp.readTemperature());  // Envia os dados de Temperatura para o Banco de Dados.
}

void DataSend(int id, float temp) {
  char query[128];
  char temperatura[10];

  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

    //  Guarda os dados.
    dtostrf(temp, 1, 1, temperatura);
    sprintf(query, INSERT_DATA, id, temperatura);

    // Executa o query.
    cur_mem->execute(query);

    // Excluir o cursor e libera memória usada.
    delete cur_mem;
    Serial.println();
    Serial.println("Dados registrados.");  //
  } else {
    Serial.println();
    Serial.println("Falha na conexão.");  //
  }
  conn.close();
}
