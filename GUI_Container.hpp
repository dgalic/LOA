#ifndef GUI_CONTAINER_HPP
#define GUI_CONTAINER_HPP

namespace GUI{

  class Container: public Component{
    
  protected:
    std::vector<Component *> children;
    Component * selectedChild;
    
  public:
    Container();
    ~Container();
    virtual void handle(const sf::Event& e);
    virtual void add(Component *);
    virtual void select(const unsigned int&);

}

#endif
