#ifndef TREE_HPP
#define TREE_HPP

#include <set>

/**
   Un simple arbre n-aire générique.
   Il n'est en aucun cas équilibré : on va l'utiliser pour l'IA.
 */

template <typename T>
class Tree{

private:
  T * mValue;
  std::set< Tree<T> * > mChildren;

public:
  Tree(T * const = nullptr);
  virtual ~Tree();
  virtual void insert(const V * const);
  virtual void emplace(const V&);
  virtual std::set<Tree<T> > getChildren() const;
  virtual Tree<T> getChild(const unsigned int&) const;
  virtual void deleteChild(const unsigned int&);
};

template <typename T>
Tree<T>::Tree(T * const t){
  mValue = t;
}

template <typename T>
Tree<T>::~Tree(){
  for(auto it = mChildren.begin(); it != mChildren.end(); it++){
    if( (*it) != nullptr)
      delete *it;
  }
  mChildren.clear();
  if( mValue != nullptr)
    delete mValue;
}

template <typename T>
void Tree<T>::insert(const V * const v){
  mChildren.insert(v);
}

template <typename T>
void Tree<T>::emplace(const V& v){
  mChildren.insert(new Tree<T>(v) );
}

template <typename T>
std::set<Tree<T> * > Tree<T>::getChildren() const{
  return mChildren;
}

template <typename T>
Tree<T> * Tree<T>::getChild(const unsigned short& n) const{
  auto it = mChildren.begin();
  for(unsigned short i = 0; i < n; i++){
    if(it == mChildren.end() )
      return nullptr;
    it++;
  }
  return it;
}

template <typename T>
void Tree<T>::deleteChild(const unsigned short& i){
  auto it = mChildren.begin();
  for(unsigned short i = 0; i < n; i++){
    if(it == mChildren.end() )
      return nullptr;
    it++;
  }
  delete(it);
}

template <typename T>
void Tree<T>::deleteChild(const Tree<V> * const v){
  mChildren.erase( mChildren.find(v) );
}

#endif
