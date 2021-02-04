// Generated by gencpp from file test_mapping/PSD.msg
// DO NOT EDIT!


#ifndef TEST_MAPPING_MESSAGE_PSD_H
#define TEST_MAPPING_MESSAGE_PSD_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace test_mapping
{
template <class ContainerAllocator>
struct PSD_
{
  typedef PSD_<ContainerAllocator> Type;

  PSD_()
    : PSD_L(0.0)
    , PSD_R(0.0)  {
    }
  PSD_(const ContainerAllocator& _alloc)
    : PSD_L(0.0)
    , PSD_R(0.0)  {
  (void)_alloc;
    }



   typedef float _PSD_L_type;
  _PSD_L_type PSD_L;

   typedef float _PSD_R_type;
  _PSD_R_type PSD_R;





  typedef boost::shared_ptr< ::test_mapping::PSD_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::test_mapping::PSD_<ContainerAllocator> const> ConstPtr;

}; // struct PSD_

typedef ::test_mapping::PSD_<std::allocator<void> > PSD;

typedef boost::shared_ptr< ::test_mapping::PSD > PSDPtr;
typedef boost::shared_ptr< ::test_mapping::PSD const> PSDConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::test_mapping::PSD_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::test_mapping::PSD_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace test_mapping

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/kinetic/share/nav_msgs/cmake/../msg'], 'test_mapping': ['/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::test_mapping::PSD_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::test_mapping::PSD_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test_mapping::PSD_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test_mapping::PSD_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test_mapping::PSD_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test_mapping::PSD_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::test_mapping::PSD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "598a8964bc738cc86264f0586f420919";
  }

  static const char* value(const ::test_mapping::PSD_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x598a8964bc738cc8ULL;
  static const uint64_t static_value2 = 0x6264f0586f420919ULL;
};

template<class ContainerAllocator>
struct DataType< ::test_mapping::PSD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "test_mapping/PSD";
  }

  static const char* value(const ::test_mapping::PSD_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::test_mapping::PSD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 PSD_L\n\
float32 PSD_R\n\
";
  }

  static const char* value(const ::test_mapping::PSD_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::test_mapping::PSD_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.PSD_L);
      stream.next(m.PSD_R);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PSD_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::test_mapping::PSD_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::test_mapping::PSD_<ContainerAllocator>& v)
  {
    s << indent << "PSD_L: ";
    Printer<float>::stream(s, indent + "  ", v.PSD_L);
    s << indent << "PSD_R: ";
    Printer<float>::stream(s, indent + "  ", v.PSD_R);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TEST_MAPPING_MESSAGE_PSD_H
