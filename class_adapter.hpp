#ifndef ADAPTER_HPP
#define ADAPTER_HPP

class Shape {
public:
    Shape();
    virtual void BoundingBox(Point& bottomLeft, Point& topRight ) const;
    virtual Manipulator* CreateManipulator() const;
};


class TextView {
public:
    TextView();
    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width, Coord& height) const;
    virtual bool IsEmpty() const;
};


class TextShape : public Shape, private TextView {
public:
    TextShape();
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;
};

void TextShape::BoundingBox (Point& bottomLeft, Point& topRight) const
{
    Coord bottom, left, width, height;

    GetOrigin(bottom, left);
    GetExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
    //..
}


bool TextShape::IsEmpty () const
{
    return TextView::IsEmpty();
}

Manipulator* TextShape::CreateManipulator () const
{
    return new TextManipulator(this);
}

#endif // ADAPTER_HPP
