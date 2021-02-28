/*
Tony Xu (tonyx2)
Partners: Ryan Yoseph (ryosep2) and Ishaan Attri (iattri2)
*/
#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()

Shape::Shape(string name){
    //TODO
    name_ = name;
}
string Shape::getName(){ //returns string, in Shape class, called getName, no parameters passed in
    //TODO
    return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//getArea(), getVolume(), operator+, operator-
//copy(), clear()

void Rectangle::copy(const Rectangle& other){
    //TODO

    spec = new double[2];
    spec[0] = other.spec[0];
    spec[1] = other.spec[1];
}
void Rectangle::clear(){
    //TODO
    delete [] spec;
}
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
    spec = new double[2];
    spec[0] = width;
    spec[1] = length;
}
Rectangle::Rectangle(const Rectangle& other):Shape("Rectangle"){
    copy(other);
}
Rectangle::~Rectangle(){
    clear();
}
const Rectangle& Rectangle::operator = (const Rectangle& other){
    clear();
    copy(other);
    return *this;
}
double Rectangle::getArea()const{
    //TODO
    double area;
    area = spec[0] * spec[1];
    return area;
}
double Rectangle::getVolume()const{
    //TODO
    double volume;
    volume = 0;
    return volume;
}
Rectangle Rectangle::operator + (const Rectangle& rhs){
    //TODO
    //double newwidth = spec[0] + rhs.getWidth();
    //double newlength = spec[1] + rhs.getLength();
    return Rectangle(this->getWidth() + rhs.getWidth(),this->getLength() + rhs.getLength());
}

Rectangle Rectangle::operator - (const Rectangle& rhs){
    //TODO
    // double newwidth, newlength;
    // if ((spec[0] - rhs.getWidth()) >= 0){
    //     double newwidth = spec[0] - rhs.getWidth();

    // }
    // else{
    //     double newwidth = rhs.getWidth() - spec[0];
    // }

    // if((spec[1] - rhs.getLength()) >= 0){
    //     double newlength = spec[1] - rhs.getLength();
    // }
    // else{
    //     double newlength = rhs.getLength() - spec[1];
    // }

    return Rectangle(max(0.0,this->getWidth() - rhs.getWidth()),max(0.0,this->getLength() - rhs.getLength()));
}

// double * spec;
//spec[0] should be width
//spec[1] should be length
double Rectangle::getWidth()const{return spec? spec[0]:0;}
double Rectangle::getLength()const{return spec? spec[1]:0;}
void Rectangle::setWidth(double width){
    if (spec == NULL)
        return;

    spec[0] = width;
}
void Rectangle::setLength(double length){
    if (spec == NULL)
        return;

    spec[1] = length;
}


//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
void RectPrism::copy(const RectPrism& other){
    //TODO

    spec = new double[3];
    spec[0] = other.spec[0];
    spec[1] = other.spec[1];
    spec[2] = other.spec[2];

}
void RectPrism::clear(){
    delete [] spec;
    //TODO
}
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
    spec = new double[3];
    spec[0] = length;
    spec[1] = width;
    spec[2] = height;
}
RectPrism::RectPrism(const RectPrism& other):Shape("RectPrism"){
    copy(other);
}
RectPrism::~RectPrism(){
    clear();
}
const RectPrism& RectPrism::operator = (const RectPrism& other){
  clear();
    copy(other);
    return *this;
}
double RectPrism::getVolume()const{
    //TODO
    double volume;
    volume = spec[0] * spec[1] * spec[2];
    return volume;
}
double RectPrism::getArea()const{
    //TODO
    double area;
    area = 2 * (spec[0] * spec[1] + spec[0] * spec[2] + spec[1] * spec[2]);
    return area;
}
RectPrism RectPrism::operator + (const RectPrism& rhs){
    //TODO
    /*double newlength = spec[0] + rhs.getLength();
    double newwidth = spec[1] + rhs.getWidth();
    double newheight = spec[2] + rhs.getHeight();
    return RectPrism(newlength,newwidth,newheight);*/
    return RectPrism(this->getWidth() + rhs.getWidth(),this->getLength() + rhs.getLength(), this->getHeight() + rhs.getHeight());

}

