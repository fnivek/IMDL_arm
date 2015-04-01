#ifndef _ROS_object_finder_TargetDesc_h
#define _ROS_object_finder_TargetDesc_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "object_finder/Mesh.h"
#include "object_finder/Color.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"

namespace object_finder
{

  class TargetDesc : public ros::Msg
  {
    public:
      uint32_t type;
      object_finder::Mesh mesh;
      double sphere_radius;
      object_finder::Color sphere_color;
      object_finder::Color sphere_background_color;
      geometry_msgs::PoseWithCovariance prior_distribution;
      double min_dist;
      double max_dist;
      bool check_180z_flip;
      bool disallow_yawing;
      bool allow_pitching;
      bool allow_rolling;
      geometry_msgs::Point extract_origin;
      geometry_msgs::Vector3 extract_x;
      geometry_msgs::Vector3 extract_y;
      uint32_t extract_x_pixels;
      uint32_t extract_y_pixels;
      enum { TYPE_MESH = 0 };
      enum { TYPE_SPHERE = 1 };

    TargetDesc():
      type(0),
      mesh(),
      sphere_radius(0),
      sphere_color(),
      sphere_background_color(),
      prior_distribution(),
      min_dist(0),
      max_dist(0),
      check_180z_flip(0),
      disallow_yawing(0),
      allow_pitching(0),
      allow_rolling(0),
      extract_origin(),
      extract_x(),
      extract_y(),
      extract_x_pixels(0),
      extract_y_pixels(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->type >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->type >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->type >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->type >> (8 * 3)) & 0xFF;
      offset += sizeof(this->type);
      offset += this->mesh.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_sphere_radius;
      u_sphere_radius.real = this->sphere_radius;
      *(outbuffer + offset + 0) = (u_sphere_radius.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sphere_radius.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sphere_radius.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sphere_radius.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_sphere_radius.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_sphere_radius.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_sphere_radius.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_sphere_radius.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->sphere_radius);
      offset += this->sphere_color.serialize(outbuffer + offset);
      offset += this->sphere_background_color.serialize(outbuffer + offset);
      offset += this->prior_distribution.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_min_dist;
      u_min_dist.real = this->min_dist;
      *(outbuffer + offset + 0) = (u_min_dist.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min_dist.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min_dist.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min_dist.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_min_dist.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_min_dist.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_min_dist.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_min_dist.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->min_dist);
      union {
        double real;
        uint64_t base;
      } u_max_dist;
      u_max_dist.real = this->max_dist;
      *(outbuffer + offset + 0) = (u_max_dist.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_dist.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max_dist.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max_dist.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_max_dist.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_max_dist.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_max_dist.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_max_dist.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->max_dist);
      union {
        bool real;
        uint8_t base;
      } u_check_180z_flip;
      u_check_180z_flip.real = this->check_180z_flip;
      *(outbuffer + offset + 0) = (u_check_180z_flip.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->check_180z_flip);
      union {
        bool real;
        uint8_t base;
      } u_disallow_yawing;
      u_disallow_yawing.real = this->disallow_yawing;
      *(outbuffer + offset + 0) = (u_disallow_yawing.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->disallow_yawing);
      union {
        bool real;
        uint8_t base;
      } u_allow_pitching;
      u_allow_pitching.real = this->allow_pitching;
      *(outbuffer + offset + 0) = (u_allow_pitching.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->allow_pitching);
      union {
        bool real;
        uint8_t base;
      } u_allow_rolling;
      u_allow_rolling.real = this->allow_rolling;
      *(outbuffer + offset + 0) = (u_allow_rolling.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->allow_rolling);
      offset += this->extract_origin.serialize(outbuffer + offset);
      offset += this->extract_x.serialize(outbuffer + offset);
      offset += this->extract_y.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->extract_x_pixels >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->extract_x_pixels >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->extract_x_pixels >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->extract_x_pixels >> (8 * 3)) & 0xFF;
      offset += sizeof(this->extract_x_pixels);
      *(outbuffer + offset + 0) = (this->extract_y_pixels >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->extract_y_pixels >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->extract_y_pixels >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->extract_y_pixels >> (8 * 3)) & 0xFF;
      offset += sizeof(this->extract_y_pixels);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->type =  ((uint32_t) (*(inbuffer + offset)));
      this->type |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->type |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->type |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->type);
      offset += this->mesh.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_sphere_radius;
      u_sphere_radius.base = 0;
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_sphere_radius.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->sphere_radius = u_sphere_radius.real;
      offset += sizeof(this->sphere_radius);
      offset += this->sphere_color.deserialize(inbuffer + offset);
      offset += this->sphere_background_color.deserialize(inbuffer + offset);
      offset += this->prior_distribution.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_min_dist;
      u_min_dist.base = 0;
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_min_dist.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->min_dist = u_min_dist.real;
      offset += sizeof(this->min_dist);
      union {
        double real;
        uint64_t base;
      } u_max_dist;
      u_max_dist.base = 0;
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_max_dist.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->max_dist = u_max_dist.real;
      offset += sizeof(this->max_dist);
      union {
        bool real;
        uint8_t base;
      } u_check_180z_flip;
      u_check_180z_flip.base = 0;
      u_check_180z_flip.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->check_180z_flip = u_check_180z_flip.real;
      offset += sizeof(this->check_180z_flip);
      union {
        bool real;
        uint8_t base;
      } u_disallow_yawing;
      u_disallow_yawing.base = 0;
      u_disallow_yawing.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->disallow_yawing = u_disallow_yawing.real;
      offset += sizeof(this->disallow_yawing);
      union {
        bool real;
        uint8_t base;
      } u_allow_pitching;
      u_allow_pitching.base = 0;
      u_allow_pitching.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->allow_pitching = u_allow_pitching.real;
      offset += sizeof(this->allow_pitching);
      union {
        bool real;
        uint8_t base;
      } u_allow_rolling;
      u_allow_rolling.base = 0;
      u_allow_rolling.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->allow_rolling = u_allow_rolling.real;
      offset += sizeof(this->allow_rolling);
      offset += this->extract_origin.deserialize(inbuffer + offset);
      offset += this->extract_x.deserialize(inbuffer + offset);
      offset += this->extract_y.deserialize(inbuffer + offset);
      this->extract_x_pixels =  ((uint32_t) (*(inbuffer + offset)));
      this->extract_x_pixels |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->extract_x_pixels |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->extract_x_pixels |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->extract_x_pixels);
      this->extract_y_pixels =  ((uint32_t) (*(inbuffer + offset)));
      this->extract_y_pixels |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->extract_y_pixels |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->extract_y_pixels |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->extract_y_pixels);
     return offset;
    }

    const char * getType(){ return "object_finder/TargetDesc"; };
    const char * getMD5(){ return "a311959f79f83d80aec6e895a72b4784"; };

  };

}
#endif