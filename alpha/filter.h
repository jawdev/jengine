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

	// set
	Filter* shader_program( ShaderProgram* );

	// get
	vector< Entity* >* entities();
	ShaderProgram* shader_program();
private:
	vector< Entity* > m_entities;
	ShaderProgram *m_pShaderProgram;
};

} //jengine
#endif //__JENGINE_FILTER_H__
