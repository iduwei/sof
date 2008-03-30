#ifndef BASE_FACTORY_H
#define BASE_FACTORY_H
  
namespace sof
{
namespace classloading
{

template<typename BaseT>
class BaseFactory
{
	public:

		virtual BaseT* newInstance() = 0;
};

}}
#endif
