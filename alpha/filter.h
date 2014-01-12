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
	virtual void render();

	// manage
	void add( Entity* );
	void clear();

	// get
	vector< Entity* >* entities();
private:
	vector< Entity* > m_entities;
};

} //jengine
#endif //__JENGINE_FILTER_H__
