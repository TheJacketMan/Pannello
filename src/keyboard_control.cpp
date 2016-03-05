#include "ros/ros.h"
#include "geometry_msgs/Wrench.h"

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
   ros::init(argc, argv, "keyboard_control");

   ros::NodeHandle n;
   ros::Publisher wrench_pub = n.advertise<geometry_msgs::Wrench>("/force", 100);
   ros::Publisher wrench_pub2 = n.advertise<geometry_msgs::Wrench>("/force2", 100);

   ros::Rate loop_rate(3);

   std::cout << "A-D Rotate Panel" << std::endl;
   std::cout << "W-S Move Panel" << std::endl;

   while (ros::ok())
   {
      int ch;
      geometry_msgs::Wrench wrench;

      wrench_pub.publish(wrench);
      wrench_pub2.publish(wrench);

      switch (ch = std::tolower(std::cin.get()))
      {
	      case 'a':
	      case 'd':
			 loop_rate.sleep();
	         wrench.torque.z = (ch == 'a') ? 0.5 : -0.5;
	         wrench_pub.publish(wrench);
	         
	         loop_rate.sleep();
	         
	         wrench.torque.z = (ch == 'a') ? -0.5 : 0.5;
	         wrench_pub.publish(wrench);
	         loop_rate.sleep();
	         
	         wrench.torque.z = 0;
	         wrench_pub.publish(wrench);
	         break;

	      case 'w':
	      case 's':
			 loop_rate.sleep();
	         wrench.torque.x= (ch == 'w') ? 0.25 : -0.25;
	         wrench_pub.publish(wrench); 
	         
	         loop_rate.sleep();
	         
	         wrench.torque.x = (ch =='w') ? -0.25 : 0.25;
	         wrench_pub2.publish(wrench);
	         loop_rate.sleep();
	         
	         wrench.torque.x = 0;
	         wrench_pub2.publish(wrench);
	         break;

         default:
            break;
      }


      // Eat \n
      std::cin.get();
   }

   return 0;
}
