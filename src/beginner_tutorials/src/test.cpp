#include"ros/ros.h"
#include"people_msgs/PositionMeasurementArray.h"
#include<string.h>
#include<cstring>
#include<iostream>
#include<math.h>
#include<ctime>
#include<time.h>
using namespace std;
using std::string;

class people
{
    public:

	void PeopleCallBack(const people_msgs::PositionMeasurementArray:: ConstPtr& msg)
	{
		current_time = ros::Time::now().toSec();
		for(int i =0; i < msg->people.size(); i++)
		{
			person1_current_x = msg->people[i].pos.x;
			person1_current_y = msg->people[i].pos.y;
			person1_id = (char*)msg->people[i].name.c_str();

			if( i !=0)
			{
						
				person2_current_x = msg->people[i-1].pos.x;
				person2_current_y = msg->people[i-1].pos.y;
				person2_id = (char*)msg->people[i-1].name.c_str();
				//ROS_INFO(" current_time: %f, store: %f", current_time, store_time);
				if(person2_id != person1_id && (store_time - current_time <= 1))
				{
					check = samePersonCheck(person1_current_x, person1_current_y, person2_current_x, person2_current_y);
				}
				if(check == false)
				{
					const char *c = msg->people[i-1].name.c_str();
					strcpy((char*)msg->people[i].name.c_str(), c);
				}
				person1_radius = personCircle( person1_current_x, person1_current_y, person1_previous_x, person1_previous_y);
				person2_radius = personCircle( person2_current_x, person2_current_y, person2_previous_x, person2_previous_y);
					if( (char*)msg->people[i].name.c_str() != (char*)msg->people[i-1].name.c_str())
						{
							check = peopleCheck( person1_current_x, person1_current_y, person2_current_x, person2_current_y, person1_radius, person2_radius);
						}
				        if( check == false)
						{
							ROS_INFO(" collision");
						} 
   					 	
				ROS_INFO(" current: %s, before: %s ", msg->people[i].name.c_str(),msg->people[i-1].name.c_str());	
				//ROS_INFO("Curx: %f, Cury: %f, prevX: %f, prevY: %f", current_x,current_y, previous_x, previous_y); 
				//ROS_INFO(" radius1: %f, radius2: %f ", person1_radius, person2_radius);
			} 
					
					
		}
		person1_previous_x = person1_current_x;
		person1_previous_y = person1_current_y;
		person2_previous_x = person2_current_x;
		person2_previous_y = person2_current_y;
		//store_radius = current_radius;
		store_time = ros::Time::now().toSec();
	}		
	private:
					
	double person1_current_x = 0.0;
	double person1_current_y = 0.0;
	double person1_previous_x = 0.0;
	double person1_previous_y = 0.0;
	double person2_current_x = 0.0;
	double person2_current_y = 0.0;
	double person2_previous_x = 0.0;
	double person2_previous_y = 0.0;
	double previous_x = 0.0;
	double previous_y = 0.0;
	string person1_id;
	string person2_id;
	bool check;
	double person1_radius = 0.0;
	double person2_radius = 0.0;
	double store_radius = 0.0;
	double current_time = 0.0;
	double store_time = 0.0;
			
	bool samePersonCheck( double xPrevVal, double yPrevVal,double xCurrVal, double yCurrVal)
	{
		double rad = 0.0;
		double dia;
		rad = (pow( (xCurrVal - xPrevVal),2)) + (pow( (yCurrVal - yPrevVal),2));
		rad = sqrt(rad);
		dia = rad * 2;
		if(dia >=10)
		{
			return false;
		}
		return true;
	}
											
	double personCircle( double xCurrVal, double yCurrVal, double
												 xPrevVal, double yPrevVal)
	{
		double h = (xCurrVal + xPrevVal) / 2.0;
		double k = (yCurrVal + yPrevVal) / 2.0;
		double r = (pow( (xPrevVal - h),2)) + (pow( (yPrevVal - k),2));
		r = sqrt(r);
		return r;
	}								
		
	bool peopleCheck( double xCurrVal, double yCurrVal, double xPrevVal, double yPrevVal, double currRad, double prevRad)
	{
		if( pow((xCurrVal - xPrevVal ),2) + pow((yCurrVal - yPrevVal),2)  <= pow((currRad + prevRad),2) )
		{
			return false;
		}
		return true;
	} 
};



int main(int argc, char** argv)
{
	ros::init(argc, argv,"beginner_tutorials");
	ros::NodeHandle nh;
	people ppl;
	ros::Subscriber sub = nh.subscribe("people_tracker_measurements",1000, &people::PeopleCallBack,&ppl);
	ros::spin();
	return 0;
}
