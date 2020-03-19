#include <string.h>
#include "SensorCallback.h"
#include "AdvJSON.h"
 
double g_rms_x = 1.1;
double g_rms_y = 2.2;
double g_motor_speed_rpm = 3.3;


void CallBack_SensorData(char* content, int len, void* para)
{
	//MessageHandler* h = (MessageHandler*)mh;
	//ReadReceivedMessage(h, c, i);
	printf("message = [%.64s]\n", content);
	if (len >= 57 && strncmp(content, "{\"susiCommData\":{\"data\":{\"AnCADHandler\":{\"AnCADHandler\":{", 57) == 0) {

		AdvJSON data(content);
		AdvJSON e = data["susiCommData"]["data"]["AnCADHandler"]["AnCADHandler"]["e"];
		int len = e.Size();
		if (len != 0) {
			std::string name;
			std::string sv;
			for (int i = 0; i < len; i++) {
				name = e[i]["n"].Value();
				sv = e[i]["sv"].Value();
				if (name == "rms_x") {
					char* p = (char*)strchr(sv.c_str(), ';');
					if (p != NULL) {
						g_rms_x = atof(p+1);
					}
				}
				if (name == "rms_y") {
					char* p = (char*)strchr(sv.c_str(), ';');
					if (p != NULL) {
						g_rms_y = atof(p+1);
					}
				}
				if (name == "motor_speed_rpm") {

					if (sv != "na") {
						g_motor_speed_rpm = atof(sv.c_str());
					}
				}
			}
		}
		//else {
		//printf("message = [%.64s]\n", content);
		//}
		//printf("message = [%s]\n", content);
	}
}


EXTERNC double Get_rms_x() {
	return g_rms_x;
}
EXTERNC double Get_rms_y() {
	return g_rms_y;
}
EXTERNC double Get_motor_speed_rpm() {
	return g_motor_speed_rpm;
}