RectPrism RectPrism::operator - (const RectPrism& rhs){
    //TODO
   /*  if ((spec[0] - rhs.getLength()) >= 0){
        double newlength = spec[0] - rhs.getLength();

    }
    else{
        double newlength = rhs.getLength() - spec[0];
    }

    if((spec[1] - rhs.getWidth()) >= 0){
        double newwidth = spec[1] - rhs.getWidth();
    }
    else{
        double newwidth = rhs.getWidth() - spec[1];
    }

    if((spec[2] - rhs.getHeight()) >= 0){
        double newheight = spec[2] - rhs.getHeight();
    }
    else{
        double newheight = rhs.getHeight() - spec[2];
    }*/
    return RectPrism(max(0.0,this->getWidth() - rhs.getWidth()),max(0.0,this->getLength() - rhs.getLength()),max(0.0,this->getHeight() - rhs.getHeight()));
}

// double * spec;
//spec[0] should be length
//spec[1] should be width
//spec[2] should be height
double RectPrism::getWidth()const{return spec? spec[1]:0;}
double RectPrism::getHeight()const{return spec? spec[2]:0;}
double RectPrism::getLength()const{return spec? spec[0]:0;}
void RectPrism::setWidth(double width){
    if (spec == NULL)
        return;

    spec[1] = width;
}
void RectPrism::setHeight(double height){
    if (spec == NULL)
        return;

    spec[2] = height;
}
void RectPrism::setLength(double length){
    if (spec == NULL)
        return;

    spec[0] = length;
}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
    //@@Insert your code here
    string name, line;
    double width, length, height;
    ifstream ifs (file_name, std::ifstream::in);
    double num_shapes = 0;
    ifs >> num_shapes;
    vector<Shape*> shape_ptrs(num_shapes, NULL);     //number of shapes is number of vector spots, each filled with NULL.
    int i = 0;                                                 //vector is called "shape_ptrs" and is filled with pointers that point to shape class stuff
    //TODO
    while(std::getline(ifs,line)){
        ifs >> name;

      //    ifs >> name;
            if(name == "Rectangle") {
              ifs >> width;
              ifs >> length;
              shape_ptrs[i] = new Rectangle(width, length);
            }

            else{
              ifs >> width;
              ifs >> length;
              ifs >> height;
              shape_ptrs[i] = new RectPrism(width, length, height);
            }

        i++;
    }
    ifs.close();
    return shape_ptrs;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){    //vector is called "shapes"
    double max_area = 0;
  //  @@Insert your code here
  //  max_area = shapes[0]->getArea();
    for(int i = 0; i < shapes.size(); i++){
       if(max_area <= shapes[i]->getArea())
           max_area = shapes[i]->getArea();
    }

    /*
    for(int i = 0; i < shapes.size(); i++){
    if((shapes[i+1]->getArea()) >= shapes[i]->getArea()){
        max_area = shapes[i+1]->getArea();                      //ERROR
    }
    else{
        max_area = shapes[i]->getArea();                        //ERROR
    }
}
*/
    return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
    double max_volume = 0;
    //@@Insert your code here
  //  max_volume = shapes[0]->getVolume();
    for(int i = 0; i < shapes.size(); i++){
       if(max_volume <= shapes[i]->getVolume())
           max_volume = shapes[i]->getVolume();
    }

/*
    for(int i = 0; i < shapes.size(); i++){
    if((shapes[i+1]->getVolume()) >= shapes[i]->getVolume()){
        max_volume = shapes[i+1]->getVolume();                  //ERROR
    }
    else{
        max_volume = shapes[i]->getVolume();                    //ERROR
    }
}
*/

    return max_volume;
}
