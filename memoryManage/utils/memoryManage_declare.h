#ifndef MEMORYMANAGE_DECLARE_H
#define MEMORYMANAGE_DECLARE_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using std::string; /**< default using string */
using std::vector; /**< default using vector */
using std::map;    /**< default using map */

template<class Key, class T>
using umap = std::unordered_map<Key, T>; /** unordered_map usage, will merge more */

typedef unsigned char byte;
typedef unsigned int uint;
typedef std::pair<int, int> IntPair;

#define DECLARE_PTR(X) typedef boost::shared_ptr<X> X##Ptr; /**< define smart ptr */
#define FORWARD_DECLARE_PTR(X) class X; DECLARE_PTR(X)      /**< forward defile smart ptr */
#define MM_NAMESPACE_START namespace optionHedge { namespace memoryManage { 
#define MM_NAMESPACE_END }};                               
#define USING_MM_NAMESPACE using namespace optionHedge::memoryManage;

#endif
