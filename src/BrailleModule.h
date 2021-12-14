#include <SoftwareSerial.h>
#ifndef BRAILLEMODULE_H_
#define BRAILLEMODULE_H_

#define SOM 0x80 // start of the message // inicio del mensaje
#define EOM 0x81 // end of the message // fin del mensaje
#define SRC 0x10 // Source // Fuente

/*
 *	Commands
 */

#define ACTUATE_CMD 0x02 // Actuate with data of 10 Bytes // Actuar con datos de 10 Bytes
#define ACTUATE_LTH 13
#define GET_DEVICE_STATUS_CMD 0x07 // Gives the status of device whether it is ready to send data or any error present in the module // Da el estado del dispositivo si está listo para enviar datos o cualquier error presente en el módulo
#define SELF_TEST_CMD 0x08 // Do the Module Self test part on request // Hacer la parte de autoprueba del módulo a pedido
#define SET_CURSOR_KEY_DATA_TIME_CMD 0x0A // Set time interval at which data to be sent when cursor is pressed continuously (Data format is DATA = Time in mS/10) Default Value is 100 mS so data is 0x0A // Establece el intervalo de tiempo en el que se enviarán los datos cuando se presiona el cursor continuamente (el formato de datos es DATOS = Tiempo en mS / 10) El valor predeterminado es 100 mS, por lo que los datos son 0x0A
#define GET_FB_TIME_INFO 0x0B // Get Feedback time of each pins // Obtenga el tiempo de retroalimentación de cada pines
#define DISABLE_AUTO_REPLY 0x0D // Disable Auto error and acknowledge packets // Deshabilitar el error automático y reconocer paquetes
#define RESUME_CMD 0x09 // Resume the System from Halt/Error Condition // Reanudar el sistema desde una condición de parada / error
/*
 *	Error Query commands	
 */
#define ERR_CMD 0x03
#define ERR_SUB_CMD_GET 0x00 // Get Error which was last occured in the module (sub command 0x00 to get the error) // Obtener el error que ocurrió por última vez en el módulo (subcomando 0x00 para obtener el error)
#define ERR_SUB_CMD_SLAVE_COMM 0x01 // Slave is not connected to host // El esclavo no está conectado al host
#define ERR_SUB_CMD_LATCH 0x02 // Latch feedback not received // No se ha recibido la retroalimentación del pestillo
#define ERR_SUB_CMD_SLAVE_ACTUATION_FB 0x04 // Send pin details of those pins which doesn’t get FB. in the same format of actaution  // Envíe los detalles de los pines de los pines que no reciben FB. en el mismo formato de actaution
#define ERR_SUB_CMD_POWER_SURGE 0x08 // When SMA Voltage is less than 1 V // Cuando el voltaje SMA es inferior a 1 V
#define ERR_SUB_CMD_OVER_TEMP 0x10 // When Temperature is greater than 45deg // Cuando la temperatura es superior a 45 grados
#define ERR_SUB_CMD_OVER_VOLTAGE 0x20 // When SMA Voltage is greater than 2.5V // Cuando el voltaje SMA es superior a 2,5 V
#define ERR_SUB_CMD_DATA_INTEGRITY 0x40 // When the data is received from module but the chksum doesn’t match // Cuando los datos se reciben del módulo pero el chksum no coincide
/*
 *	Diagnostics In Detail
 */
#define DIA_CMD 0x05
#define DIA_SUB_CMD_MODE_ENABLE 0x01 // Switch to Diagnostic mode where normal command are disabled. // Cambia al modo de diagnóstico donde los comandos normales están deshabilitados.
#define DIA_SUB_CMD_MODE_DISABLE 0x01 // Switch to Normal Mode // Cambiar al modo normal
#define DIA_SUB_CMD_LATCH_ON 0x02 // Switch ON the latch  // Encienda el pestillo
#define DIA_SUB_CMD_LATCH_OFF 0x02 // Switch OFF the latch // Apague el pestillo
#define DIA_SUB_CMD_ACTUATION_ON 0x03 // Actuate wires with 10 bytes of data sent and remain in steady with out any safety cutoff timers  // Activa los cables con 10 bytes de datos enviados y permanece estable sin temporizadores de corte de seguridad
#define DIA_SUB_CMD_ACTUATION_OFF 0x04 // Deactuate all wires if actuated  // Desactivar todos los cables si se activan
#define DIA_SUB_CMD_PEAK_PWR_CONSTANT 0x05 // Set Peak power added by the value specified // Establecer la potencia máxima agregada por el valor especificado
#define DIA_SUB_CMD_STEADY_PWR_CONSTANT 0x06 // Set Steady power added by value specified // Establecer la potencia constante agregada por el valor especificado


/*
 *	Information received to the source / Información recibida a la fuente
 *	Here, destination and source will be reversed / Aquí, el destino y la fuente se invertirán
 */

#define KEY_INFO 0x01 // Send Key Press event to Main module  // Enviar evento de pulsación de tecla al módulo principal
#define DEVICE_STATUS 0x07 // Send the Status of the device as in table below // Envíe el estado del dispositivo como se muestra en la siguiente tabla
#define SUCCESS_INFO 0x04 // Send Success when all pins actuated with proper feedback // Enviar éxito cuando todos los pines se activaron con la retroalimentación adecuada
#define FB_TIME_INFO 0x0B // Send feedback time of pins slave wise (Sub command defines the slave no.) // Enviar tiempo de retroalimentación de los pines esclavo (el comando secundario define el número de esclavo)

/*
 *	Device Status Data Details
 */
#define INIT 0x01 // Initialising phase where self test is not complete // Fase de inicialización donde la autocomprobación no está completa
#define READY 0x02 // Ready to receive data // Listo para recibir datos
#define BUSY 0x04 // HOST is in actuation cycle // HOST está en ciclo de actuación
#define ERR 0x08 // Stuck in communication or latch error // Atascado en la comunicación o error de pestillo
#define SELF_TEST 0x10 // Self test Pass/Fail // Autoprueba Pasa / No pasa
/*************************************/
#define ERR_LOW_VOL 0x08
#define ERR_HIGH_VOL 0x20
#define ERR_OVER_TEMP 0x10
#define ERR_COMM_ERR 0x01
#define CHK_FRAME_DATA_INTEGRITY 0x40
#define LATCH 0x02
#define FB 0x04


class BrailleModule
{
  public:
    long last_acutate;
  	int host_addr;
  	int* prev_data[10];
  	void init_host(int host_id);
  	bool is_data_written();
	void actuate(int data[]);
	void get_device_status();
	void self_test();
	void set_cursor(int data);
	void get_fb();
	void resume();
	void error(int sub_cmd);
	int parse_message();
};

#endif //BRAILLEMODULE_H_
