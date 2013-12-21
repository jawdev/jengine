/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > filter.h
*******************************************************/
#ifndef __JENGINE_FILTER_H__
#define __JENGINE_FILTER_H__
namespace jengine {

///////////////////////////////////////////////// Filter

class Filter {
public:
	Filter();
	virtual ~Filter();

	// run
	virtual void update();
private:
};

} //jengine
#endif //__JENGINE_FILTER_H__
