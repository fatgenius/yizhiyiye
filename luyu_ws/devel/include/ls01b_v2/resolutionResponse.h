// Generated by gencpp from file ls01b_v2/resolutionResponse.msg
// DO NOT EDIT!


#ifndef LS01B_V2_MESSAGE_RESOLUTIONRESPONSE_H
#define LS01B_V2_MESSAGE_RESOLUTIONRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ls01b_v2
{
template <class ContainerAllocator>
struct resolutionResponse_
{
  typedef resolutionResponse_<ContainerAllocator> Type;

  resolutionResponse_()
    : status(false)  {
    }
  resolutionResponse_(const ContainerAllocator& _alloc)
    : status(false)  {
  (void)_alloc;
    }



   typedef uint8_t _status_type;
  _status_type status;





  typedef boost::shared_ptr< ::ls01b_v2::resolutionResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ls01b_v2::resolutionResponse_<ContainerAllocator> const> ConstPtr;

}; // struct resolutionResponse_

typedef ::ls01b_v2::resolutionResponse_<std::allocator<void> > resolutionResponse;

typedef boost::shared_ptr< ::ls01b_v2::resolutionResponse > resolutionResponsePtr;
typedef boost::shared_ptr< ::ls01b_v2::resolutionResponse const> resolutionResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ls01b_v2::resolutionResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ls01b_v2

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ls01b_v2::resolutionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ls01b_v2::resolutionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ls01b_v2::resolutionResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3a1255d4d998bd4d6585c64639b5ee9a";
  }

  static const char* value(const ::ls01b_v2::resolutionResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3a1255d4d998bd4dULL;
  static const uint64_t static_value2 = 0x6585c64639b5ee9aULL;
};

template<class ContainerAllocator>
struct DataType< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ls01b_v2/resolutionResponse";
  }

  static const char* value(const ::ls01b_v2::resolutionResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool status\n\
";
  }

  static const char* value(const ::ls01b_v2::resolutionResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.status);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct resolutionResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ls01b_v2::resolutionResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ls01b_v2::resolutionResponse_<ContainerAllocator>& v)
  {
    s << indent << "status: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.status);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LS01B_V2_MESSAGE_RESOLUTIONRESPONSE_H
