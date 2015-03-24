#ifndef _ROS_dynamixel_servo_DynamixelControlTablePost_h
#define _ROS_dynamixel_servo_DynamixelControlTablePost_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelControlTablePost : public ros::Msg
  {
    public:
      uint16_t model_num;
      uint8_t firmware_ver;
      uint8_t id;
      uint8_t baud;
      uint8_t return_delay_time;
      uint16_t cw_angle_limit;
      uint16_t ccw_angle_limit;
      uint8_t high_temp_limit;
      uint8_t low_voltage_limit;
      uint8_t high_voltage_limit;
      uint16_t max_torque;
      uint8_t status_return_level;
      uint8_t alarm_led;
      uint8_t alarm_shutdown;
      uint16_t multi_turn_offset;
      uint8_t resolution_divider;
      uint8_t torque_enable;
      uint8_t led;
      uint8_t pid_d_gain;
      uint8_t pid_i_gain;
      uint8_t pid_p_gain;
      uint16_t goal_position;
      uint16_t moving_speed;
      uint16_t torque_limit;
      uint16_t present_position;
      uint16_t present_speed;
      uint16_t present_load;
      uint8_t present_voltage;
      uint8_t present_temp;
      uint8_t instruction_registered;
      uint8_t is_moving;
      uint8_t eeprom_lock;
      uint16_t punch;
      uint16_t consuming_current;
      uint8_t torque_control_mode;
      uint16_t goal_torque;
      uint8_t goal_acceleration;

    DynamixelControlTablePost():
      model_num(0),
      firmware_ver(0),
      id(0),
      baud(0),
      return_delay_time(0),
      cw_angle_limit(0),
      ccw_angle_limit(0),
      high_temp_limit(0),
      low_voltage_limit(0),
      high_voltage_limit(0),
      max_torque(0),
      status_return_level(0),
      alarm_led(0),
      alarm_shutdown(0),
      multi_turn_offset(0),
      resolution_divider(0),
      torque_enable(0),
      led(0),
      pid_d_gain(0),
      pid_i_gain(0),
      pid_p_gain(0),
      goal_position(0),
      moving_speed(0),
      torque_limit(0),
      present_position(0),
      present_speed(0),
      present_load(0),
      present_voltage(0),
      present_temp(0),
      instruction_registered(0),
      is_moving(0),
      eeprom_lock(0),
      punch(0),
      consuming_current(0),
      torque_control_mode(0),
      goal_torque(0),
      goal_acceleration(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->model_num >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->model_num >> (8 * 1)) & 0xFF;
      offset += sizeof(this->model_num);
      *(outbuffer + offset + 0) = (this->firmware_ver >> (8 * 0)) & 0xFF;
      offset += sizeof(this->firmware_ver);
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->baud >> (8 * 0)) & 0xFF;
      offset += sizeof(this->baud);
      *(outbuffer + offset + 0) = (this->return_delay_time >> (8 * 0)) & 0xFF;
      offset += sizeof(this->return_delay_time);
      *(outbuffer + offset + 0) = (this->cw_angle_limit >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cw_angle_limit >> (8 * 1)) & 0xFF;
      offset += sizeof(this->cw_angle_limit);
      *(outbuffer + offset + 0) = (this->ccw_angle_limit >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ccw_angle_limit >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ccw_angle_limit);
      *(outbuffer + offset + 0) = (this->high_temp_limit >> (8 * 0)) & 0xFF;
      offset += sizeof(this->high_temp_limit);
      *(outbuffer + offset + 0) = (this->low_voltage_limit >> (8 * 0)) & 0xFF;
      offset += sizeof(this->low_voltage_limit);
      *(outbuffer + offset + 0) = (this->high_voltage_limit >> (8 * 0)) & 0xFF;
      offset += sizeof(this->high_voltage_limit);
      *(outbuffer + offset + 0) = (this->max_torque >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->max_torque >> (8 * 1)) & 0xFF;
      offset += sizeof(this->max_torque);
      *(outbuffer + offset + 0) = (this->status_return_level >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status_return_level);
      *(outbuffer + offset + 0) = (this->alarm_led >> (8 * 0)) & 0xFF;
      offset += sizeof(this->alarm_led);
      *(outbuffer + offset + 0) = (this->alarm_shutdown >> (8 * 0)) & 0xFF;
      offset += sizeof(this->alarm_shutdown);
      *(outbuffer + offset + 0) = (this->multi_turn_offset >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->multi_turn_offset >> (8 * 1)) & 0xFF;
      offset += sizeof(this->multi_turn_offset);
      *(outbuffer + offset + 0) = (this->resolution_divider >> (8 * 0)) & 0xFF;
      offset += sizeof(this->resolution_divider);
      *(outbuffer + offset + 0) = (this->torque_enable >> (8 * 0)) & 0xFF;
      offset += sizeof(this->torque_enable);
      *(outbuffer + offset + 0) = (this->led >> (8 * 0)) & 0xFF;
      offset += sizeof(this->led);
      *(outbuffer + offset + 0) = (this->pid_d_gain >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pid_d_gain);
      *(outbuffer + offset + 0) = (this->pid_i_gain >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pid_i_gain);
      *(outbuffer + offset + 0) = (this->pid_p_gain >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pid_p_gain);
      *(outbuffer + offset + 0) = (this->goal_position >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->goal_position >> (8 * 1)) & 0xFF;
      offset += sizeof(this->goal_position);
      *(outbuffer + offset + 0) = (this->moving_speed >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->moving_speed >> (8 * 1)) & 0xFF;
      offset += sizeof(this->moving_speed);
      *(outbuffer + offset + 0) = (this->torque_limit >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->torque_limit >> (8 * 1)) & 0xFF;
      offset += sizeof(this->torque_limit);
      *(outbuffer + offset + 0) = (this->present_position >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->present_position >> (8 * 1)) & 0xFF;
      offset += sizeof(this->present_position);
      *(outbuffer + offset + 0) = (this->present_speed >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->present_speed >> (8 * 1)) & 0xFF;
      offset += sizeof(this->present_speed);
      *(outbuffer + offset + 0) = (this->present_load >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->present_load >> (8 * 1)) & 0xFF;
      offset += sizeof(this->present_load);
      *(outbuffer + offset + 0) = (this->present_voltage >> (8 * 0)) & 0xFF;
      offset += sizeof(this->present_voltage);
      *(outbuffer + offset + 0) = (this->present_temp >> (8 * 0)) & 0xFF;
      offset += sizeof(this->present_temp);
      *(outbuffer + offset + 0) = (this->instruction_registered >> (8 * 0)) & 0xFF;
      offset += sizeof(this->instruction_registered);
      *(outbuffer + offset + 0) = (this->is_moving >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_moving);
      *(outbuffer + offset + 0) = (this->eeprom_lock >> (8 * 0)) & 0xFF;
      offset += sizeof(this->eeprom_lock);
      *(outbuffer + offset + 0) = (this->punch >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->punch >> (8 * 1)) & 0xFF;
      offset += sizeof(this->punch);
      *(outbuffer + offset + 0) = (this->consuming_current >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->consuming_current >> (8 * 1)) & 0xFF;
      offset += sizeof(this->consuming_current);
      *(outbuffer + offset + 0) = (this->torque_control_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->torque_control_mode);
      *(outbuffer + offset + 0) = (this->goal_torque >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->goal_torque >> (8 * 1)) & 0xFF;
      offset += sizeof(this->goal_torque);
      *(outbuffer + offset + 0) = (this->goal_acceleration >> (8 * 0)) & 0xFF;
      offset += sizeof(this->goal_acceleration);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->model_num =  ((uint16_t) (*(inbuffer + offset)));
      this->model_num |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->model_num);
      this->firmware_ver =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->firmware_ver);
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      this->baud =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->baud);
      this->return_delay_time =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->return_delay_time);
      this->cw_angle_limit =  ((uint16_t) (*(inbuffer + offset)));
      this->cw_angle_limit |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->cw_angle_limit);
      this->ccw_angle_limit =  ((uint16_t) (*(inbuffer + offset)));
      this->ccw_angle_limit |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->ccw_angle_limit);
      this->high_temp_limit =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->high_temp_limit);
      this->low_voltage_limit =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->low_voltage_limit);
      this->high_voltage_limit =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->high_voltage_limit);
      this->max_torque =  ((uint16_t) (*(inbuffer + offset)));
      this->max_torque |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->max_torque);
      this->status_return_level =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status_return_level);
      this->alarm_led =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->alarm_led);
      this->alarm_shutdown =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->alarm_shutdown);
      this->multi_turn_offset =  ((uint16_t) (*(inbuffer + offset)));
      this->multi_turn_offset |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->multi_turn_offset);
      this->resolution_divider =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->resolution_divider);
      this->torque_enable =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->torque_enable);
      this->led =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->led);
      this->pid_d_gain =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pid_d_gain);
      this->pid_i_gain =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pid_i_gain);
      this->pid_p_gain =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pid_p_gain);
      this->goal_position =  ((uint16_t) (*(inbuffer + offset)));
      this->goal_position |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->goal_position);
      this->moving_speed =  ((uint16_t) (*(inbuffer + offset)));
      this->moving_speed |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->moving_speed);
      this->torque_limit =  ((uint16_t) (*(inbuffer + offset)));
      this->torque_limit |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->torque_limit);
      this->present_position =  ((uint16_t) (*(inbuffer + offset)));
      this->present_position |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->present_position);
      this->present_speed =  ((uint16_t) (*(inbuffer + offset)));
      this->present_speed |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->present_speed);
      this->present_load =  ((uint16_t) (*(inbuffer + offset)));
      this->present_load |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->present_load);
      this->present_voltage =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->present_voltage);
      this->present_temp =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->present_temp);
      this->instruction_registered =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->instruction_registered);
      this->is_moving =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->is_moving);
      this->eeprom_lock =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->eeprom_lock);
      this->punch =  ((uint16_t) (*(inbuffer + offset)));
      this->punch |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->punch);
      this->consuming_current =  ((uint16_t) (*(inbuffer + offset)));
      this->consuming_current |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->consuming_current);
      this->torque_control_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->torque_control_mode);
      this->goal_torque =  ((uint16_t) (*(inbuffer + offset)));
      this->goal_torque |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->goal_torque);
      this->goal_acceleration =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->goal_acceleration);
     return offset;
    }

    const char * getType(){ return "dynamixel_servo/DynamixelControlTablePost"; };
    const char * getMD5(){ return "b0131b316f4d76214625a4a68a1c5101"; };

  };

}
#endif