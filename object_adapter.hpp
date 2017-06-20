#ifndef OBJECT_ADAPTER_HPP
#define OBJECT_ADAPTER_HPP

class TextShape : public Shape {
public:
    TextShape(TextView*);
    virtual void BoundingBox( Point& bottomLeft, Point& topRight) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;
private:
    TextView* _text;
};



TextShape::TextShape (TextView* t) {
    _text = t;
}


void TextShape::BoundingBox (Point& bottomLeft, Point& topRight) const
{
    Coord bottom, left, width, height;

    _text->GetOrigin(bottom, left);
    _text->GetExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
}


bool TextShape::IsEmpty () const
{
    return _text->IsEmpty();
}


Manipulator* TextShape::CreateManipulator () const
{
    return new TextManipulator(this);
}

#endif // OBJECT_ADAPTER_HPP
