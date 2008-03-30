#ifndef FACTORY_H
#define FACTORY_H

namespace sof
{
namespace classloading
{

template<typename BaseT, typename SubT=BaseT>
class Factory : public BaseFactory<BaseT>
{
	private:
	
	public:
		BaseT* newInstance() { return new SubT; }

};

}}

#endif