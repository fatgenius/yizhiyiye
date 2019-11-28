

#include "IMU100.h"
#include "string.h"

CIMU100 ::CIMU100 ()
{
}

void CIMU100 ::CopeSerialData(unsigned char ucData[],unsigned short usLength)
{
	int i=0;
	static unsigned char chrTemp[70];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;


	memcpy(&stFrame,ucData,usLength);
	
	for(i=0; i< 3 ; i++)
	{
		stInfo.angle[i] = (float)(0x0f & stFrame.angle[i][0]) * 100 ; //MSB
		stInfo.angle[i] += (float)((0xf0 & stFrame.angle[i][1]) >> 4) * 10;
		stInfo.angle[i] += (float)(0x0f & stFrame.angle[i][1]) ;
		stInfo.angle[i] += (float)((0xf0 & stFrame.angle[i][2]) >> 4) * 0.1 ;
		stInfo.angle[i] += (float)(0x0f & stFrame.angle[i][2]) * 0.01 ; //LSB
		if((0xf0 & stFrame.angle[i][0]) == 0x10)
		{
			stInfo.angle[i] = -stInfo.angle[i];
		}

		stInfo.acc[i] = (float)(0x0f & stFrame.acc[i][0]) ; //MSB
		stInfo.acc[i] += (float)((0xf0 & stFrame.acc[i][1]) >> 4) * 0.1;
		stInfo.acc[i] += (float)(0x0f & stFrame.acc[i][1]) * 0.01;
		stInfo.acc[i] += (float)((0xf0 & stFrame.acc[i][2]) >> 4) * 0.001 ;
		stInfo.acc[i] += (float)(0x0f & stFrame.acc[i][2]) * 0.0001 ; //LSB
		if((0xf0 & stFrame.acc[i][0]) == 0x10)
		{
			stInfo.acc[i] = -stInfo.acc[i];
		}

		stInfo.angle_vel[i] = (float)(0x0f & stFrame.angle_vel[i][0]) * 100 ; //MSB
		stInfo.angle_vel[i] += (float)((0xf0 & stFrame.angle_vel[i][1]) >> 4) * 10;
		stInfo.angle_vel[i] += (float)(0x0f & stFrame.angle_vel[i][1]) ;
		stInfo.angle_vel[i] += (float)((0xf0 & stFrame.angle_vel[i][2]) >> 4) * 0.1 ;
		stInfo.angle_vel[i] += (float)(0x0f & stFrame.angle_vel[i][2]) * 0.01 ; //LSB
		if((0xf0 & stFrame.angle_vel[i][0]) == 0x10)
		{
			stInfo.angle_vel[i] = -stInfo.angle_vel[i];

		}

		stInfo.quat[i] = (float)(0x0f & stFrame.quat[i][0]) ; //MSB
		stInfo.quat[i] += (float)((0xf0 & stFrame.quat[i][1]) >> 4) * 0.1;
		stInfo.quat[i] += (float)(0x0f & stFrame.quat[i][1]) * 0.01;
		stInfo.quat[i] += (float)((0xf0 & stFrame.quat[i][2]) >> 4) * 0.001 ;
		stInfo.quat[i] += (float)(0x0f & stFrame.quat[i][2]) * 0.0001 ; 
		stInfo.quat[i] += (float)((0xf0 & stFrame.quat[i][3]) >> 4) * 0.00001 ;
		stInfo.quat[i] += (float)(0x0f & stFrame.quat[i][3]) * 0.000001 ; //LSB

		if((0xf0 & stFrame.quat[i][0]) == 0x10)
		{
			stInfo.quat[i] = -stInfo.quat[i];
		}
	}

		//add Four elements
		stInfo.quat[3] =(float)( 0x0f & stFrame.quat[3][0]) ; //MSB
		stInfo.quat[3] += (float)((0xf0 & stFrame.quat[3][1]) >> 4) * 0.1;
		stInfo.quat[3] += (float)(0x0f & stFrame.quat[3][1]) * 0.01;
		stInfo.quat[3] += (float)((0xf0 & stFrame.quat[3][2]) >> 4) * 0.001 ;
		stInfo.quat[3] += (float)(0x0f & stFrame.quat[3][2]) * 0.0001 ; 
		stInfo.quat[3] += (float)((0xf0 & stFrame.quat[3][3]) >> 4) * 0.00001 ;
		stInfo.quat[3] += (float)(0x0f & stFrame.quat[3][3]) * 0.000001 ; //LSB
		if((0xf0 & stFrame.quat[3][0]) == 0x10)
		{
			stInfo.quat[3] = -stInfo.quat[3];
		}



}



CIMU100 IMU100 = CIMU100();
