# Proyecto NPKArduinoDraginoShield_to_IoTCR

Este repositorio contiene el código de programación en Arduino IDE para el Dragino LG01-P. El objetivo del proyecto es utilizar el LG01-P como gateway para recibir datos de Nitrogeno, Fósforo y Potasio (NPK) del repositorio **NPKArduinoDraginoShield_to_IoTCR.ino** y enviarlos a través de MQTT al broker de IoTCRProjects. 

## Configuración del entorno

### Requisitos previos

- Cable Ethernet para conectar el Dragino LG01-P al puerto Ethernet de la PC.
- Software Arduino IDE instalado en la PC.

### Paso 1: Configuración del Arduino IDE

1. Abre el Arduino IDE y ve a **Archivo > Preferencias**.
2. En la sección **Gestor de URLS adicionas de tarjetas**, ingresa la siguiente URL: `http://www.dragino.com/downloads/downloads/YunShield/package_dragino_yun_test_index.json`.
3. Haz clic en **OK** para cerrar la ventana de preferencias.

### Paso 2: Carga del código

1. Conecta el cable Ethernet al puerto LAN del Dragino LG01-P y a un puerto Ethernet disponible en tu PC.
2. Abre el archivo de código en este repositorio (`DraginoLG01PtoIoTCR`) en el Arduino IDE.
3. Selecciona la placa correcta en el menú **Herramientas > Placa**. Elije "Dragino Yún + UNO or LG01-P/OLG01".
4. Selecciona el puerto correcto en el menú **Herramientas > Puerto**. Debería aparecer como "draginoxxxxx at 10.130.1.1 (Arduino Yun)".
5. Haz clic en el botón **Subir** para cargar el código en el Dragino LG01-P.

## Configuración del servidor MQTT

Es posible que necesites configurar el servidor MQTT en el Dragino LG01-P para establecer la conexión con el broker de IoTCRProjects. Aquí tienes los pasos:

1. Abre un navegador web e ingresa la siguiente dirección: `http://10.130.1.1`.
2. Ingresa la contraseña "dragino" cuando se te solicite.
3. Ve a la sección de configuración del servidor IoT y MQTT.
4. Configura el broker MQTT especificando el usuario, contraseña, puerto y tópico adecuados.

## Acceso al Linux incorporado

Puedes acceder al sistema Linux incorporado en el Dragino LG01-P mediante SSH. Aquí tienes los pasos:

1. Abre una terminal en tu PC.
2. Ejecuta el siguiente comando para iniciar la conexión SSH: `ssh root@10.130.1.1`.
3. Ingresa la contraseña "dragino" cuando se te solicite.

### Verificación de la conexión a Internet

1. Accede a la interfaz gráfica del Dragino LG01-P a través de un navegador web.
2. Dirígete a la sección "Acceso a internet".
3. Verifica y configura la conexión a Internet, preferiblemente utilizando una conexión Ethernet para una mejor conectividad.
4. Asegúrate de que el cable Ethernet esté correctamente conectado al puerto WAN del Dragino LG01-P.

## Funcionamiento del código

El código se ejecuta de la siguiente manera:

1. El bucle principal (`loop`) está a la escucha de un mensaje Lora.
2. Cuando se cumple una condición, se crea una instancia de `Process`.
3. Se recorre tres veces el bucle para cada valor de NPK (Nitrogeno, Fósforo y Potasio).
4. Los parámetros se envían a través de un puente a la instancia de Linux incorporada en el Dragino LG01-P.
5. La instancia de Linux envía los parámetros por MQTT al broker de IoTCRProjects.

## Contribuciones

¡Las contribuciones a este proyecto son bienvenidas! Si encuentras algún problema, tienes alguna mejora o quieres colaborar, no dudes en abrir un issue o enviar una solicitud de pull.

## Contacto

Si tienes alguna pregunta o necesitas más información, puedes contactarme a través de [correo electrónico](mailto:tu-email@example.com).

¡Gracias por utilizar el Dragino LG01-P!

---   

## Verificación de paquetes instalados

Puedes verificar los paquetes instalados en el Dragino LG01-P utilizando los siguientes comandos:

```shell
root@dragino-169d30:~# opkg update // para obtener la lista de paquetes más reciente
root@dragino-169d30:~# opkg list // muestra los paquetes disponibles
root@dragino-169d30:~# opkg install mosquitto-client // instala el cliente MQTT (se instalará automáticamente)
````

### Verificación de la conexión a Internet

1. Accede a la interfaz gráfica del Dragino LG01-P a través de un navegador web.
2. Dirígete a la sección "Acceso a internet".
3. Verifica y configura la conexión a Internet, preferiblemente utilizando una conexión Ethernet para una mejor conectividad.
4. Asegúrate de que el cable Ethernet esté correctamente conectado al puerto WAN del Dragino LG01-P.

## Funcionamiento del código

El código se ejecuta de la siguiente manera:

1. El bucle principal (`loop`) está a la escucha de un mensaje Lora.
2. Cuando se cumple una condición, se crea una instancia de `Process`.
3. Se recorre tres veces el bucle para cada valor de NPK (Nitrogeno, Fósforo y Potasio).
4. Los parámetros se envían a través de un puente a la instancia de Linux incorporada en el Dragino LG01-P.
5. La instancia de Linux envía los parámetros por MQTT al broker de IoTCRProjects.

## Contribuciones

¡Las contribuciones a este proyecto son bienvenidas! Si encuentras algún problema, tienes alguna mejora o quieres colaborar, no dudes en abrir un issue o enviar una solicitud de pull.

## Contacto

Si tienes alguna pregunta o necesitas más información, puedes contactarme a través de [correo electrónico](mailto:rrojasl@iscr.com).

¡Gracias por utilizar el Dragino LG01-P!

---



