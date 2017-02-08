#include"ros/ros.h"
#include"people_msgs/PositionMeasurementArray.h"
#include"beginner_tutorials/people_id.h"
#include<string.h>
#include<cstring>
#include<iostream>
#include<math.h>
#include<ctime>
#include<time.h>
using namespace std;
using std::string;
using beginner_tutorials::people_id;
class people
{
    public:
	people( const ros::Publisher& ID_pub)
		:ID_pub_(ID_pub){
	}		

    void PeopleCallBack(const people_msgs::PositionMeasurementArray:: ConstPtr& msg)
    {
        current_time = ros::Time::now().toSec();
		people_id ID;
        for(int i = 1; i < msg->people.size(); i++)
        {
            person1_current_x =  msg->people[i].pos.x;
            person1_current_y = msg->people[i].pos.y;
            person1_id = msg->people[i].name.c_str();
          
            if(person1_store_id != person1_id)
            {
                
                check1 = samePersonCheck(person1_radius, person1_current_x, 
					person1_current_y, person1_previous_x, person1_previous_y);
            }
            if(check1 == false)
            {
                  
                people_id ID = Change( person1_store_id, true);
                 
            }
            if(check1 == true)
			{
				ID.person1_id = person1_id;
			}
               
            person1_radius = personCircle( person1_current_x, person1_current_y, person1_previous_x, person1_previous_y);
               
            person2_current_x =  msg->people[i-1].pos.x;
            person2_current_y = msg->people[i-1].pos.y;
            person2_id = msg->people[i-1].name.c_str();
          
            if(person2_store_id != person2_id )
            {
                                                            
                check2 = samePersonCheck(person2_radius, person2_current_x, 
					person2_current_y, person2_previous_x, person2_previous_y);
            }
            if(check2 == false)
            {
                  
                people_id ID = Change( person2_store_id, false);
                 
            }
            if(check2 == true)
			{
				ID.person2_id = person2_id;
			}
             
               
            person2_radius = personCircle( person2_current_x, person2_current_y, person2_previous_x, person2_previous_y);
            check = peopleCheck( person1_current_x, person1_current_y, person2_current_x, person2_current_y,person1_radius, person2_radius);
               
            if( check == false)
            {
                //ROS_INFO(" collision");
               
            }
           // ROS_INFO(" current: %s, before: %s ", ID.person1_id.c_str(),ID.person2_id.c_str());
			ID.person1_X = person1_current_x;
			ID.person1_Y = person1_current_y;
			ID.person2_X = person2_current_x;
			ID.person2_Y = person2_current_y;
			ID_pub_.publish(ID);
          
        }
            person1_store_id = person1_id;
            person1_previous_x = person1_current_x;
            person1_previous_y = person1_current_y;
			person1_store_radius = person1_radius;
            person2_store_id = person2_id;
            person2_previous_x = person2_current_x;
            person2_previous_y = person2_current_y;
			person2_store_radius = person2_radius;
            store_time = ros::Time::now().toSec();
    }

    private: 

    double person1_current_x = 0.0;
    double person1_current_y = 0.0;
    double person1_previous_x = 0.0;       
    double person1_previous_y = 0.0;
    string person1_store_id = "";
    string person2_store_id = "";
    double person2_current_x = 0.0;
    double person2_current_y = 0.0;
    double person2_previous_x = 0.0;
    double person2_previous_y = 0.0;
    double previous_x = 0.0;
    double previous_y = 0.0;
    string person1_id;
    string person2_id ;
    bool check;
    bool check1;
    bool check2;
    int size = 0;
    double person1_radius = 0.0;
    double person2_radius = 0.0;
    double person1_store_radius = 0.0;
    double person2_store_radius = 0.0;
    double store_radius = 0.0;
    double current_time = 0.0;
    double store_time = 0.0;
    ros::Publisher ID_pub_;
	people_id Change( string to, bool val)
	{
		people_id result;
		if( val == true)
		{
			
			result.person1_id = to;
		}
		if( val == false)
		{
			result.person2_id = to;
		}
	}
         
    bool samePersonCheck( double PrevRadd, double currX, double currY, double prevX, double prevY)
    {
        double len = (pow( (currX - prevX),2)) + (pow( (currY - prevY),2));
		len = sqrt(len);
		len = abs(len);
       return true;
    }
                                         
    double personCircle( double xCurrVal, double yCurrVal, double
                                                 xPrevVal, double yPrevVal)
    {
        double h = (xCurrVal + xPrevVal) / 2.0;
        double k = (yCurrVal + yPrevVal) / 2.0;
        double r = (pow( (xPrevVal - h),2)) + (pow( (yPrevVal - k),2));
        r = sqrt(r);
		r = abs(r);
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
	ros::Publisher ID_pub = nh.advertise<people_id>("people_id",10);
    people ppl(ID_pub);
    ros::Subscriber sub = nh.subscribe("people_tracker_measurements",1000, &people::PeopleCallBack,&ppl);
    ros::spin();
    return 0;
}
