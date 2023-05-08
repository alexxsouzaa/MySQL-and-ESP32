# Enviando dados do sensor BME280 para um banco de dados MySQL usando ESP32.

Este é um projeto de exemplo que mostra como enviar dados do sensor BME280 para um banco de dados MySQL usando um microcontrolador ESP32. O projeto é escrito em Arduino Framework e foi testado usando o IDE do Arduino.

# Requisitos
Microcontrolador ESP32 (ex: ESP-WROOM-32)
Sensor BME280
Servidor MySQL (usamos o db4free.net para fins de exemplo)
IDE do Arduino

# Bibliotecas
As seguintes bibliotecas são necessárias para este projeto:

Adafruit BME280 Library (https://github.com/adafruit/Adafruit_BME280_Library)
MySQL Connector Arduino Library (https://github.com/ChuckBell/MySQL_Connector_Arduino)

# Conexão
Conecte o sensor BME280 ao ESP32 conforme o seguinte diagrama:

BME280	ESP32
VIN	3.3V
GND	GND
SCL	GPIO22
SDA	GPIO21

# Configuração do servidor MySQL
Este exemplo usa um servidor MySQL hospedado no db4free.net. Você precisa se registrar para obter as credenciais necessárias para acessar o servidor.

Após o registro, acesse o painel do phpMyAdmin e crie um novo banco de dados chamado "dados_sensor". Em seguida, crie uma nova tabela chamada "temperatura" com três colunas: id_sensor, temperatura e data_hora.

# Como funciona
O ESP32 lê os dados do sensor BME280 e os envia para o servidor MySQL usando uma conexão Wi-Fi. Ele se conecta à rede Wi-Fi configurada nas credenciais fornecidas e, em seguida, envia os dados para a tabela "temperatura" no banco de dados "dados_sensor". O ID do sensor é definido como "0" neste exemplo, mas você pode alterá-lo para cada sensor conectado ao servidor.

# Considerações finais
Este é apenas um exemplo de como enviar dados de um sensor para um banco de dados usando um ESP32 e o IDE do Arduino. Você pode adaptar este projeto para usar outros sensores, adicionar mais tabelas ao banco de dados e personalizar o código para atender às suas necessidades específicas.

# Contribuindo
Sinta-se à vontade para enviar sugestões de melhorias ou correções de bugs neste projeto. Abra um problema ou envie uma solicitação de recebimento para contribuir com o código.

# Licença
Este projeto é licenciado sob a Licença MIT - consulte o arquivo LICENSE para obter detalhes.


![WhatsApp Image 2023-05-08 at 14 45 09](https://user-images.githubusercontent.com/132787362/236894004-9be251c8-03ad-4bf9-b062-cf0cc4826939.jpeg)
![WhatsApp Image 2023-05-08 at 14 45 09 (1)](https://user-images.githubusercontent.com/132787362/236894045-d4afc0ff-6b35-46bb-93fb-4f0910cb5f49.jpeg)
![WhatsApp Image 2023-05-08 at 14 45 09 (2)](https://user-images.githubusercontent.com/132787362/236894070-c1f32ab1-4819-4098-b90b-57a64d7f7d24.jpeg)
![WhatsApp Image 2023-05-08 at 14 45 08](https://user-images.githubusercontent.com/132787362/236894072-3f1eda92-33de-4a2a-bda3-72863b2a12ef.jpeg)
