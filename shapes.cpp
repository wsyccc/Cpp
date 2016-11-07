#ifndef POINT_H
#define POINT_H
// header file should not be "using namespace std";

#include <iostream>
#include <iostream>

class Point { //class definition
  public:
    // constructor. the = 0 makes it so we also have 
    // a default constructor with 0 arguments
    explicit Point(int x = 0, int y = 0): x_(x), y_(y){} // implicitly inline
    
    // compiler - generator copy constructor, default constructor
    // if we are copying pointers, we want each to have their own copy
    // so in that case we would want to write out own copy constructor.
    
    // + and += are related. 
        // += is a member fuction
        // + can be an outside fucntion or a member function
    // implementing +=:
    Point& operator += (const Point& p){
        x_ += p.x_; // same as: this->x_ += p.x_;
                    // this is a pointer. 
        y_ += p.y_;
        // return the current object by reference.
        return *this;
    }
    
    // this is how you declare a friend. its actually a frikin type.
    // remember we are not using namespace std, so we need std::
    friend std::ostream& operator << (std::ostream&, const Point&);
    friend std::istream& operator >> (std::istream&,  Point&);
    
    
    
  private:
    int x_, y_;
};


//if we were to put the += thingy thats in "public:" outside:
inline Point // note: no reference
operator += (const Point& lhs, const Point& rhs) {
    // make a copy of the lhs
    Point p(lhs);
    return p += rhs;
}

// didnt understand why we need this
inline std::ostream& // function defined in header <-- says albert.. whatever that means
                     // definition should be declared "inline"
operator << (std::ostream&, const Point&){
    // to print:
    return os <<  '(' << p.x_ << ',' << p.y_ << ')';
}


inline std::istream&
operator >> (stf::istream& is, Point& p){
    // if reading fails, we will still have a valid point, so we say its consistant. this is a "weak guarantee"
    // me make sure both are changed or neither is changed.
    
    // weak vs strong guarantee:
    char c1, c2, c3;
        //this is the weak version:
    return is >> c >> p.x_ >> c >> p.y_ >> c3;
        // this is the strong version:
    int x,y;
    if (is >> c1 >> x >> c2 >> y >> c3 && c1 == '(' && c2 == ',' && c3 == ')')
        p.x_ = x, p.y_ = y;
    else 
        is.setstate(std::ios_base::failbit);
    return is;
}



#endif
