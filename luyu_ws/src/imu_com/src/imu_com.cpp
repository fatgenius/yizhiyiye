

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <serial/serial.h> 
#include "IMU100.h"
# include <sensor_msgs/Imu.h>
#include <sstream>

serial::Serial ser; // 
unsigned char cal_flag = 1;
unsigned char cal_count =0;

//
void write_callback(const std_msgs::String::ConstPtr& msg) 
{ 
    ROS_INFO_STREAM("Writing to serial port" <<msg->data); 
    ser.write(msg->data);   //
} 

void cal_callback(const std_msgs::String::ConstPtr& msg) 
{ 
    ROS_INFO_STREAM("calibrate imu"); 
    //ser.write(msg->data);   //
    cal_flag =1;
} 

int main(int argc, char **argv)
{
    unsigned char  gdata[1024*1024] ;
    int   gcount,gtotal ; //gcount=current pointer; gtotal=total data number

    gcount =0;
    gtotal =0;
    int i=0;
    int j=0;

    // 
    ros::init(argc, argv, "serial_imu_node"); 
    // 
    ros::NodeHandle nh; 
    //
    ros::Subscriber IMU_write_pub = nh.subscribe("imu_command", 1000, write_callback); 

    ros::Subscriber IMU_cal_sub = nh.subscribe("imu_cal", 1000, cal_callback); 
    //
    ros::Publisher IMU_read_pub = nh.advertise<sensor_msgs::Imu>("imu/data", 1000); 

    //
    try 
    { 
    	//
        ser.setPort("/dev/ttyUSB0"); 
        //ser.setBaudrate(9600); 
	ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
        ser.setTimeout(to); 
        ser.open(); 
    } 
    catch (serial::IOException& e) 
    { 
        ROS_ERROR_STREAM("Unable to open port "); 
        return -1; 
    } 

    //
    if(ser.isOpen()) 
    { 
        ROS_INFO_STREAM("Serial Port initialized"); 
    } 
    else 
    { 
        return -1; 
    } 


    //100Hz
    //ros::Rate loop_rate(100);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
       ///ser.flush();
       //CMD
       ////char  cmddata[10] ;
       ////cmddata[0] = 0x77;
       ////cmddata[1] = 0x04;
       ////cmddata[2] = 0x00;
       ////cmddata[3] = 0x59;
       ///cmddata[4] = 0x5D;
       ///cmddata[5] = 0x0;
       ///ser.write((uint8_t*)cmddata, 5);

      //delay 0.01s
      ///ros::Duration(0.025).sleep();
      //ros::Duration(1).sleep();

      unsigned char  data_size;
      
      if(data_size = ser.available())
      { 
	   /*
           //ROS_INFO_STREAM("data_size:" <<data_size);    
 	   if(data_size < 48)
	   {
               printf("data_size=%d\n",data_size); 
	       char  tdata[data_size] ;
	       ser.read((uint8_t*)tdata, data_size);

	       for(i=0; i<data_size; i++)
               {
                   printf("%02X ",(uint8_t*)tdata[i]);
	       }           
	       printf("\n");
              // ROS_INFO_STREAM("data_size not valid");
	       continue;
	   }
	   */
           //unsigned char  tmpdata[data_size] ;
	   unsigned char  data[data_size] ;
           // ser.read(tmpdata, data_size);
	   ser.read((uint8_t*)data, data_size);

           //new swap tmp buffer
	   unsigned char  tmp[gtotal-gcount] ;
	   
	   //swap data to begin
	   printf("gtotal=%d, gcount=%d\n",gtotal,gcount);
           memcpy(tmp, &gdata[gcount] , gtotal-gcount);
	   gtotal = gtotal-gcount;
           gcount =0;
           printf("gtotal=%d\n",gtotal);
	   memcpy(gdata, tmp, gtotal);
	   
           if(gtotal + data_size >= 1024*1024)
	   {
                gtotal =0;
		gcount =0;
		continue ; 
           }
           printf("gtotal=%d, data_size=%d\n",gtotal,data_size);
	   memcpy(&gdata[gtotal], data, data_size);   //add new data frame
	   gtotal += data_size;

           //parsing
           for(gcount=0; gcount < gtotal; gcount++) 
	   {
                   if(gtotal-gcount <= 48+9)
		   {
		       break;
		   }
		   //is real data ? check data frame
		   //need add checksum
		   //if((0x77 != gdata[i]) && (0x59 != gdata[3+i]) && (0x2F != gdata[1+i]))
		   if((0x77 != gdata[gcount]) && (0x59 != gdata[3+gcount]) && (0x38 != gdata[1+gcount]))
		   {
		      //ROS_INFO_STREAM("data frame error!"); 
		      continue;
		   }

		   unsigned char check=0;
		   for(j = gcount+1 ; j< gcount + 47+9; j++)
		   {
		          check = 0xff & (check +  (unsigned char)gdata[j]);
		   } 
		   if(( 0xff & (unsigned char)gdata[gcount + 47+9]) != (0xff & check))
		   {
		           printf("data check error!gdata[47]=0x%02X,check=0x%02X\n",gdata[gcount+ 47+9],check); 
		           for(j=gcount; j<gcount + 48+9; j++)
		           { 
		               printf("%02X ",(unsigned char)gdata[j]);
			   }           
			   printf("\n");
			   continue;
		   }
                   else
		   {
		        printf("------ok!!!----\n");
		        printf("data check ok!gdata[47]=0x%02X,check=0x%02X\n",gdata[gcount+ 47+9],check); 
		        for(j=gcount; j<gcount + 48+11; j++)
		        { 
		             printf("%02X ",(unsigned char)gdata[j]);
			}           
			printf("\n");
		   }

		   IMU100.CopeSerialData( &gdata[gcount] ,48+9);   //
		   gcount += 48+9;

		   sensor_msgs::Imu imu_data;
		    
		   if(!cal_flag)
		   {
			   imu_data.header.stamp = ros::Time::now();
			   imu_data.header.frame_id = "base_link";
			   imu_data.orientation.x = (float)IMU100.stInfo.quat[0];// - IMU100.stCal.quat[0];
			   imu_data.orientation.y = (float)IMU100.stInfo.quat[1];// - IMU100.stCal.quat[1] ;
			   imu_data.orientation.z = (float)IMU100.stInfo.quat[2];// - IMU100.stCal.quat[2] ;
			   imu_data.orientation.w = (float)IMU100.stInfo.quat[3];// - IMU100.stCal.quat[3] ;
		       
			   imu_data.angular_velocity.x = (float)IMU100.stInfo.angle_vel[0] - IMU100.stCal.angle_vel[0];
			   imu_data.angular_velocity.y = (float)IMU100.stInfo.angle_vel[1] - IMU100.stCal.angle_vel[1];
			   imu_data.angular_velocity.z = (float)IMU100.stInfo.angle_vel[2] - IMU100.stCal.angle_vel[2];

 			   //imu_data.angular_velocity.x = (float)IMU100.stInfo.angle_vel[0] ;
			   //imu_data.angular_velocity.y = (float)IMU100.stInfo.angle_vel[1] ;
			   //imu_data.angular_velocity.z = (float)IMU100.stInfo.angle_vel[2] ;
		 
			   imu_data.linear_acceleration.x = (float)IMU100.stInfo.acc[0] ;//- IMU100.stCal.acc[0];
			   imu_data.linear_acceleration.y = (float)IMU100.stInfo.acc[1] ;//- IMU100.stCal.acc[1];
			   imu_data.linear_acceleration.z = (float)IMU100.stInfo.acc[2] ;//- IMU100.stCal.acc[2];
 
			   IMU_read_pub.publish(imu_data);
		   }
		   else
		   {    //calibrate
		       if(cal_count < 100)
		       {
                           cal_count++;

			   IMU100.stCal.quat[0] += (float)IMU100.stInfo.quat[0];
			   IMU100.stCal.quat[1] += (float)IMU100.stInfo.quat[1];
			   IMU100.stCal.quat[2] += (float)IMU100.stInfo.quat[2];
                           IMU100.stCal.quat[3] += (float)IMU100.stInfo.quat[3];
		       
			   IMU100.stCal.angle_vel[0] += (float)IMU100.stInfo.angle_vel[0];
			   IMU100.stCal.angle_vel[1] += (float)IMU100.stInfo.angle_vel[1];
			   IMU100.stCal.angle_vel[2] += (float)IMU100.stInfo.angle_vel[2];

			   IMU100.stCal.acc[0] += (float)IMU100.stInfo.acc[0];
			   IMU100.stCal.acc[1] += (float)IMU100.stInfo.acc[1];
			   IMU100.stCal.acc[2] += (float)IMU100.stInfo.acc[2];

		       }
		       else
		       {
			   cal_flag =0;		
  			   cal_count =0;
	   
			   IMU100.stCal.quat[0] = (float)IMU100.stCal.quat[0] / 100;
			   IMU100.stCal.quat[1] = (float)IMU100.stCal.quat[1] / 100;
			   IMU100.stCal.quat[2] = (float)IMU100.stCal.quat[2] / 100;
                           IMU100.stCal.quat[3] = (float)IMU100.stCal.quat[3] / 100;
		       
			   IMU100.stCal.angle_vel[0] = (float)IMU100.stCal.angle_vel[0] / 100;
			   IMU100.stCal.angle_vel[1] = (float)IMU100.stCal.angle_vel[1] / 100;
			   IMU100.stCal.angle_vel[2] = (float)IMU100.stCal.angle_vel[2] / 100;

			   IMU100.stCal.acc[0] = (float)IMU100.stCal.acc[0] / 100;
			   IMU100.stCal.acc[1] = (float)IMU100.stCal.acc[1] / 100;
			   IMU100.stCal.acc[2] = (float)IMU100.stCal.acc[2] / 100;
			 
		       }

		   }
		   
		   
	   }
        }
        
        ros::spinOnce(); 
        loop_rate.sleep(); 
    }
        ser.close();
  	return 0;
 }






