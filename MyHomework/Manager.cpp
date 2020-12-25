#ifndef MANAGER_H
#define MANAGER_H
#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#define between(left,center,right) (left <= center && center <= right) || (right <= center && center <= left)

using namespace std;

class Object {

public:
    virtual string toString()const=0;
};

class Parent_found_Exception : exception {
private:
    string out;
public:
    Parent_found_Exception(string out) {
        this->out = out;
    }
	const char*what() const throw(){
        return (string("this shape has its parent which is ")+out).c_str();
    }
};

class CouldNotSetPosition : exception {
private:
    string out;
public:
    CouldNotSetPosition(string out) {
        this->out = out;
    }
    const char*what() const throw() {
        return (string("can't set position ")+out).c_str();
    }
};

struct _3D_double: Object, pair<pair<double,double>,double> {
    _3D_double() {}
	_3D_double(const _3D_double&other){
		(*this)(other.getX(), other.getY(), other.getZ());
	}
    _3D_double(double x,double y,double z):pair( make_pair(x,y),z) {}
    double getX()const {
        return first.first;
    }
    double getY()const {
        return first.second;
    }
    double getZ()const {
        return second;
    }
	_3D_double& operator()(double x,double y,double z) {
        setX(x);
        setY(y);
        setZ(z);
		return *this;
    }
    double setX(double x) {
        first.first = x;
		return x;
    }

    double setY(double y) {
        first.second = y;
		return y;
    }
    double setZ(double z) {
        second = z;
		return z;
    }

    double distance(const _3D_double&other)const {
		_3D_double out = *this;
		out = out - other;
        out.setX(pow(out.getX(),2));
        out.setY(pow(out.getY(),2));
        out.setZ(pow(out.getZ(),2));

        return sqrt(out.getX()+out.getY()+out.getZ());
    }
    _3D_double operator-()const {
        return _3D_double(-getX(),-getY(),-getZ());
    }

    _3D_double operator+(_3D_double other)const {
        return _3D_double(getX()+other.getX(),getY()+other.getY(),getZ()+other.getZ());
    }
    _3D_double operator+(double other)const {
        return _3D_double(getX()+other,getY()+other,getZ()+other);
    }

    _3D_double operator-(_3D_double other)const {
        _3D_double out = -other;
        return (*this)+out;
    }

    _3D_double operator-(double other)const {
        return _3D_double(getX()-other,getY()-other,getZ()-other);
    }

    _3D_double operator*(double other)const {
        return _3D_double(getX()*other,getY()*other,getZ()*other);
    }

    _3D_double operator/(double other)const {
        return _3D_double(getX()/other,getY()/other,getZ()/other);
    }
	bool isBetween(const _3D_double&left,const _3D_double&right)const{
		return between(left,*this,right);
	}
    string toString()const {
        stringstream out;
        out<<"("<<first.first<<","<<first.second<<","<<second<<")";
        return out.str();
    }

	
static pair<_3D_double,_3D_double> getMaxAndMin(vector<_3D_double>&points){
	pair<_3D_double,_3D_double>out;
	out.first = out.second = points[0];
	for(unsigned int i = 0; i<points.size(); i++){
		out.first.setX(max(out.first.getX(),points[i].getX()));
		out.first.setY(max(out.first.getY(),points[i].getY()));
		out.first.setZ(max(out.first.getZ(),points[i].getZ()));

		out.second.setX(min(out.first.getX(),points[i].getX()));
		out.second.setY(min(out.first.getY(),points[i].getY()));
		out.second.setZ(min(out.first.getZ(),points[i].getZ()));

	}
	return out;
}

};



class Shape:public Object {//search for )=0; to get all abstract methods
protected:
    vector<Shape*>children;
    _3D_double center;
    _3D_double length;

    void addChild(Shape*child) {
        if(length< child->getLength()){
            throw CouldNotSetPosition("length of parent is smaller than child");
        }
        child->children[0]=this;
        children.push_back(child);
    }
    bool isIn(Shape*child){
		for(_3D_double i:child->getAllPoints()){
			if(!isSharedWith(i))
				return false;
		}
        return true;
    };
    virtual void drawShape()=0;

public:
    Shape( Shape*parent,_3D_double center,_3D_double length):children(vector<Shape*>(10)),length(length),center(center) {
        if(parent != nullptr) {
            parent->addChild(this);
        } else {
            children.push_back(nullptr);
        }
    }
    Shape* getParent() {
        if(children.size() == 0)
            return nullptr;
        return children[0];
    }

    void setPosition(_3D_double p) {//set position according to 0,0,0
        _3D_double cur = center;
        if(getParent()!=nullptr) {
            center = p;
            if(!getParent()->isIn(this)) {
                center = cur;
                throw CouldNotSetPosition(p.toString()+string("makes child out of its parent"));
            }
        }
        center = p;
    }

    _3D_double getPosition() {
        return center;
    }

    void setLength(_3D_double length) {
        this->length = length;
    }
    _3D_double getLength() {
        return length;
    }

    void draw(){
        this->drawShape();
		bool x = true;
        for(Shape*i:children){
			if(x){
				x=false;
				continue;
			}
            if(i!=nullptr)
                i->draw();
        }
    };

    bool canWalkAt(_3D_double p) {
		//we have to check the boarder
        for(Shape*shape:children) {
            if(shape->isSharedWith(p))
                return false;
        }
        return true;
    }
    string toString()const {
        string out = "{";
        out+= center.toString();
        return out+"}";
    }
	virtual bool isSharedWith(const _3D_double p){
		//get max and min x
		vector<_3D_double>points = getAllPoints();
		pair<_3D_double,_3D_double> maxMin = _3D_double::getMaxAndMin(points);
		return p.isBetween(maxMin.first,maxMin.second);
	}
    virtual vector<_3D_double> getAllPoints()=0;
    
};

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return is_base_of<Base, T>::value;
}



#endif
