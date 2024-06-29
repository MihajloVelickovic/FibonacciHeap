#include "fibnode.h"

FibNode::FibNode(int32_t key)
	:m_Key(key), m_Mark(false),
	 m_Degree(0), m_Parent(nullptr),
	 m_Child(nullptr), m_ChildList(std::list<FibNode*>()){}

FibNode::~FibNode(){
	m_Parent = m_Child = nullptr;
}

void FibNode::add_child_to_list(FibNode* node){
	m_ChildList.push_back(node);
}

size_t FibNode::get_degree() const{
	return m_Degree;
}

int32_t FibNode::get_key() const{
	return m_Key;
}

std::list<FibNode*>& FibNode::get_child_list(){
	return m_ChildList;
}
	
FibNode* FibNode::get_parent() const{		
	return m_Parent;
}

FibNode* FibNode::get_child() const{
	return m_Child;
}

uint32_t FibNode::marked_node_cout() const{
	uint32_t count = m_Mark ? 1 : 0;

	for(auto child: m_ChildList)
		count += child->marked_node_cout();

	return count;

}

bool FibNode::get_mark() const{
    return m_Mark;
}

void FibNode::set_parent(FibNode* node){
	m_Parent = node;
}

void FibNode::set_child(FibNode* node){
	m_Child = node;
}

void FibNode::increase_degree(int32_t deg){
	if(deg < (-1 * m_Degree))
		return;	
	m_Degree += deg;	
}

void FibNode::set_mark(bool mark){
	m_Mark = mark;
}

void FibNode::set_key(int32_t value){
	m_Key = value;
}
