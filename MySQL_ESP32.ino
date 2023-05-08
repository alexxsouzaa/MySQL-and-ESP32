 __ __       ___  ___  _      ___    ___  ___  ___  ____ ___ 
|  \  \ _ _ / __]| . || |    | __]  | __]/ __]| . \[__ /[_  ]
|     || | |\__ \| | || |_   | _]   | _] \__ \|  _/ [_ \ / / 
|_|_|_| \  |[___/`___\|___|  |___]  |___][___/|_|  [___/[___]
        [__/                                                 
/*
Created in 04/05/2023.
*/

#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(85, 10, 205, 173);  //endereço IP do servidor MySQL.
char user[] = "XXXXXXXXXXXXXX";           //nome do usuário do MySQL.
char password[] = "XXXXXXXXXXXXXX";       //senha do usuário do MySQL.

char ssid_wifi[] = "XXXXXXXXXXXXXX";      //nome da rede WiFi.
char senha_wifi[] = "XXXXXXXXXXXXXX.";    //senha da rede WiFi.

//char INSERT_DATA[] = "INSERT INTO  NOME_DO_BANCO_DE_DADOS.NOME_DA_TABELA (COLUNA1, COLUNA2) VALUES (%d,%s)";
char INSERT_DATA[] = "INSERT INTO  esp32_db.temperatura (ID_SENSOR, temperatura) VALUES (%d,%s)";

int id = 1;         //  Variavel de Identifição.
float temp = 27.4;  //  Variavel de Temperatura.

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid_wifi, senha_wifi);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  DataSend(id, temp);
}

//  Função responsavel por enviar os dados.
void DataSend(int id, float temp) {
  char query[128];
  char temperatura[10];

  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

    // Guarda os dados.
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
